/*
1166. Design File System
You are asked to design a file system which provides two functions:

bool createPath(string path, int value): Creates a new path and associates a value to it if possible and returns True. Returns False if the path already exists or its parent path doesn't exist.
int get(string path): Returns the value associated with a path or returns -1 if the path doesn't exist.
The format of a path is one or more concatenated strings of the form: / followed by one or more lowercase English letters. For example, /leetcode and /leetcode/problems are valid paths while an empty string and / are not.

Implement the two functions.


Please refer to the examples for clarifications.

 

Example 1:

Input:
["FileSystem","createPath","get"]
[[],["/a",1],["/a"]]
Output:
[null,true,1]
Explanation:
FileSystem fileSystem = new FileSystem();

fileSystem.createPath("/a", 1); // return true
fileSystem.get("/a"); // return 1
Example 2:

Input:
["FileSystem","createPath","createPath","get","createPath","get"]
[[],["/leet",1],["/leet/code",2],["/leet/code"],["/c/d",1],["/c"]]
Output:
[null,true,true,2,false,-1]
Explanation:
FileSystem fileSystem = new FileSystem();

fileSystem.createPath("/leet", 1); // return true
fileSystem.createPath("/leet/code", 2); // return true
fileSystem.get("/leet/code"); // return 2
fileSystem.createPath("/c/d", 1); // return false because the parent path "/c" doesn't exist.
fileSystem.get("/c"); // return -1 because this path doesn't exist.
 
Constraints:

2 <= path.length <= 100
1 <= value <= 109
Each path is valid and consists of lowercase English letters and '/'.
At most 104 calls in total will be made to createPath and get.
*/


/*
Thoughts: 
Create a struct called FolderWithValue. This can have nested folders, as well as one value inside it. 

When we need to create a folder:
 - Will first tokenize the given path. Then we'll try to go deeper into the folders, till the time we are at the last folder in the path. If that already
 exists, we'll return false. If it doesn't exist, we'll create it. If any of the parent folders didn't exist, we'll return false.

When it comes to get a value:
 - Just parse deeper into the folders similarly.
 */

#include <iostream>
using namespace std;

class FileSystem {
    typedef struct FolderWithValue {
        int val;
        unordered_map<string, FolderWithValue*> folders;
        FolderWithValue(int x): val(x) {};
    } FolderWithValue;

    private:
        FolderWithValue* rootFolder;

        vector<string> tokenize(string &path) {
            vector<string> tokens;
            string token = "";
            for(int i=1; i<path.length(); i++) {
                if(path[i]=='/') {
                    tokens.push_back(token);
                    token = "";
                } else {
                    token.push_back(path[i]);
                }
            }
            if(token.length() > 0)
                tokens.push_back(token);
            return tokens;
        }

    public:
        FileSystem() {
            rootFolder = new FolderWithValue(-1);
        }

        bool createPath(string path, int val) {
            vector<string> tokens = tokenize(path);
            FolderWithValue* currentFolder = rootFolder;
            for(int i=0; i<tokens.size()-1; i++) { // go deeper till second last folder
                if(currentFolder->folders.find(tokens[i])==currentFolder->folders.end())
                    return false;
                currentFolder = currentFolder->folders[tokens[i]];
            }
            // now we are standing in parent folder of the folder we have to create
            if(currentFolder->folders.find(tokens[tokens.size()-1])!=currentFolder->folders.end())
                return false; // folder already created.
            // else create
            currentFolder->folders[tokens[tokens.size()-1]] = new FolderWithValue(val);
            return true;
        }
        
        int get(string path) {
            vector<string> tokens = tokenize(path);
            FolderWithValue* currentFolder = rootFolder;
            for(int i=0; i<tokens.size(); i++){
                if(currentFolder->folders.find(tokens[i])==currentFolder->folders.end())
                    return false;
                currentFolder = currentFolder->folders[tokens[i]];
            }
            return currentFolder->val;
        }

};

int main() {
    // Test 1
    FileSystem fileSystem;
    cout << fileSystem.createPath("/a", 1) << endl; // true 
    cout << fileSystem.get("/a") << endl; // 1

    cout << endl; 

    // Test 2
    FileSystem fileSystem2;
    cout << fileSystem2.createPath("/leet", 1) << endl; // true
    cout << fileSystem2.createPath("/leet/code", 2) << endl; // true
    cout << fileSystem2.get("/leet/code") << endl; // 2
    cout << fileSystem2.createPath("/c/d", 1) << endl; // false, because the parent path "/c" doesn't exist.
    cout << fileSystem2.get("/c") << endl; // -1, because this path doesn't exist.

    cout << endl; 

    // Test 3
    FileSystem fileSystem3;
    cout << fileSystem3.createPath("/a", 1) << endl; // true 
    cout << fileSystem3.createPath("/a/b", 2) << endl; // true
    cout << fileSystem3.createPath("/a/c", 3) << endl; // true
    cout << fileSystem3.createPath("/a/c/d", 4) << endl; // true
    cout << fileSystem3.createPath("/a/e/d", 5) << endl; // false
    cout << fileSystem3.createPath("/a/b", 2) << endl; // false, because folder already exists
    cout << fileSystem3.get("/a/c") << endl; // 3
    cout << fileSystem3.get("/a/b") << endl; // 2
    cout << fileSystem3.get("/a/e") << endl; // -1
}