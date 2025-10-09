#include <iostream>  // requires reviewing
#include "arrayqueue.h"

ArrayQueue::ArrayQueue(size_t maxSize)
    : capacity(maxSize), front(0), rear(0), count(0)
{
    data = new int[capacity];
}


ArrayQueue::~ArrayQueue() {
    delete[] data;
}


bool ArrayQueue::isEmpty() const {
    return count == 0;
}

bool ArrayQueue::isFull() const {
    return count == capacity;
}

size_t ArrayQueue::size() const {
    return count;
}

size_t ArrayQueue::getCapacity() const {
    return capacity;
}


void ArrayQueue::enqueue(int value) {
    if (isFull()) {
        std::cout << "Queue is full. Cannot enqueue.\n";
        return;
    }

    data[rear] = value;
    rear = (rear + 1) % capacity; // circular move
    ++count;

    std::cout << "Enqueued: " << value << '\n';
}


void ArrayQueue::dequeue() {
    if (isEmpty()) {
        std::cout << "Queue is empty. Cannot dequeue.\n";
        return;
    }

    std::cout << "Dequeued: " << data[front] << '\n';
    front = (front + 1) % capacity;
    --count;
}


int ArrayQueue::getFront() const {
    if (isEmpty()) {
        std::cout << "Queue is empty.\n";
        return -1;
    }
    return data[front];
}


void ArrayQueue::display() const {
    if (isEmpty()) {
        std::cout << "Queue is empty.\n";
        return;
    }

    std::cout << "Queue: ";
    for (size_t i = 0; i < count; ++i) {
        size_t index = (front + i) % capacity;
        std::cout << data[index] << ' ';
    }
    std::cout << '\n';
}


int main() {
    ArrayQueue q(5); // queue with capacity 5

    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    q.enqueue(40);
    q.display();

    std::cout << "Front element: " << q.getFront() << '\n';

    q.dequeue();
    q.dequeue();
    q.display();

    q.enqueue(50);
    q.enqueue(60);
    q.enqueue(70); // will fail if full
    q.display();

    return 0;
}

