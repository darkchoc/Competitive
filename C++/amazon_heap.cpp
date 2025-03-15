#include <bits/stdc++.h>
using namespace std;

// implement a priority queue
// do this from the ground up, e.g. the container
// let have quick mini-design: data structure
// heap - how do we rearrange the heap, what's the characteristic of the heap


class PriorityQueue {
private:    
    vector<int> heap;
    
    void bubbleUp(int ind){
        if(ind == 0) return;
        int parent = (ind-1)/2;
        if(heap[parent] > heap[ind]){
            swap(heap[parent], heap[ind]);
            bubbleUp(parent);
        }
    }

    void bubbleUpIterativeImplementation(int ind){
        while(ind > 0 && heap([(ind-1)/2] > heap[ind])){
            swap(heap[(ind-1)/2], heap[ind]);
            ind = (ind-1)/2;
        }
    }
    
    void bubbleDown(int ind){
        int left = 2*ind + 1;
        int right = 2*ind + 2;
        int smallest = ind;
        if(left < heap.size()){
            if(heap[left] < heap[ind]){
                smallest = left;
            }
        }
        if(right < heap.size()){
            if(heap[right] < heap[smallest]){
                smallest = right;
            }
        }
        if(smallest != ind){
            swap(heap[smallest], heap[ind]);
            bubbleDown(smallest);
        }
    }
    
    void buildHeap(){
        for(int i=heap.size()/2; i>=0; i--){
            bubbleDown(i);
        }
    }
    
    
public:    
    PriorityQueue(vector<int> arr){
        heap = arr;
        buildHeap();
    }    
    
    void add(int element){
        heap.push_back(element);
        int n = heap.size();
        bubbleUp(n-1);
    }
    
    int pop(){
        if(heap.size()==0) return 0;
        swap(heap[0], heap[heap.size()-1]);
        int toReturn = heap[heap.size()-1];
        heap.pop_back();
        bubbleDown(0);
        return toReturn;
    }
    
    int top(){
        if(heap.size() > 0)
            return heap[0];
        return -1.0;
    }

    void printHeap(){
        for(int i=0; i<heap.size(); i++)
            cout << heap[i] << " ";
        cout << endl;
    }
};

int main(){
    vector<int> arr;
    arr.push_back(10);
    arr.push_back(8);
    arr.push_back(4);
    arr.push_back(9);
    arr.push_back(3);
    arr.push_back(5);
    arr.push_back(2);
    arr.push_back(1);
    arr.push_back(7);
    PriorityQueue* pq = new PriorityQueue(arr);
    pq->printHeap();
    PriorityQueue* pq2 = new PriorityQueue(vector<int> ());
    pq2->add(10);
    pq2->add(8);
    pq2->add(4);
    pq2->add(9);
    pq2->add(3);
    pq2->add(5);
    pq2->add(2);
    pq2->add(1);
    pq2->add(7);
    pq2->printHeap();
    cout << pq2->pop() << endl;
    pq2->printHeap();
    cout << pq2->top() << endl;
}

