#include <iostream>         // this code requires checking 
#include "linkedqueue.h"


LinkedQueue::LinkedQueue() : front(nullptr), rear(nullptr), count(0) {}

LinkedQueue::~LinkedQueue() {
    clear();
}


bool LinkedQueue::isEmpty() const {
    return front == nullptr;
}

size_t LinkedQueue::size() const {
    return count;
}


void LinkedQueue::enqueue(int value) {
    Node* newNode = new Node(value, nullptr);

    if (isEmpty()) {
        front = rear = newNode;
    }
    else {
        rear->next = newNode;
        rear = newNode;
    }

    ++count;
    std::cout << "Enqueued: " << value << '\n';
}


void LinkedQueue::dequeue() {
    if (isEmpty()) {
        std::cout << "Queue is empty. Cannot dequeue.\n";
        return;
    }

    Node* temp = front;
    front = front->next;
    std::cout << "Dequeued: " << temp->data << '\n';
    delete temp;
    --count;

    if (front == nullptr) {
        rear = nullptr;
    }
}


int LinkedQueue::getFront() const {
    if (isEmpty()) {
        std::cout << "Queue is empty.\n";
        return -1; 
    }
    return front->data;
}


void LinkedQueue::clear() {
    while (!isEmpty()) {
      
        dequeue();
    }
}


void LinkedQueue::display() const {
    if (isEmpty()) {
        std::cout << "Queue is empty.\n";
        return;
    }

    Node* cur = front;
    std::cout << "Queue: ";
    while (cur) {
        std::cout << cur->data << ' ';
        cur = cur->next;
    }
    std::cout << '\n';
}


int main() {
    LinkedQueue q;

    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);

    q.display();
    std::cout << "Front element: " << q.getFront() << '\n';

    q.dequeue();
    q.display();

    q.dequeue();
    q.dequeue();
    q.dequeue(); 

    return 0;
}

