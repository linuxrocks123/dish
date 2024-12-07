/*dish.y -- Yacc grammar file for Dish language*/
%define parse.error verbose
%{
#include <cassert>
#include <climits>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <regex>
#include <unistd.h>
#include <unordered_set>
  
#include "Number.hpp"
#include "spawn.hpp"
#include "StringFunctions.h"
#include "xmacroplay.h"

using namespace std;

int yylex();
void yyerror(const char* e_str);

struct Coordinates
{
  Number x;
  Number y;
};

struct Options
{
  int ordinal;
  enum Direction { LEFT, RIGHT, TOP, BOTTOM } direction;
  Coordinates offset;
  bool case_sensitive;
};

Coordinates get_coordinates(string text, Options options);
void xmacroplay(const string& x);

%}

%union
{
  Options options;
  Number numeric_literal;
  char* text_literal;
  struct
  {
    char* begin_ptr;
    char* end_ptr;
  } key_list;
  int integral_literal;
}

%token CLICK SEEK TYPE KEY SLEEP
%token CASE
%token FROM
%token <numeric_literal> NUMBER
%token <integral_literal> INTEGER ORDINAL
%token <text_literal> STRING
%token <key_list> KEY_LIST

%type <options> Options Disambiguator Offset
%type <numeric_literal> Number

%start Command

%%

Command:        CLICK Options STRING
                {
                    Coordinates c = get_coordinates($3,$2);
                    xmacroplay("MotionNotify "+to_string(c.x)+" "+to_string(c.y));
                    xmacroplay("ButtonPress 1");
                    xmacroplay("ButtonRelease 1");
                }
        |       SEEK Options STRING
                {
                    Coordinates c = get_coordinates($3,$2);
                    xmacroplay("MotionNotify "+to_string(c.x)+" "+to_string(c.y));
                }
        |       TYPE STRING
                {
                    xmacroplay(string{"String "}+$2);
                }
        |       KEY KEY_LIST
                {
                    for(const char* command : { "KeyStrPress ", "KeyStrRelease " } )
                    {
                      char* cur_ptr = $2.begin_ptr;
                      while(cur_ptr < $2.end_ptr)
                      {
                        string x = cur_ptr;
                        xmacroplay(command+x);
                        cur_ptr += x.length()+1;
                      }
                    }
                }
        |       SLEEP INTEGER
                {
                    sleep($2);
                }
        |       /*empty*/
                {
                };

Options:        CASE Disambiguator
                {
                    $$ = $2;
                    $$.case_sensitive = true;
                }
        |       Disambiguator
                {
                    $$ = $1;
                    $$.case_sensitive = false;
                };

Disambiguator:  '[' INTEGER FROM ORDINAL ']' Offset
                {
                    $$ = $6;
                    $$.ordinal = $2;
                    $$.direction = (Options::Direction)$4;
                }
        |       Offset
                {
                    $$ = $1;
                    $$.ordinal = -1;
                };

Offset:         '+' '[' Number ',' Number ']'
                {
                    $$.offset = Coordinates{$3, $5};
                }
        |       /*empty*/
                {
                    $$.offset = Coordinates{0,0};
                };

Number:         NUMBER
                {
                    $$ = $1;
                }
        |       INTEGER
                {
                    $$ = $1;
                };

%%

