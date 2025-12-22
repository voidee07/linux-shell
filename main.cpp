#include<bits/stdc++.h>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;

vector<string> tokenize(const string & input){
    vector<string>tokens;
    stringstream ss(input);// splits on whitespace by default
    string token;
    while(ss>>token){// extract each token and store it in a string named token 
        tokens.push_back(token);
    }
    return tokens;
}

int main(){
    string input;
    while(true){
        cout<<"Myshell> ";

        if(!getline(cin, input)){  
              cout<<"\n";                                     //handels the ctrl+d command 
            break;
        }

        if(input=="exit"){
            break;
        }
        //cout<< "You entered: " << input << endl;---checking the loop;
        // Tokenize the input
        vector<string> tokens = tokenize(input);
        if(tokens.empty()){
            continue; // if no command is entered, prompt again
        }
        //---checking the tokens 
        // for(const auto &t:tokens){
        //     cout<<t<<endl;}

        //---builtins

        if(tokens[0]=="cd"){
            if(tokens.size()<2){
                cerr<<"cd: missing argument"<<endl;
            }
            else{
                if(chdir(tokens[1].c_str())!=0){
                    perror("cd ");
                }
            }
            continue; // prompt again after cd
        }



        vector<char*> args;
        for(auto &token:tokens){
            args.push_back(const_cast<char*>(token.c_str())); // convert string to c style null terminated strings understood by c apis 
        }
        args.push_back(nullptr); // null terminate the array

    //----checking and running the command 

   

    pid_t pid=fork();
    if(pid==0){
        //child process
        execvp(args[0],args.data());
        //if execvp returns, there was an error
        perror("execvp failed");
        exit(1);
    }
    else if (pid>0){
        waitpid(pid,nullptr,0); // parent process waits for child to finish
    }//added null ptr for the time for mvp (update later)
    else {
        perror("fork failed");
    }

    }
    return 0;}
