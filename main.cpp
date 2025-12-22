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
        cout<<"myshell> ";

        if(!getline(cin, input)){  
              cout<<"\n";                                     //handels the ctrl+d command 
            break;
        }

        if(input=="exit"){
            break;
        }
        //cout<< "You entered: " << input << endl;
        vector<string> tokens = tokenize(input);
        if(tokens.empty()){
            continue; // if no command is entered, prompt again
        }
        for(const auto &t:tokens){
            cout<<t<<endl;}
    }
    return 0;
}