int yylex()
{
  static enum { SEEN_NOTHING = 0, SEEN_CASE, SEEN_ORDINAL_BEGIN, SEEN_ORDINAL_END, SEEN_OFFSET_BEGIN, SEEN_OFFSET_END, SEEN_KEY_CMD, SEEN_SLEEP_CMD } line_state;
  static char* buffer;
  static char* buffer_end;
  static char* saveptr;
  const static regex INTEGRAL("-?[0-9]+",regex_constants::extended);
  const static regex NUMERIC("[-+]?[0-9]+(\\.[0-9]+)?",regex_constants::extended);
  const unordered_set<string> DIRECTIONS { "left", "right", "top", "bottom" };

  char* token = NULL;
  size_t ignored;

  if(!buffer)
  {
    line_state = SEEN_NOTHING;
    if(saveptr)
    {
      free(saveptr);
      saveptr = nullptr;
      return 0;
    }
    if(getline(&buffer,&ignored,stdin)==-1)
      return 0;
    
    buffer_end = buffer + strlen(buffer);
    if(*(buffer_end-1)=='\n')
    {
      buffer_end--;
      *buffer_end = '\0';
    }
    
    token = strtok_r(buffer," \t",&saveptr);
  }
  else if(!(token = strtok_r(NULL," \t",&saveptr)))
  {
    free(buffer);
    line_state = SEEN_NOTHING;
    buffer = NULL;
    return 0;
  }

  if(token+strlen(token)==buffer_end)
  {
    saveptr = buffer;
    buffer = nullptr;
  }

  if(!strcmp(token,"click") && line_state==SEEN_NOTHING)
    return CLICK;
  else if(!strcmp(token,"seek") && line_state==SEEN_NOTHING)
    return SEEK;
  else if(!strcmp(token,"type") && line_state==SEEN_NOTHING)
    return TYPE;
  else if(!strcmp(token,"key") && line_state==SEEN_NOTHING)
  {
    line_state = SEEN_KEY_CMD;
    return KEY;
  }
  else if(!strcmp(token,"sleep") && line_state==SEEN_NOTHING)
  {
    line_state = SEEN_SLEEP_CMD;
    return SLEEP;
  }
  else if(!strcmp(token,"-case") && line_state==SEEN_NOTHING)
  {
    line_state = SEEN_CASE;
    return CASE;
  }
  else if(!strcmp(token,"from") && line_state==SEEN_ORDINAL_BEGIN)
    return FROM;
  else if(!strcmp(token,"[") && line_state < SEEN_OFFSET_BEGIN)
  {
    line_state = line_state < SEEN_ORDINAL_BEGIN ? SEEN_ORDINAL_BEGIN : SEEN_OFFSET_BEGIN;
    return '[';
  }
  else if(!strcmp(token,"]") && line_state < SEEN_OFFSET_END)
  {
    line_state = line_state < SEEN_ORDINAL_END ? SEEN_ORDINAL_END : SEEN_OFFSET_END;
    return ']';
  }
  else if(!strcmp(token,"+") && line_state < SEEN_OFFSET_BEGIN)
  {
    line_state = SEEN_ORDINAL_END;
    return '+';
  }
  else if(!strcmp(token,",") && line_state==SEEN_OFFSET_BEGIN)
    return ',';
  else if((line_state==SEEN_ORDINAL_BEGIN || line_state==SEEN_OFFSET_BEGIN || line_state==SEEN_SLEEP_CMD) && regex_match(token,NUMERIC))
  {
    if(*token=='+')
      token++;

    if(regex_match(token,INTEGRAL))
    {
      yylval.integral_literal = atoi(token);
      return INTEGER;
    }

    yylval.numeric_literal = Number{token};
    return NUMBER;
  }
  else if(line_state==SEEN_ORDINAL_BEGIN && DIRECTIONS.count(token))
  {
    if(!strcmp(token,"left"))
      yylval.integral_literal = Options::LEFT;
    else if(!strcmp(token,"right"))
      yylval.integral_literal = Options::RIGHT;
    else if(!strcmp(token,"top"))
      yylval.integral_literal = Options::TOP;
    else
    {
      assert(!strcmp(token,"bottom"));
      yylval.integral_literal = Options::BOTTOM;
    }
    return ORDINAL;
  }
  //No match, but special because of previously seen key command
  else if(line_state==SEEN_KEY_CMD)
  {
    yylval.key_list.begin_ptr = token;
    while(*token)
    {
      if(*token=='+')
        *token = '\0';
      token++;
    }
    yylval.key_list.end_ptr = token;

    return KEY_LIST;
  }

  //Okay, nothing special found, so just return the remainder of the line as a single STRING token
  char* token_end = token + strlen(token);
  if(token_end!=buffer_end)
  {
    *token_end = ' ';
    saveptr = buffer;
    buffer = nullptr;
  }

  yylval.text_literal = token;
  return STRING;
}

void yyerror(const char* e_str)
{
  cerr << e_str << endl;
}

struct Paddle_Entry
{
  unsigned x_left, x_right, y_top, y_bottom;
  string characters;

  Coordinates center() const { return Coordinates{(x_left+x_right)/2,(y_top+y_bottom)/2}; }
  Coordinates left() const { return Coordinates{x_left,(y_top+y_bottom)/2}; }
  Coordinates right() const { return Coordinates{x_right,(y_top+y_bottom)/2}; }
  Coordinates top() const { return Coordinates{(x_left+x_right)/2,y_top}; }
  Coordinates bottom() const { return Coordinates{(x_left+x_right)/2,y_bottom}; }
  unsigned width() const { return x_right - x_left; }
  unsigned height() const { return y_bottom - y_top; }
  Paddle_Entry subentry(string to_match) const;
};

Paddle_Entry Paddle_Entry::subentry(string to_match) const
{
  Paddle_Entry to_return{};
  int idx;
  if((idx=characters.find(to_match))==-1)
    return to_return;

  Number pixels_per_char = Number{width()}/characters.length();
  pixels_per_char.round(Number{1,8});
  to_return.x_left = x_left + (int64_t)(idx*pixels_per_char);
  to_return.x_right = x_left + (int64_t)((idx+to_match.length())*pixels_per_char);
  to_return.y_top = y_top;
  to_return.y_bottom = y_bottom;
  to_return.characters = to_match;
  return to_return;
}

