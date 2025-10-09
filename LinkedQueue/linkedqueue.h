#ifndef LINKEDQUEUE_HPP
#define LINKEDQUEUE_HPP

#include <cstddef> // size_t

struct Node {
    int data;
    Node* next;
    Node(int value = 0, Node* nextPtr = nullptr) : data(value), next(nextPtr) {}
};


class LinkedQueue {
private:
    Node* front;   
    Node* rear;    
    size_t count;  

public:
    LinkedQueue();        
    ~LinkedQueue();       

    bool isEmpty() const;     
    size_t size() const;      

    void enqueue(int value);  
    void dequeue();          
    int getFront() const;    

    void clear();            
    void display() const;    
};

#endif 
