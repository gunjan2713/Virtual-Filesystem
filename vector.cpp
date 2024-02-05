// #ifdef VECTOR_H
#include "vector.hpp"
#include "inode.hpp"
#include <iostream>


template <typename T>
// returns an iterator pointing to the first element of the vector
typename Vector<T>::iterator Vector<T>::begin() {
    return data; }

template <typename T>
// returns a constant iterator pointing to the first element
typename Vector<T>::const_iterator Vector<T>::begin() const {
    return data; 
}

template <typename T>
// Returns an iterator pointing to one past the last element of the vecto
typename Vector<T>::iterator Vector<T>::end() {
    return data + v_size; 
}

template <typename T>
// Returns a constant iterator pointing to one past the last element
typename Vector<T>::const_iterator Vector<T>::end() const {
    return data + v_size; 
}

// Constructor
template <typename T>
// Initializes size to 0 and allocates memory for the array
Vector<T>::Vector(int cap) : v_size(0), v_capacity(cap) {
    data = new T[v_capacity];
}

// Destructor
template <typename T>
Vector<T>::~Vector() {
    // delete[] data;
}

// returns the current size (number of elements) of the vector
template <typename T>
int Vector<T>::size() const {
    return v_size;
}

// returns the capacity (allocated size) of the vector
template <typename T>
int Vector<T>::capacity() const {
    return v_capacity;
}

// removes the first occurrence of the specified element from the vector
template <typename T>
void Vector<T>::remove(const T& element) {
    int index = -1;
    // searches for the element and records its index
    for (int i = 0; i < v_size; ++i) {
        if (data[i] == element) {
            index = i;
            break;
        }
    }
// if the element is found, shifts subsequent elements one position left and decrements the size
    if (index != -1) {
        for (int i = index; i < v_size - 1; ++i) {
            data[i] = data[i + 1];
        }
        --v_size;
    }
}

// returns true if the vector is empty
template <typename T>
bool Vector<T>::empty() const {
    return v_size == 0;
}

// returns the first element of the vector
template <typename T>
const T& Vector<T>::front() {
    // Throws an exception if the vector is empty
    if (empty()) throw std::out_of_range("Vector is empty");
    return data[0];
}

// Returns the last element of the vector
template <typename T>
const T& Vector<T>::back() {
     // throws an exception if the vector is empty
    if (empty()) throw std::out_of_range("Vector is empty");
    return data[v_size - 1];
}

// adds an element to the end of the vector
template <typename T>
void Vector<T>::push_back(T element) {
    // If the vector is full
    if (v_size == v_capacity) {
        // it reallocates with double the previous capacity
        v_capacity = (v_capacity == 0) ? 1 : 2 * v_capacity;
        T* new_data = new T[v_capacity];
        // copies existing elements to the new array
        for (int i = 0; i < v_size; ++i) {
            new_data[i] = data[i];
        }
        // deletes the old array
        delete[] data;
        data = new_data;
    }
    data[v_size++] = element;
}

// inserts an element at a specified index
template <typename T>
void Vector<T>::insert(int index, T element) {
    // checks if the index is within the valid range
    if (index < 0 || index > v_size) throw std::out_of_range("Index out of range");
    // If the vector is full
    if (v_size == v_capacity) {
        // it reallocates with double the previous capacity
        v_capacity = (v_capacity == 0) ? 1 : 2 * v_capacity;
        T* new_data = new T[v_capacity];
        // copies existing elements to the new array
        for (int i = 0; i < v_size; ++i) {
            new_data[i] = data[i];
        }
        // deletes the old array
        delete[] data;
        data = new_data;}
        // Shifts elements to the right to make room for the new element and then inserts it
    for (int i = v_size; i > index; --i) {
        data[i] = data[i - 1];
    }
    data[index] = element;
    ++v_size;
}

// Erases the element at a specified index
template <typename T>
void Vector<T>::erase(int index) {
    if (index < 0 || index >= v_size) throw std::out_of_range("Index out of range");
    // Checks if the index is within the valid range
    for (int i = index; i < v_size - 1; ++i) {
// Shifts elements to the left to fill the gap left by the erased element and decrements the size
        data[i] = data[i + 1];
    }
    --v_size;
}
// overloads the subscript operator for element access
template <typename T>
T& Vector<T>::operator[](int index) {
      // Checks if the index is within the valid range and returns the element at that index
    if (index < 0 || index >= v_size) throw std::out_of_range("Index out of range");
    return data[index];
}


// Similar to operator[], but more explicitly name
template <typename T>
T& Vector<T>::at(int index) {
    // Checks if the index is within the valid range and returns the element at that index
    if (index < 0 || index >= v_size) throw std::out_of_range("Index out of range");

    return data[index];
}

// Reduces the capacity of the vector to fit its size
template <typename T>
void Vector<T>::shrink_to_fit() {
    // If the size is less than the capacity, reallocates the array to match the size and updates the capacity
    if (v_size < v_capacity) {
        T* new_data = new T[v_size];
        for (int i = 0; i < v_size; ++i) {
            new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
        v_capacity = v_size;
    }
}
// efines a method to display the contents of the vector
template <typename T>
void Vector<T>::display() {
    for (int i = 0; i < v_size; ++i) {
        std::cout << data[i] << " ";
    }
    std::cout << std::endl;
}


// Explicit template instantiation
template class Vector<int>;
template class Vector<double>;
template class Vector<Inode*>;


// #endif

