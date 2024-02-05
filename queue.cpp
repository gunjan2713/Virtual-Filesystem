// #ifdef QUEUE_H
#include <iostream>
#include "queue.hpp"
// #include "inode.cpp"

// constructor
template<typename T>
// initializes a queue with a given capacity. size, front, and rear are initialized to 0.
Queue<T>::Queue(int capacity) : capacity(capacity), size(0), front(0), rear(0) {
    // dynamically allocates an array to hold elements of the queue
    array = new T[capacity];
}

// destructor
template<typename T>
Queue<T>::~Queue() {
    // deallocates the memory allocated for the array
    // delete[] array;
}

// method is used to add an element to the queue
template<typename T>
void Queue<T>::enqueue(T element) {
    // checks if the queue is full before adding a new element
    if (isFull()) {
        throw std::overflow_error("Queue is full");
    }
    // adds the element to the position pointed by rear
    array[rear] = element;
    // updates the rear position in a circular manner
    rear = (rear + 1) % capacity;
    size++;
}

// this method removes an element from the front of the queue and returns it
template<typename T>
T Queue<T>::dequeue() {
    if (isEmpty()) {
        throw std::underflow_error("Queue is empty");
    }
    // Saves the element at the front
    T element = array[front];
    // Updates the front position in a circular manner
    front = (front + 1) % capacity;
    size--;
    return element;
}

// Returns true if the queue is empty
template<typename T>
bool Queue<T>::isEmpty() {
    return size == 0;
}

// Returns true if the queue is full ( size equals capacity)
template<typename T>
bool Queue<T>::isFull() {
    return size == capacity;
}

// retrieves the front element of the queue without removing it
template<typename T>
T Queue<T>::front_element() {
    // checks if the queue is empty and throws an error if it is
    if (isEmpty()) {
        throw std::underflow_error("Queue is empty");
    }
    // Returns the element at the front of the queue
    return array[front];
}

// Defines a method to clear the queue
template<typename T>
void Queue<T>::clear() {
    size = 0;
    front = 0;
    rear = 0;
}

// Explicit instantiation for the supported types
template class Queue<int>;
template class Queue<double>;
template class Queue<Inode*>;
template class Queue<string>;

// #endif // QUEUE_H


