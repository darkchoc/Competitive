#include <bits/stdc++.h>
using namespace std;

class Container {
    public:
        bool isFile;
        map<string, Container*> children;
        string content;
        string  name;
        Container(string name, bool isFile) {
            this->name = name;
            this->isFile = isFile;
            content = "";
        }

        vector<string> listall() {
            vector<string> names;
            if(isFile)
                names.push_back(name);
            else
                for(auto it=children.begin(); it!=children.end(); it++)
                    names.push_back(it->first);
            sort(names.begin(), names.end());
            return names;
        }
};


class FileSystem {
    
    private:
        Container* root;

        vector<string> tokenize(string path){
            vector<string> tokens;
            string word = "";
            int i = 0;
            while(i < path.length()){
                if(path[i]=='/'){
                    if(word.length() > 0){
                        tokens.push_back(word);
                        word="";
                    }
                } else {
                    word+=path[i];
                }
                i++;
            }
            if(word.length() > 0)
                tokens.push_back(word);
            return tokens;
        }

    public:
        FileSystem(){
            root = new Container("/", false);
        }

        vector<string> ls(string path){
            vector<string> tokens = tokenize(path);
            Container* current = root;
            for(int i=0; i<tokens.size(); i++)
                current = current->children[tokens[i]];
            return current->listall();
        }

        void mkdir(string path){
            vector<string> tokens = tokenize(path);
            Container* current = root;
            for(int i=0; i<tokens.size(); i++){
                if(current->children.find(tokens[i])==current->children.end())
                    current->children[tokens[i]] = new Container(tokens[i], false);
                current = current->children[tokens[i]];
            }
        }

        void addContentToFile(string path, string content){
            vector<string> tokens = tokenize(path);
            Container* current = root;
            for(int i=0; i<tokens.size(); i++){
                if(current->children.find(tokens[i])==current->children.end()) // this would only happen for last token if the file is not already created.
                    current->children[tokens[i]] = new Container(tokens[i], true); 
                current = current->children[tokens[i]];
            }
            // current points to file
            current->content += content;
        }

        string readContentFromFile(string path){
            vector<string> tokens = tokenize(path);
            Container* current = root;
            for(int i=0; i<tokens.size(); i++)
                current = current->children[tokens[i]];
            return current->content;
        }
};

void runFileSystemTest(vector<string> commands, vector<vector<string> > arguments) {
    vector<vector<string> > responses;
    FileSystem* fs;
    for(int i=0; i<commands.size(); i++){
        if(commands[i]=="FileSystem"){
            fs = new FileSystem();
            vector<string> toRet;
            toRet.push_back("NULL");
            responses.push_back(toRet);
        } else if(commands[i]=="ls") {
            vector<string> fileFolderList = fs->ls(arguments[i][0]);
            responses.push_back(fileFolderList);
        } else if(commands[i]=="mkdir") {
            fs->mkdir(arguments[i][0]);
            vector<string> toRet;
            toRet.push_back("NULL");
            responses.push_back(toRet);
        } else if(commands[i]=="addContentToFile") {
            fs->addContentToFile(arguments[i][0], arguments[i][1]);
            vector<string> toRet;
            toRet.push_back("NULL");
            responses.push_back(toRet);
        } else {
            string content = fs->readContentFromFile(arguments[i][0]);
            vector<string> toRet;
            toRet.push_back(content);
            responses.push_back(toRet);
        }
    }

    for(int i=0; i<responses.size(); i++){
        for(int j=0; j<responses[i].size(); j++){
            cout << responses[i][j] << ", ";
        }
        cout << endl;
    }
    cout << "Done" << endl;
    return;
}

int main(){
    vector<string> commands;
    vector<vector<string> > arguments;
    vector<string> arg;
    commands.push_back("FileSystem"); // NULL,
    arguments.push_back(arg); arg.clear();

    commands.push_back("ls"); // blank
    arg.push_back("/");
    arguments.push_back(arg); arg.clear();

    commands.push_back("mkdir"); // NULL,
    arg.push_back("/a/b/c");
    arguments.push_back(arg); arg.clear();

    commands.push_back("addContentToFile"); // NULL,
    arg.push_back("/a/b/c/d"); arg.push_back("hello");
    arguments.push_back(arg); arg.clear();

    commands.push_back("ls"); // a
    arg.push_back("/");
    arguments.push_back(arg); arg.clear();

    commands.push_back("readContentFromFile"); // Hello
    arg.push_back("/a/b/c/d"); 
    arguments.push_back(arg); arg.clear();
    runFileSystemTest(commands, arguments);
  
    // test 2

    commands.clear(); arguments.clear(); arg.clear();
    commands.push_back("FileSystem"); // NULL,
    arguments.push_back(arg);

    commands.push_back("ls"); // blank
    arg.push_back("/");
    arguments.push_back(arg); arg.clear();

    commands.push_back("mkdir"); // NULL,
    arg.push_back("a/b/c");
    arguments.push_back(arg); arg.clear();

    commands.push_back("mkdir"); // NULL,
    arg.push_back("a/c/e");
    arguments.push_back(arg); arg.clear();

    commands.push_back("ls"); // b, c
    arg.push_back("/a");
    arguments.push_back(arg); arg.clear();

    commands.push_back("addContentToFile"); // NULL,
    arg.push_back("/a/b/c/d"); arg.push_back("First line of file");
    arguments.push_back(arg); arg.clear();

    commands.push_back("ls"); // d
    arg.push_back("/a/b/c/d");
    arguments.push_back(arg); arg.clear();

    commands.push_back("addContentToFile"); // NULL,
    arg.push_back("a/c/e/f"); arg.push_back("First line here too");
    arguments.push_back(arg); arg.clear();

    commands.push_back("readContentFromFile"); // First line of file
    arg.push_back("/a/b/c/d");
    arguments.push_back(arg); arg.clear();

    commands.push_back("addContentToFile"); // NULL,
    arg.push_back("a/b/c/d"); arg.push_back(" This is second line");
    arguments.push_back(arg); arg.clear();

    commands.push_back("readContentFromFile"); // First line of file This is second line
    arg.push_back("a/b/c/d/");
    arguments.push_back(arg); arg.clear();

    runFileSystemTest(commands, arguments);

}