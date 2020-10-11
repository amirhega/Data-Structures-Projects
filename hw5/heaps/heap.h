#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
    /// Constructs an m-ary heap for any m >= 2
    Heap(int m, PComparator c = PComparator());

    /// Destructor as needed
    ~Heap();

    /// Adds an item
    void push(const T& item);

    /// returns the element at the top of the heap
    ///  max (if max-heap) or min (if min-heap)
    T const & top() const;

    /// Removes the top element
    void pop();

    /// returns true if the heap is empty
    bool empty() const;

private:
    /// Add whatever helper functions and data members you need below
    int m;
    PComparator check;
    std::vector<T> heap;
    void trickleUp(int location);
    void heapify(unsigned int index);


};

// Add implementation of member functions here
//my code

// Your code here
template <typename T, typename PComparator>
Heap<T,PComparator>::Heap(int m, PComparator c) {
    this->m = m;
    //heap.push_back(0);
    check = c;
} 

template <typename T, typename PComparator>
Heap<T,PComparator>::~Heap() {
    
}


template <typename T, typename PComparator>
void Heap<T,PComparator>::push(const T& item){
    heap.push_back(item);
    trickleUp(heap.size()-1);
    //int parent;

}


// We will start top() for you to handle the case of
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
    // Here we use exceptions to handle the case of trying
    // to access the top element of an empty heap
    if(empty()) {
        throw std::logic_error("can't top an empty heap");
    }
    // If we get here we know the heap has at least 1 item
    // Add code to return the top element
    return heap[0];



}


// We will start pop() for you to handle the case of
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
    if(empty()) {
        throw std::logic_error("can't pop an empty heap");
    }

    //set root to back node and delete back node
    heap[0] = heap.back();
    heap.pop_back();
    //doesn't call on an empty heap because no 0 index
    if(!heap.empty()) {
        heapify(0);
    }
}


template <typename T, typename PComparator>
void Heap<T,PComparator>::trickleUp(int location) {

    //base case checks if root
    if(location  == 0) {
        return;
    }

    int parent;
    //if its less then m, parent is root
    if(location <= m) {
        parent = 0;
    } else {
        parent = (location - 1) / m;
    }

    //recursively swaps if returns true
    if(check(heap[location], heap[parent])) {
        std::swap(heap[parent], heap[location]);
        location = parent;
        trickleUp(location);
    }
}


template <typename T, typename PComparator>
void Heap<T,PComparator>::heapify(unsigned int index) {

    //base case checks if leaf node
    int sizeTemp = heap.size() - 2;
    if(sizeTemp < 0) {
        return;
    }
    if((heap.size()-2)/m < index) {
        return;
    }


    unsigned int rightmost = (m * index) + m;
    bool temp = true;
    //checks what the rightmost index that exists is
    while(temp) {

        if(rightmost <= (heap.size() - 1)) {
            temp = false;
        } else {
            rightmost--;
        }
    }

    int smallest = ((m*index)+1);
    //finds smallest child from leftmost to rightmost
    for(unsigned int i = ((m*index)+1); i <= rightmost; i++) {


        if(check(heap[i], heap[smallest])) {
            smallest = i;
        }
    }

    //recursively swaps down
    if(check(heap[smallest], heap[index])) {
        std::swap(heap[index], heap[smallest]);
        heapify(smallest);
    }

}

template <typename T, typename PComparator>
bool Heap<T,PComparator>::empty() const {
    if(heap.size() == 0)  {
        return true;
    } else {
        return false;
    }
}




#endif

