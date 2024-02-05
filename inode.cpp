// #ifdef INODE_H
#include<cstdlib>
#include<string>
#include<ctime>
#include <iostream>
// #include "vector.hpp"
#include "inode.hpp"

// Destructor for Inode 
Inode::~Inode() {
    // for (size_t i = 0; i < children.size(); ++i) {
    //     delete children[i];
    // }
}

// Defines a method to add a child inode to the current inode
void Inode::addChild(Inode* child) {
    // Adds the child inode to the children vector
    children.push_back(child);
}

// /defines a method to remove a child inode from the current inode
void Inode::removeChild(Inode* child) {
    // removes the specified child inode from the children vector
    children.remove(child);
}

// defines a method to get a constant reference to the vector of child inodes
const Vector<Inode*>& Inode::getChildren() const {
    return children;
}

// defines a method to get the name of the inode
string Inode::getName() const{
    return name;
}
// defines a method to get the type of the inode
bool Inode::getType() {
    return type;
}

// defines a method to get the size of the inode
unsigned int Inode::getSize() const{
    return size;
}

// defines a method to get the creation time of the inode
string Inode::getCreationTime() const {
    return cr_time;
}

// defines a method to set the size of the inode
void Inode::setSize(unsigned int newSize) {
    size = newSize;
}

// Defines a method to display information about the inode
void Inode::display() {
    cout << "Name: " << name << endl;
    cout << "Type: " << (type == File ? "File" : "Folder") << endl;
    cout << "Size: " << size << " bytes" << endl;
    cout << "Creation Time: " << cr_time << endl;
// If the inode is a folder, it also prints the names of its children
    if (type == Folder) {
        cout << "Children: ";
        for (int i = 0; i < children.size(); ++i) {
            cout << children[i]->getName() << " ";
        }
        cout << endl;
    }
}
// Defines a method to update the size of the inode and propagate the change to its parent inodes
void Inode::updateSize(int sizeChange) {
    // Update the size of the current inode
    this->size += sizeChange;

    // Propagate the size change up to the parent inodes
    Inode* current = this->parent;
    while (current != nullptr) {
        current->size += sizeChange;
        current = current->parent;
    }
}

template class Vector<Inode*>;
// #endif

