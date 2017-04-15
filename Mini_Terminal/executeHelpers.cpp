#include "iostream"
#include "string"
#include "cstring"
#include "vector"
#include "cstdlib"
#include "sys/types.h"
#include "sys/wait.h"
#include "sys/stat.h"
#include "unistd.h"

using namespace std;

bool executeBuiltInCommand(vector<char *> args){
  if(strcmp(args[0], "cd") == 0){
    if(args.size() == 1 || strcmp(args[1], string(1, '~').c_str()) == 0){
      char * temp = (char *) malloc(sizeof(char)*(2));
      strcpy(temp , (string("/home/ermichan006").c_str()));
      args.insert(args.begin() + 1,temp);
    }
    // cout << args[1] << endl;
    chdir(args[1]);
    return 1;
  }else if(strcmp(args[0], "pwd") == 0){
    char pwd[512];
    if(getcwd(pwd, sizeof(pwd)) == NULL){
      perror("getcwd error");
    }else{
      // cout << endl << pwd << endl;
    }
  }
}
bool isBinInCommand(char *cmd){
  struct stat st;
  char *path = (char *) malloc(sizeof(char)*(strlen(cmd) + 8));
  strcpy(path, "/bin/");
  strcat(path, cmd);
  if(stat(path, &st) == 0){
    cout << "isBuiltInCommand: " << endl;
    return true;
  }else{
    return false;
  }
}
void executeBinInCommand(vector<char *> cmd){
  int size = cmd.size();
  char* args[size + 1];
  for (int i = 0; i < size; ++i)
  {
    args[i] = cmd[i];
  }
  args[size] = NULL;
  // cout << "executeBuiltInCommand: " << cmd[0] << endl;
  int j = execvp( cmd[ 0 ], args );
  if(j==-1)
    exit(0);
}
/*
void executeCommand(vector<char *> cmd){

}

bool isBackgroundJob(vector<char *> cmd){
  return true;
}
*/