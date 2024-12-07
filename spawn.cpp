#include "spawn.hpp"
#include "StringFunctions.h"

#include <ctime>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <utility>
#include <vector>

using namespace std;
using __gnu_cxx::stdio_filebuf;

static int exec_wrapper(const vector<string>& tokens)
{
  char* filename = StringFunctions::permanent_c_str(tokens[0]);
  char** args = new char*[tokens.size()+1];
  for(int i=0; i<tokens.size(); i++)
    args[i] = StringFunctions::permanent_c_str(tokens[i]);
  args[tokens.size()]=NULL;
  return execvp(filename,args);
}

tuple<int,int,pid_t> spawn(const vector<string>& tokens)
{
  //Now we create pipes and do fork/exec
  int to_child, to_parent;
  int parent_writes[2];
  int child_writes[2];
  pipe(parent_writes);
  pipe(child_writes);
  pid_t child_id = fork();

  if(child_id!=0) //we are the parent
  {
    //Set up pipe communication
    to_child = parent_writes[1];
    to_parent = child_writes[0];
    close(parent_writes[0]);
    close(child_writes[1]);

    //Return child's ID and read end of child's pipe
    return make_tuple(to_parent,to_child,child_id);
  }
  else //we are the child
  {
    //Set up pipe communication
    to_child = parent_writes[0];
    to_parent = child_writes[1];
    close(parent_writes[1]);
    close(child_writes[0]);

    //Redirect pipes to standard in and standard out
    dup2(to_child,STDIN_FILENO);
    dup2(to_parent,STDOUT_FILENO);

    //Execute child: exec_wrapper() does not return if the child's main process is able to be executed.
    exec_wrapper(tokens);

    //If exec_wrapper() returns, it means something went wrong, most likely a typo in the Bakefile.  Exit with error.
    exit(1);
  }
}
