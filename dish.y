/*dish.y -- Yacc grammar file for Dish language*/
%define parse.error verbose
%{
#include <cassert>
#include <climits>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <list>
#include <regex>
#include <unistd.h>
#include <unordered_set>
#include <vector>

#include "Dimension_Swapper.hpp"
#include "MultiArray.hpp"
#include "Number.hpp"
#include "rtolvalue.hpp"
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
void dump_ocr_to_txt();

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

%token CLICK SEEK TYPE KEY SLEEP PRINT
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
#ifndef PARSER_TEST
                    sleep($2);
#endif
                }
        |       PRINT { dump_ocr_to_txt(); }
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

static FILE* yyin = stdin;
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
    if(getline(&buffer,&ignored,yyin)==-1)
      return 0;
    
    buffer_end = buffer + strlen(buffer);
    while(*(buffer_end-1)=='\n' || *(buffer_end-1)==' ' || *(buffer_end-1)=='\t')
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
  else if(!strcmp(token,"print") && line_state==SEEN_NOTHING)
    return PRINT;
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
  unsigned intersects(const Paddle_Entry& other) const; //returns number of pixels

  void merge_with(const Paddle_Entry& other);
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

unsigned Paddle_Entry::intersects(const Paddle_Entry& other) const
{
  int x_left_interect = max(x_left,other.x_left);
  int x_right_intersect = min(x_right,other.x_right);
  int y_top_intersect = max(y_top,other.y_top);
  int y_bottom_intersect = min(y_bottom,other.y_bottom);

  if(x_right_intersect - x_left_interect > 0 && y_bottom_intersect - y_top_intersect > 0)
    return (x_right_intersect-x_left_interect)*(y_bottom_intersect-y_top_intersect);
  return 0;
}

