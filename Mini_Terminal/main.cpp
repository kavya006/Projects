// Simple Shell (Pseudo Code):
#include "iostream"
#include "string"
#include "cstring"
#include "vector"
#include "cstdlib"
#include "fstream"
#include "sys/types.h"
#include "sys/wait.h"
#include "sys/stat.h"
#include "unistd.h"
#include "readline/readline.h"
#include "readline/history.h"
#include "parser.cpp"

using namespace std;

char currDir[512];
vector <int> backgroundPIDS;


char *getCWD(){
  if(getcwd(currDir, sizeof(currDir)) == NULL){
    perror("getcwd() error\n");
  }
  int i = 0;
  int count = 0;
  char *temp;
  temp = (char *)malloc(strlen(currDir) + 1);
  strcpy(temp, currDir);
  while(i < strlen(temp)){
    if(temp[i] == '/'){
      count++;
    }
    if(count == 3){
      break;
    }
    temp = temp + 1;
  }
  char *temp2 = (char *)malloc(strlen(temp)+3);
  temp2[0]='~';
  temp2[1]='\0';
  // cout << temp << " " << temp2 << endl;
  strcat(temp2, temp);
  return temp2;
}

char* printPrompt(){
  char *temp2 = getCWD();
  char *temp = (char *) malloc(sizeof(char)*(40+strlen(temp2)));
  char temp3[] = "ermichan006@CharmKavya ";
  char temp4[] = " [$] ";
  strcpy(temp, temp3);
  strcat(temp, temp2);
  strcat(temp, temp4);
  return temp;
}

int main ()
{
  while (1){
    int stdout = dup(1);
    int stdin = dup(0);
    char *cmdLine;
    vector<vector<Command *>> cmd;
    bool isBackgroundJob = false;
    // printPrompt();
    cmdLine = readline(printPrompt()); //or GNU readline("");
    string temp = string(cmdLine);
    int size = temp.size() - 1;
    while(temp[size] == ' '){
      size--;
    }
    temp.erase(size+1, temp.size() - 1);
    if(temp.find('&') == temp.size()-1){
      isBackgroundJob = true;
      cmdLine[temp.size() - 1] ='\0';
    }
    if(strlen(cmdLine)>513){
      cout << "Error : Very long command line" << endl;
      continue;
    }
    cmd = parseCommand(cmdLine);
    vector<string>::iterator it2;
    for (int i = 0; i < cmd.size(); ++i)
    {
      /*if (isBuiltInCommand(cmd[i])){
        cout << "isBuiltInCommand " << endl;
      } else if(isBinInCommand(cmd[i][0])){
        int pid;
        pid = fork();
        if(pid == 0){
          executeBuiltInCommand(cmd[i]);
        }else{
          waitpid(pid, NULL, 0);
        }
      } 
      else {                
         childPid = fork();
         if (childPid == 0){
          executeCommand(cmd[i]); //calls execvp  
         } else {
          if (isBackgroundJob(cmd[i])){
              cout << "A background job" << endl;
              // record in list of background jobs
          } else {
            waitpid (childPid, NULL, 0);
          }               
        }
      }*/
      for (int j = 0; j < cmd[i].size(); ++j)
      {
        int fd[2] = {0,1};
        pipe(fd);
        Command &c = *(cmd[i][j]);
        if(!executeBuiltInCommand(c.args)){
          int pid;
          pid = fork();
          if(pid == 0){
            if(j!=cmd[i].size()-1)
              dup2(fd[1],1);
            close(fd[1]);
            close(fd[0]);
            if(isBackgroundJob){
              int k = open("Background.txt",O_CREAT | O_WRONLY,0666);
              dup2(k,1);}
            if(strcmp(c.args[0],"lsb") ==0){
              for (int p=0;p<backgroundPIDS.size();p++){
                cout << p << endl;
              }
              exit(0);
            }
            else{
              c.execute();
            }
          }
          else{
            if(j!=cmd[i].size()-1)
              dup2(fd[0],0);
            close(fd[0]);
            close(fd[1]);
            if(!isBackgroundJob){
              waitpid(pid,NULL,0);
            }
            else{
              backgroundPIDS.push_back(pid);
              waitpid(pid,NULL,WNOHANG);
            }
          }
        }
      }
      dup2(stdout,1);
      dup2(stdin,0);
    }
    dup2(stdout,1);
  }
}
