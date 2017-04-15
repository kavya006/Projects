#include "iostream"
#include "string"
#include "cstring"
#include "vector"
#include "cstdlib"
#include "Constructors.cpp"

using namespace std;


vector<string> MySplit (char delim, string rawString){
  int pos = 0;
  vector<string> output;
  string token;
  int i = 0;
  while(rawString[i] == ' '){
    i++;
  }
  rawString.erase(0, i);
  i = rawString.size() - 1;
  while(rawString[i] == ' '){
    i--;
  }
  rawString.erase(i+1, rawString.size() - 1);
  while ((pos = rawString.find(delim)) != string::npos) {
    token = rawString.substr(0, pos);
    output.push_back(token);
    rawString.erase(0, pos + 1);
    i = 0;
    while(rawString[i] == ' '){
      // rawString.erase(0,1);
      i++;
    }
    rawString.erase(0,i);
    i = rawString.size() - 1;
    while(rawString[i] == ' '){
      i--;
    }
    rawString.erase(i+1, rawString.size() - 1);
  }
  output.push_back(rawString);
  return output;
}

char* stringToChar(string a){
  char *temp = (char *) malloc((sizeof(char)*(a.size() + 1)));
  strcpy(temp, a.c_str());
  return temp;
}

vector<vector<Command *>> parseCommand(char *cmdInput){
  vector<vector<Command *>> cmdTable;
  vector<string> cmdLine;
  cmdLine = MySplit(';',string(cmdInput));
  vector<string>::iterator it;
  for(it = cmdLine.begin(); it != cmdLine.end(); ++it){
    string tmp1 = *it;
    vector<Command *> tempCommand;
    vector<string> pipes = MySplit('|',tmp1);
    vector<string>::iterator it1;
    for(it1 = pipes.begin(); it1 != pipes.end(); ++it1){
      string tmp = *it1; 
      size_t found1 = tmp.find("<");
      size_t found2 = tmp.find(">");
      string first, middle, end;
      vector<string>::iterator it2;
      vector<char *> args;
      vector<string> args_string;
      vector<string> middle_more_args;
      vector<string> end_more_args;
      char *in; 
      char *out;
      if(found1 != string::npos && found2 != string::npos){
        if(found1 < found2){
          first = tmp.substr(0, found1);
          middle = tmp.substr(found1 + 1, found2 - found1 - 1);
          middle_more_args = MySplit(' ' , middle);
          in = (char *) malloc(sizeof(char) * (middle_more_args[0].size() + 1));
          strcpy(in, middle_more_args[0].c_str());
          end = tmp.substr(found2 + 1);
          end_more_args = MySplit(' ' , end);
          out = (char *) malloc(sizeof(char) * (end_more_args[0].size() + 1));
          strcpy(out, end_more_args[0].c_str());
        }else if(found2 < found1){
          first = tmp.substr(0, found2);
          middle = tmp.substr(found2 + 1, found1 - found2 - 1);
          middle_more_args = MySplit(' ' , middle);
          out = (char *) malloc(sizeof(char) * (middle_more_args[0].size() + 1));
          strcpy(out, middle_more_args[0].c_str());
          end = tmp.substr(found1 + 1);
          end_more_args = MySplit(' ' , end);
          in = (char *) malloc(sizeof(char) * (end_more_args[0].size() + 1));
          strcpy(in, end_more_args[0].c_str());
        }
        args_string = MySplit(' ', first);
        for (it2 = args_string.begin(); it2 != args_string.end(); ++it2){
          args.push_back(stringToChar(*it2));
        }
        for (it2 = middle_more_args.begin() + 1; it2 != middle_more_args.end(); ++it2){
          args.push_back(stringToChar(*it2));
        }
        for (it2 = end_more_args.begin() + 1; it2 != end_more_args.end(); ++it2){
          args.push_back(stringToChar(*it2));
        }
        tempCommand.push_back(new RedirCommand (REDIR,in, out, args));
        continue;
      }
      else if(found2 != string::npos){
        first = tmp.substr(0,found2);
        end = tmp.substr(found2+1);
        args_string = MySplit(' ',first);
        for (it2 = args_string.begin(); it2 != args_string.end(); ++it2){
          args.push_back(stringToChar(*it2));
        }
        end = tmp.substr(found2 + 1);
        end_more_args = MySplit(' ', end);
        out = (char *) malloc(sizeof(char) * (end_more_args[0].size() + 1));
        strcpy(out, end_more_args[0].c_str());
        for (it2 = end_more_args.begin() + 1; it2 != end_more_args.end(); ++it2){
          args.push_back(stringToChar(*it2));
        }
        tempCommand.push_back(new RedirCommand (REDIR, stringToChar(""),out, args));
        continue;
      }
      else if(found1 != string::npos){
        first = tmp.substr(0,found1);
        end = tmp.substr(found1+1);
        args_string = MySplit(' ',first);
        for (it2 = args_string.begin(); it2 != args_string.end(); ++it2){
          args.push_back(stringToChar(*it2));
        }
        end = tmp.substr(found1 + 1);
        end_more_args = MySplit(' ',end);
        in = (char *) malloc(sizeof(char) * (end_more_args[0].size() + 1));
        strcpy(in, end_more_args[0].c_str());
        for (it2 = end_more_args.begin() + 1; it2 != end_more_args.end(); ++it2){
          args.push_back(stringToChar(*it2));
        }
        tempCommand.push_back(new RedirCommand (REDIR,in, stringToChar(""), args));
        continue;
      }
      args_string = MySplit(' ',tmp);
      for (it2 = args_string.begin(); it2 != args_string.end(); ++it2){
          args.push_back(stringToChar(*it2));
      }
      tempCommand.push_back(new ExecCommand(EXEC,args));
    }
    cmdTable.push_back(tempCommand); 
  }
  return cmdTable;
}
