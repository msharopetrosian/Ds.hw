#pragma once
#ifndef ARRAYQUEUE_HPP
#define ARRAYQUEUE_HPP

#include <cstddef> 

class ArrayQueue {
private:
    int* data;         
    size_t capacity;   
    size_t front;      
    size_t rear;       
    size_t count;      

public:
    ArrayQueue(size_t maxSize = 10); 
    ~ArrayQueue();                   

    bool isEmpty() const;
    bool isFull() const;
    size_t size() const;
    size_t getCapacity() const;

    void enqueue(int value);  
    void dequeue();           
    int getFront() const;     
    void display() const;     
};

#endif 
