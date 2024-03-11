#include <bits/stdc++.h>
using namespace std;

class Path {
    public:
        string name; 
        string isFile;
        Path(string name, bool isFile){
            this->name = name;
            this->isFile = isFile;
        }
        virtual vector<string> listAll() = 0;
};

class Folder: public Path {
    public:
        vector<Path*> paths;
        Folder(string name): Path(name, false){}
        vector<string> listAll (){
            vector<string> contents;
            for(int i=0; i<paths.size(); i++)
                contents.push_back(paths[i]->name);
            sort(contents.begin(), contents.end());
            return contents;
        }
};

class File: public Path {
    public:
        string content;
        File(string name): Path(name, true){}
        vector<string> listAll() {
            vector<string> toRet;
            toRet.push_back(name);
            return toRet;
        }
};

class FileSystem {
    
    private:
        Path* root;
        vector<string> tokenize(string path){
            vector<string> tokens;
            string word = "";
            int i=0;
            while(i < path.length()){
                if(path[i]=='/'){
                    if(word.length() > 0){
                        tokens.push_back(word);
                        word = "";
                    }
                } else {
                    word += path[i];
                }
                i++;
            }
            if(word.length() > 0)
                tokens.push_back(word);
            return tokens;
        }

    public:
        FileSystem(){
            root = new Folder("/");
        }

        vector<string> ls(string path){
            vector<string> tokens = tokenize(path);
            Path* current = root;
            for(int i=0; i<tokens.size(); i++){
                vector<Path*> &mypaths = static_cast<Folder*>(current)->paths;
                for(int j=0; j< mypaths.size(); j++){
                    if(mypaths[j]->name == tokens[i]){
                        current = mypaths[j];
                        break;
                    }
                }
            }
            // now current points to last Path of the path we received as input. It coudl be file or folder.
            return current->listAll();
        }

        void mkdir(string path){
            Path* current = root;
            vector<string> tokens = tokenize(path);
            for(int i=0; i<tokens.size(); i++){
                vector<Path*> &mypaths = static_cast<Folder*>(current)->paths;
                int j = 0;
                for(; j<mypaths.size(); j++){
                    if(mypaths[j]->name == tokens[i]){
                        current = mypaths[j];
                        break;
                    }
                }
                if(j==mypaths.size()){
                    // create this folder
                    mypaths.push_back(new Folder(tokens[i]));
                    current = mypaths[j];
                } 
            }
        }

        void addContentToFile(string path, string content){
            vector<string> tokens = tokenize(path);
            Path* current = root;
            for(int i=0; i<tokens.size(); i++){
                vector<Path*> &mypaths = static_cast<Folder*>(current)->paths;
                int j = 0;
                for(j=0; j<mypaths.size(); j++){
                    if(mypaths[j]->name == tokens[i]){
                        current = mypaths[j];
                        break;
                    }
                }
                if(j==mypaths.size()){
                    // file doesn't exist
                    mypaths.push_back(new File(tokens[i]));
                    current = mypaths[mypaths.size()-1];
                    // no need to break as this would be last token.
                }
            }
            // current points to file.
            static_cast<File*>(current)->content += content;
        }

        string readContentFromFile(string path){
            vector<string> tokens = tokenize(path);
            Path* current = root;
            for(int i=0; i<tokens.size(); i++){
                vector<Path*> &mypaths = static_cast<Folder*>(current)->paths;
                for(int j=0; j<mypaths.size(); j++){
                    if(mypaths[j]->name == tokens[i]){
                        current = mypaths[j];
                        break;
                    }
                }
            }
            // current points to current file
            return static_cast<File*>(current)->content;
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