void Paddle_Entry::merge_with(const Paddle_Entry& other)
{
  x_left = min(x_left,other.x_left);
  x_right = max(x_right,other.x_right);
  y_top = min(y_top,other.y_top);
  y_bottom = max(y_bottom,other.y_bottom);
  characters += '\n'+other.characters;
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

string process_escape_sequences(const string& text)
{
  string new_body;
  bool backslash_active = false;
  for(char c : text)
    if(backslash_active)
    {
      if(c=='n')
        new_body+='\n';
      else if(c=='\\')
        new_body+='\\';
      else
      {
        cerr << "Invalid escape sequence in text: " << text << endl;
        exit(3);
      }
      backslash_active = false;
    }
    else
      if(c!='\\')
        new_body+=c;
      else
        backslash_active = True;
  return new_body;
}

template<class T>
T get_matches(string text, const Options& options, istream& paddle_in)
{
  if(!options.case_sensitive)
    text = StringFunctions::upperCase(text);
  
  T matches;
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
  
  return matches;
}

Coordinates disambiguate_matches(const string& text, Options options, vector<Paddle_Entry>& matches)
{
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

    auto paddle_entry_comparator = [&options,&text](const Paddle_Entry& left, const Paddle_Entry& right)
      {
        switch(options.direction)
        {
        case Options::LEFT: return left.center().x < right.center().x;
        case Options::RIGHT: return left.center().x > right.center().x;
        case Options::TOP: return left.center().y < right.center().y;
        case Options::BOTTOM: return left.center().y > right.center().y;
        }
      };
    
    sort(matches.begin(),matches.end(),paddle_entry_comparator);

    unsigned match_idx = options.ordinal-1;
    entry = matches[match_idx];
    
    if(matches.size() > match_idx+1 && !paddle_entry_comparator(entry,matches[match_idx+1]))
    {
      cerr << "Could not disambiguate matches for text: " << text << endl;
      exit(2);
    }
    
    if(match_idx && !paddle_entry_comparator(matches[match_idx-1],entry))
    {
      cerr << "Could not disambiguate matches for text: " << text << endl;
      exit(2);
    }
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
  offset_point.x.round(1);
  offset_point.y.round(1);
  return offset_point;
}

static vector<string> backend_cmd = {"paddleocr", "--lang", "en", "--det_db_score_mode", "slow", "--image_dir", "dish_current_screenshot.png"};
void dump_ocr_to_txt()
{
  system("import -window root dish_current_screenshot.png");
  auto paddle = spawn(backend_cmd);
  get_streams(paddle);

  vector<Paddle_Entry> all_entries;
  string line;
  while(getline(paddle_in,line))
  {
    if(line.find("INFO: [[[")==-1)
      continue;

    all_entries.push_back(get_paddle_entry_for_line(line));
  }

  unsigned max_x = 0, max_y = 0;
  for(const Paddle_Entry& entry : all_entries)
  {
    max_x = max(max_x,entry.x_right+1);
    max_y = max(max_y,entry.y_bottom+1);
  }

  unsigned resolution = 16;
  while(resolution)
  {
    unsigned width = max_x/resolution;
    unsigned height = max_y/resolution;
    char* linear_ptr = (char*)alloca(width*height);
    MultiArray<char,2> text_map_(linear_ptr,height,width);
    stack<int> s;
    Array_Index_Swapper<MultiArray<char,2>,int,2> text_map(text_map_,s);
    bzero(linear_ptr,width*height);
    for(const Paddle_Entry& entry : all_entries)
    {
      unsigned x_coord = entry.x_left/resolution;
      unsigned y_coord = entry.y_top/resolution;
      for(char c : entry.characters)
      {
        if(text_map[x_coord][y_coord])
          goto fail;
        text_map[x_coord++][y_coord] = c;
      }
    }

    for(unsigned j=0; j<height; j++)
      for(int i=width-1; i>=0; i--)
        if(text_map[i][j])
        {
          for(i=i-1; i>=0; i--)
            if(!text_map[i][j])
              text_map[i][j]=' ';
          break;
        }

    for(unsigned j=0; j<height; j++)
        if(text_map[0][j])
          cout << &text_map[0][j] << endl;
    
    return;

  fail:
    resolution/=2;
  }
}

Coordinates get_coordinates(string text, Options options)
{
  #ifdef PARSER_TEST
  return Coordinates{0,0};
  #endif
  
  system("import -window root dish_current_screenshot.png");
  auto paddle = spawn(backend_cmd);
  get_streams(paddle);

  text = process_escape_sequences(text);
  vector<string> result;
  StringFunctions::tokenize(result,text,"\n");

  //Common case: only matching single line
  if(result.size()==1)
    return disambiguate_matches(text,options,rtolvalue<vector<Paddle_Entry>>(get_matches<vector<Paddle_Entry>>(text,options,paddle_in)));

  //Complex case: attemping to match multiple lines of text
  string paddle_str;
  getline(paddle_in,paddle_str,'\0');
  istringstream stream_in{paddle_str};
  vector<vector<Paddle_Entry>> match_table;
  match_table.reserve(result.size()-1);
  list<Paddle_Entry> final_matches = get_matches<list<Paddle_Entry>>(result[0],options,stream_in);
  for(int i=1; i<result.size(); i++)
  {
    stream_in.clear(); stream_in.seekg(0);
    match_table.push_back(get_matches<vector<Paddle_Entry>>(result[i],options,stream_in));
  }

  //Now, iteratively attempt to match against the next line until all lines have been considered.

  /*Y Axis bounding box tolerance of 10 pixels.  Theoretically, the top of the
    next line's bounding box should be on the exact same Y coordinate as the
    bottom of the current line's bounding box, but we live in a dark and twisted
    world.*/
  const static unsigned Y_BB_TOLERANCE = 10;
  for(auto& row : match_table)
    for(auto& entry : row)
      entry.y_top -= min(entry.y_top,Y_BB_TOLERANCE);

  for(auto& row : match_table)
    for(list<Paddle_Entry>::iterator f_it=final_matches.begin(), next; f_it!=final_matches.end(); f_it=next)
    {
      next = std::next(f_it);
      
      Paddle_Entry* best_intersector;
      unsigned best_intersection = 0;
      for(Paddle_Entry& entry : row)
      {
        unsigned intersection = f_it->intersects(entry);
        if(intersection > best_intersection)
        {
          best_intersector = &entry;
          best_intersection = intersection;
        }
      }

      if(best_intersection)
      {
        f_it->merge_with(*best_intersector);
        row.erase(row.begin()+(best_intersector-&row[0]));
      }
      else
        final_matches.erase(f_it);
    }

  return disambiguate_matches(text,options,rtolvalue<vector<Paddle_Entry>>(vector<Paddle_Entry>(final_matches.begin(),final_matches.end())));
}

void xmacroplay(const string& x)
{
  #ifdef PARSER_TEST
  cout << x << endl;
  return;
  #endif
  
  static Display* display;
  static int screen;
  if(!display)
  {
    display = remoteDisplay(NULL);
    screen = DefaultScreen(display);
  }
  xmacro_command(display,screen,x.c_str());
}

int main(int argc, char** argv)
{
  int retval;
  
  string single_command;
  if(argc > 1)
  {
    unsigned command_idx = 1;
    if(!strcmp(argv[1],"--backend"))
    {
      
      command_idx+=2;
      backend_cmd.clear();
      backend_cmd.push_back(argv[2]);
    }

    if(command_idx < argc)
    {
      single_command = argv[command_idx];
      for(unsigned i=command_idx+1; i<argc; i++)
        single_command += string(" ") + argv[i];
      yyin = fmemopen(&single_command[0],single_command.length(),"r");
    }
  }
  
  while(!feof(yyin) && !(retval = yyparse()));
  
  return retval;
}
