/*
Algorithm to sort a file that cannot fit into RAM.
1. Stream the input file in chunks size chunk_size. Sort these, and print them into another file (output stream): scratch_x where x is the number of the scratch file.
2. Let's say the complete data was cut into k chunks, so we have k scratch files.
3. Now create k input streams, each belonging to 1 scratch file, and keep streaming the minimum element to output stream (final sorted file).
*/


#include <bits/stdc++.h>
using namespace std;

void mergeKSortedLists(string outputFile, int numScratchFiles){

    //create input streams for all scratch files
    vector<fstream> scratchFileStreams (numScratchFiles);
    for(int i=0; i<numScratchFiles; i++){
        /*
        We can't do: 
        fstream scratchStream;
        scratchStream.open("scratch_" + to_string(i), ios::in);
        scratchFileStreams.push_back(scratchStream); 

        as this will give private copy constructor error. Basically we cannot copy stream object while trying to push it to a vector. 
        We can either initialize scratchFileStreams vector as currently done, or we'll have to change it to:
        vector<fstream*> scratchFileStreams, and push pointers of fstream objects.
        */
        scratchFileStreams[i].open("scratch_" + to_string(i), ios::in);
    }

    //create output file stream
    fstream outputFileStream;
    outputFileStream.open(outputFile, ios::out);

    //apply k sorted list merge
    priority_queue<pair<int, int>, vector<pair<int, int> > , greater<pair<int, int> > > minHeap;
    int num;
    for(int i=0; i<numScratchFiles; i++){
        scratchFileStreams[i] >> num;
        minHeap.push(make_pair(num, i));
    }
    while(!minHeap.empty()){
        pair<int, int> p = minHeap.top();
        minHeap.pop();
        outputFileStream << p.first << " ";
        scratchFileStreams[p.second] >> num;
        if(scratchFileStreams[p.second].eof()){
            continue; //in "num" we actually got eof and not a valid num
        } else {
            minHeap.push(make_pair(num, p.second));
        }
    }

    //close all input and output streams and delete scratch files
    outputFileStream.close();
    for(int i=0; i<numScratchFiles; i++){
        scratchFileStreams[i].close();
        remove(("scratch_" + to_string(i)).c_str()); //to convert string to const char *, we have to user c_str().
    }
    return;
}

/*
Reads input file from a stream. Sorts once it gets chunkSize numbers. Writes the sorted chunk to a scratch file
Returns number of chunks formed.
*/
int createChunkFiles(int chunkSize, string inputFile){
    fstream inputFileStream;
    inputFileStream.open(inputFile, ios::in);
    int currentScratchFile = 0;
    bool moreInput = true;
    while(moreInput){

        vector<int> chunk;
        int num;
        for(int i=0; i<chunkSize; i++){
            inputFileStream >> num;
            if(inputFileStream.eof()){ //open executing inputFileStream >> num after consuming all nums, pointer will point to EOF. So check before inserting num to arr as otherwise we would be inserting last num twice. Check: https://stackoverflow.com/questions/21647/reading-from-text-file-until-eof-repeats-last-line
                moreInput = false;
                break;
            }
            chunk.push_back(num);
        }

        //sort this chunk
        sort(chunk.begin(), chunk.end());

        //write to scratch file
        fstream scratchFileStream;
        scratchFileStream.open("scratch_" + to_string(currentScratchFile), ios::out);
        for(int i=0; i<chunk.size(); i++)
            scratchFileStream << chunk[i] << " ";
        scratchFileStream.close();
        currentScratchFile++;
    }
    return currentScratchFile;
}

int main(){
    string inputFile = "external_sort_input.txt";
    string outputFile = "external_sort_output.txt";
    int totalNumbers = 108; //assume 108 numbers in total, and they can't fit in RAM
    int chunkSize = 10; //at a time only 10 numbers can fit. So last chunk should have 8 numbers.

    //generate random numbers and stream them to form the input file
    fstream inputFileStream;
    inputFileStream.open(inputFile, ios::out); //in write mode
    for(int i=0; i<108; i++){
        inputFileStream << rand()%200 << " ";
    }
    inputFileStream.close();
    
    int numChunks = createChunkFiles(chunkSize, inputFile);

    mergeKSortedLists(outputFile, numChunks);
    return 0;
}