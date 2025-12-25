#include<bits/stdc++.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>   // open

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

        //-- checking for valid  pipe
        int pipe_pos = -1;
          for (int i = 0; i < tokens.size(); i++) {
            if (tokens[i] == "|") {
          pipe_pos = i;
          break;
    }
}

if (pipe_pos != -1) {
    vector<string> left(tokens.begin(), tokens.begin() + pipe_pos);
    vector<string> right(tokens.begin() + pipe_pos + 1, tokens.end());

    if (left.empty() || right.empty()) {
        cerr << "syntax error near |\n";
        continue;
    }

    // pipe logic will go here

    int fd[2];// defined an array of two integers to hold the read and write file descriptors
if (pipe(fd) < 0) {
    perror("pipe");
    continue;
}
    pid_t pid1 = fork();
    if (pid1 == 0) { // first child for left command
        close(fd[0]); // close read end
        dup2(fd[1], STDOUT_FILENO); // redirect stdout to pipe write end
        close(fd[1]);

        vector<char*> args_left;
        for (auto &token : left) {
            args_left.push_back(const_cast<char*>(token.c_str()));
        }
        args_left.push_back(nullptr);

        execvp(args_left[0], args_left.data());
        perror("execvp failed");
        exit(1);
    }

    pid_t pid2 = fork();
    if (pid2 == 0) { // second child for right command
        close(fd[1]); // close write end
        dup2(fd[0], STDIN_FILENO); // redirect stdin to pipe read end
        close(fd[0]);

        vector<char*> args_right;
        for (auto &token : right) {
            args_right.push_back(const_cast<char*>(token.c_str()));
        }
        args_right.push_back(nullptr);

        execvp(args_right[0], args_right.data());
        perror("execvp failed");
        exit(1);
    }

    // parent process
    close(fd[0]);
    close(fd[1]);
    waitpid(pid1, nullptr, 0);
    waitpid(pid2, nullptr, 0);
    continue; // prompt again after handling the pipe


}



        
        //--- Redirection 
        bool redirect_output = false;
        bool append_output = false;
        bool redirect_input = false;
           string in_file;

            string out_file;
            vector<string> cmd_tokens;

            for (size_t i = 0; i < tokens.size(); i++) {
                 if (tokens[i] == ">") {
                 if (i + 1 >= tokens.size()) {
                     cerr << "syntax error: expected filename after >\n";
                      
            cmd_tokens.clear();
            break;
        }
        redirect_output = true;
        append_output = false;
        out_file = tokens[i + 1];
        break;
    }
    else if (tokens[i] == ">>") {
        if (i + 1 >= tokens.size()) {
            cerr << "syntax error: expected filename after >>\n";
            cmd_tokens.clear();
            break;
        }
        redirect_output = true;
        append_output = true;
        out_file = tokens[i + 1];
        break;
    }
     else if (tokens[i] == "<") {
        if (i + 1 >= tokens.size()) {
            cerr << "syntax error: expected filename after <\n";
            cmd_tokens.clear();
            break;
        }
        redirect_input = true;
        in_file = tokens[i + 1];
        break;
    }
    else {
        cmd_tokens.push_back(tokens[i]);
    }
}

if (cmd_tokens.empty()) continue;// the complete while loop 




        vector<char*> args;
        for(auto &token:cmd_tokens){
            args.push_back(const_cast<char*>(token.c_str())); // convert string to c style null terminated strings understood by c apis 
        }
        args.push_back(nullptr); // null terminate the array

    //----checking and running the command 
    //---forking 

   

    pid_t pid=fork();
    if(pid==0){ //child process
        //redirection 
    if (redirect_input) {
    int fd = open(in_file.c_str(), O_RDONLY);
    if (fd < 0) {
        perror("open");
        exit(1);
    }
    dup2(fd, STDIN_FILENO);
    close(fd);
}
        if (redirect_output) {
             int flags = O_WRONLY | O_CREAT;
    if (append_output)
        flags |= O_APPEND;
    else
        flags |= O_TRUNC;
    int fd = open(out_file.c_str(), flags, 0644);
    if (fd < 0) {
        perror("open");
        exit(1);
    }
    dup2(fd, STDOUT_FILENO);
    close(fd);
}

       
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