static pair<unsigned,unsigned> parse_paddle_token(string token)
{
  token = StringFunctions::slice(token,1,INT_MAX);
  vector<string> tokens;
  StringFunctions::strsplit(tokens,token,", ");
  return make_pair(stoi(tokens[0]),stoi(tokens[1]));
}

static Paddle_Entry get_paddle_entry_for_line(string line)
{
  vector<string> tokens;
  StringFunctions::strsplit(tokens,line,": [[");
  if(tokens.size()==1)
    return Paddle_Entry{};

  line = tokens[1];
  tokens.clear();
  StringFunctions::strsplit(tokens,line,"], ");
  if(tokens.size() < 5)
    return Paddle_Entry{};

  for(unsigned i=5; i<tokens.size(); i++)
    tokens[4]+="], "+tokens[i];
  tokens.resize(5);

  tokens[3] = StringFunctions::slice(tokens[3],0,-1);
  Paddle_Entry to_return{UINT_MAX,0,UINT_MAX,0};
  for(unsigned i=0; i<4; i++)
  {
    pair<unsigned,unsigned> bound = parse_paddle_token(tokens[i]);
    to_return.x_left = min(to_return.x_left,bound.first);
    to_return.x_right = max(to_return.x_right,bound.first);
    to_return.y_top = min(to_return.y_top,bound.second);
    to_return.y_bottom = max(to_return.y_bottom,bound.second);
  }

  tokens[4] = StringFunctions::slice(tokens[4],2,tokens[4].rfind(", ")-1);
  bool backslash_escape = 0;
  for(unsigned i=0; i<tokens[4].size(); i++)
    if(tokens[4][i]=='\\')
    {
      if(backslash_escape)
        to_return.characters+=tokens[4][i];
      backslash_escape = !backslash_escape;
    }
    else
      to_return.characters+=tokens[4][i];

  return to_return;
}

Coordinates get_coordinates(string text, Options options)
{
  if(!options.case_sensitive)
    text = StringFunctions::upperCase(text);
  
  system("import -window root dish_current_screenshot.png");
  auto paddle = spawn({"paddleocr", "--lang", "en", "--image_dir", "dish_current_screenshot.png"});
  get_streams(paddle);

  vector<Paddle_Entry> matches;
  string line;
  while(getline(paddle_in,line))
  {
    if(line.find("INFO: [[[")==-1)
      continue;

    Paddle_Entry entry = get_paddle_entry_for_line(line);
    if(!options.case_sensitive)
      entry.characters = StringFunctions::upperCase(entry.characters);
    entry = entry.subentry(text);
    if(entry.characters.length())
      matches.push_back(entry);
  }

  if(matches.empty())
  {
    cerr << "Could not find text: " << text << endl;
    exit(1);
  }

  Paddle_Entry entry;
  if(options.ordinal==-1)
    if(matches.size()==1)
      entry = matches[0];
    else
    {
      cerr << "Multiple matches for text: " << text << endl;
      exit(2);
    }
  else
  {
    if(matches.size() < options.ordinal)
    {
      cerr << "Too few matches for text: " << text << endl;
      exit(1);
    }
    
    sort(matches.begin(),matches.end(),[&options,&text](const Paddle_Entry& left, const Paddle_Entry& right)
         {
           if(options.direction < Options::TOP && left.center().x==right.center().x || options.direction >= Options::TOP && left.center().y==right.center().y)
           {
             cerr << "Could not disambiguate matches for text: " << text << endl;
             exit(2);
           }
           switch(options.direction)
           {
           case Options::LEFT: return left.center().x < right.center().x;
           case Options::RIGHT: return left.center().x > right.center().x;
           case Options::TOP: return left.center().y < right.center().y;
           case Options::BOTTOM: return left.center().y > right.center().y;
           }
         });
    entry = matches[options.ordinal-1];
  }

  options.offset.x *= entry.width();
  options.offset.y *= entry.height();

  Coordinates offset_point = entry.center();
  if(options.offset.x != 0)
    offset_point.x = options.offset.x < 0 ? entry.x_left : entry.x_right;
  if(options.offset.y != 0)
    offset_point.y = options.offset.y < 0 ? entry.y_top : entry.y_bottom;

  offset_point.x += options.offset.x;
  offset_point.y += options.offset.y;
  return offset_point;
}

void xmacroplay(const string& x)
{
  static Display* display;
  static int screen;
  if(!display)
  {
    display = remoteDisplay(NULL);
    screen = DefaultScreen(display);
  }
  xmacro_command(display,screen,x.c_str());
}

int main()
{
  int retval;
  while(!feof(stdin) && !(retval = yyparse()));

  return retval;
}
