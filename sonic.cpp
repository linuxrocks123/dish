#include <iostream>
#include <unordered_map>
#include "StringFunctions.h"

using namespace std;

const static unordered_map<string,string> REPLACEMENTS = { {"one","1"}, {"two","2"}, {"three","3"}, {"four","4"}, {"five","5"}, {"six","6"}, {"seven","7"}, {"eight","8"}, {"nine","9"}, {"zero","0"}, {"space"," "}};
const static unordered_map<string,string> CONTEXTUAL_REPLACEMENTS = { {"in","n"} };

int main()
{
  string line;
  while(getline(cin,line))
  {
    vector<string> line_parts;
    StringFunctions::strsplit(line_parts,line,": \"");
    line = line_parts[1];
    if(line[0]=='"')
      continue;
    line_parts.clear();
    StringFunctions::strsplit(line_parts,line,"\"");
    line = line_parts[0];
    line_parts.clear();
    if(!line.length())
      continue;
    StringFunctions::strsplit(line_parts,line," ");
    cout << line_parts[0] << ' ';
    for(int i=1; i<line_parts.size(); i++)
    {
      const string& to_print = line_parts[i];
      if(REPLACEMENTS.count(to_print))
        cout << REPLACEMENTS.at(to_print);
      else if(CONTEXTUAL_REPLACEMENTS.count(to_print) && (line_parts[i-1].size()==1 || line_parts[i+1].size()==1))
        cout << CONTEXTUAL_REPLACEMENTS.at(to_print);
      else
        cout << to_print;
    }
    cout << endl;
  }
}
