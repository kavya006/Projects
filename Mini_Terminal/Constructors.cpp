#include "iostream"
#include "string"
#include "cstring"
#include "vector"
#include "cstdlib"
#include "executeHelpers.cpp"
#include <fcntl.h>


#define EXEC 0
#define REDIR 1
#define PIPE 2
#define BACK 3

using namespace std;




class Command
{
  public :
    int type;
    vector<char *> args;
    Command(int x,vector<char * >arguments){
      type = x;
      args = arguments;
    }

    virtual void execute(){
      // cout << "execute in command" << endl;
    }
};

class ExecCommand : public Command{
public:
  vector<char *> args;
  ExecCommand(int x,vector<char *>arguments);
  void execute() override{
    // cout << "execute in ExecCommand" << endl;
    // if(!executeBuiltInCommand(args)){
    //   if(isBinInCommand(args[0])){
    //     int pid;
    //     pid = fork();
    //     if(pid == 0){
          executeBinInCommand(args);
          // cout << "I am here" << endl;
    //     }else{
    //       waitpid(pid, NULL, 0);
    //     }
    //   }
    // }
  }
};
ExecCommand::ExecCommand(int x,vector<char *>arguments):Command(x,arguments){
        args = arguments;
  }


class RedirCommand : public Command{
  public :
          char * inFile;
          char * outFile;
          vector<char *> args;
          bool flag = false;
          int stdoutdup = dup(1);
          int stdindup = dup(0);
          RedirCommand(int x,char *in,char *out,vector<char *>arguments);
          void execute(){
            // int pid = fork();
            // if(!executeBuiltInCommand(args)){
            //   if(pid == 0){
                int inFd;
                int outFd;
                if(strlen(inFile) != 0){
                  inFd = open(inFile, O_RDONLY);
                  if(inFd < 0){
                    cout << "Error in opening" << endl;
                    return;
                  }
                  dup2(inFd,fileno(stdin));
                }
                if(strlen(outFile) != 0){
                  outFd = open(outFile, O_CREAT | O_WRONLY,0666);
                  if(outFd < 0){
                    cout << "Error in opening" << endl;
                    return;
                  }
                  flag = true;
                  dup2(outFd,1);
                }
                executeBinInCommand(args);
                exit(0);
              }
              // else{
              //   waitpid(pid, NULL, 0);
              // }
            // }
          // }
};

RedirCommand::RedirCommand(int x,char *in,char *out,vector<char *>arguments):Command(x,arguments){
            inFile = (char *)malloc(sizeof(char)* (strlen(in)+1));
            strcpy(inFile, in);
            outFile = (char *)malloc(sizeof(char)* (strlen(out)+1));
            strcpy(outFile, out);
            args = arguments;
          }


/*class PipeCommand : public Command{
  public :
          char * inCommand;
          char * outCommand;
          PipeCommand(int x, const char* in, const char* out);
          void execute(){
            vector<Command *> cmd1 = parseCommand(inCommand);
            vector<Command *> cmd2 = parseCommand(outCommand);
            int fd[2] = [0,1];
            pipe(fd);
            for

          }
};
PipeCommand::PipeCommand(int x,const char * in, const char * out):Command(x){
            inCommand = (char *)malloc(sizeof(char)* (strlen(in)+1));
            strcpy(inCommand, in);
            outCommand = (char *)malloc(sizeof(char)* (strlen(out)+1));
            strcpy(outCommand, out);
          }
*/