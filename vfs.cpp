// #ifdef VFS_H
#include <iostream>
#include <ctime>
#include <iterator>
#include <chrono>
#include <sstream>
#include <iomanip>
#include<stack>
#include<ctime>
#include<iomanip>
// #include "inode.hpp"
// #include "queue.hpp"
#include "vfs.hpp"

// Constructor for VFS
VFS::VFS() {
    // initialize the root
    root = new Inode("/", nullptr, Folder, 0, getTime());
    // set the current and previous inode pointers
    curr_inode = root;
    prev_inode = nullptr;
}



// Display the list of available commands
void VFS::help() {
    cout << "Available commands:" << endl;
    cout << "help           (Display this help message)" << endl;
    cout << "pwd            (Print the current directory)" << endl;
    cout << "ls             (List the contents of the current directory)" << endl;
    cout<<  "mkdir          (Create a new folder under the current directory)"<<endl;
    cout<<  "touch          (Create a new file under the current directory)"<<endl;
    cout<< "cd foldername   (change current inode to the specified folder)"<<endl<<
            "cd filename    (return an error)"<<endl<<
            "cd ..          (changes current inode to its parent folder)"<<endl<<
            "cd -           (changes current inode to the previous working directory)"<<endl<<
            "cd             (changes current inode to root)"<<endl<<
            "cd /my/path/name   (changes the current inode to the specified path if it exists)"<<endl<<
            "rm             (Removes the specified folder or file and puts it in a Queue)"<<endl<<
            "size           (Display the size of a file or folder)"<<endl<<
            "showbin        (Show the contents of the bin (deleted items))"<<endl<<
            "emptybin       (Empty the bin (delete items permanently))"<<endl<<
            "recover        (Reinstates the oldest inode back from the bin to its original position in the tree ()"<<endl<<
            "find           (Returns the path of the file (or the folder) if it exists)"<<endl<<
            "exit"<<endl;
}

// return the current directory as a strinrg
string VFS::pwd() {
    // stack to store path
    stack<string> pathStack;
    Inode* currentNode = curr_inode;

    // traverse from the current inode to the root, pushing each directory name onto the stack
    while (currentNode != nullptr && currentNode != root) {
        pathStack.push(currentNode->getName());
        // moving pointer to the parent node
        currentNode = currentNode->parent;
    }

    string path;
    // if the stack is empty, we are at the root
    if (pathStack.empty()) {
        return "/";
    }

    // construct the path by popping names from the stack
    while (!pathStack.empty()) {
        // keep popping and addign to the path
        path += "/" + pathStack.top();
        pathStack.pop();
    }

    return path;
}

// get inode based on a given path
Inode* VFS::getInode(const string& path) {
    // check if the path is the root
    if (path.empty() || path == "/") {
        return root;
    }
    // declares a pointer to an Inode, named target
    Inode* target;
    if (path[0] == '/')
    // Start from the root inode
    target = root; 
    else
        target = curr_inode;
    // stringstream is used to process the path string
    stringstream ss(path);
    // declared to hold each part of the path
    string segment;

    // process each segment of the path
    while (getline(ss,segment,'/')) {
        // skip empty segments due to leading '/'
        if (segment.empty()) continue; 

        // Find \the child inode with the matching segment name
        bool found = false;
        // retrieves a list of child inodes of the current target
        Vector<Inode*> children = target->getChildren();
        for (size_t i = 0; i < children.size(); ++i) {
            Inode* child = children[i]; 
            // if a child's name matches the current segment, the target is updated to this child
            if (child->getName() == segment) {
                
                target = child;
                // found is set to true
                found = true;
                break;
            }
            }
            // If no matching child inode is found in the current segment, the function returns nullptr
        if (!found) {
            return nullptr; // Inode not found
        }
    }
    return target;
}

// list the contents of the current directory
void VFS::ls() {
    // checks if the current inode (curr_inode) is of type Folder
    if (curr_inode->getType() == Folder) {
        // retrieves the children of the current inode
        Vector<Inode*> children = curr_inode->getChildren();

        // bubble sort to order by descending file size
        bool swapped;
        do {
            swapped = false;
            // loops through the children, except the last one
            for (size_t i = 0; i < children.size() - 1; i++) {
                // compares the size of the current inode with the next inode
                if (children[i]->getSize() < children[i + 1]->getSize()) {
                    // Swap the elements
                    // creating temporary variable temp
                    Inode* temp = children[i];
                    children[i] = children[i + 1];
                    children[i + 1] = temp;
                    swapped = true;
                }
            }
        } while (swapped);

        // iterates over the sorted children for printing their details
        for (size_t i = 0; i < children.size(); ++i) {
            Inode* child = children[i];
            // for each child inode, it determines if it's a folder ("dir") or a file ("file"), based on its type.
            string type = (child->getType() == Folder) ? "dir" : "file";
            // prints the details of each child, including its type, name, size, and creation time.
            cout << type << " " << child->getName() << " " << child->getSize() << " " << child->getCreationTime() << endl;
        }
    } else {
        cerr << "Error: ls command can only be used on folders." << endl;
    }
}


// create a new folder under the current directory
void VFS::mkdir(string folder_name) {
    if (curr_inode->getType() == Folder) {
// Checks if the current inode  is of type Folder
        Vector<Inode*> children = curr_inode->getChildren();
        // iterates through each child inode in the current directory
        for (size_t i = 0; i < children.size(); ++i) {
            
            Inode* child = children[i];
            // checks if any child inode has the same name as the folder_name 
            if (child->getName() == folder_name) {
                
                cerr << "Error: Folder with the same name already exists." << endl;
                return;
            }
        }
        // creates a new Inode with the given folder_name
            Inode* new_folder = new Inode(folder_name, curr_inode, Folder, 10, getTime());
            // adds the newly created folder inode to the children of the current inode
            curr_inode->addChild(new_folder);
            
    } else {
        cerr << "Error: mkdir command can only be used on folders." << endl;
    }
}

// create a new file under the current directory
void VFS::touch(string file_name, unsigned int size) {
    // checks if the current inode (curr_inode) is a folder
    if (curr_inode->getType() == Folder) {
        // retrieves the list of child inodes 
        Vector<Inode*> children = curr_inode->getChildren();
        // starts a loop to iterate through each child inode
        for (size_t i = 0; i < children.size(); ++i) {
            Inode* child = children[i];
            // checks if any of the child inodes has the same name as the file_name
            if (child->getName() == file_name) {
                cerr << "Error: File with the same name already exists." << endl;
                return;
            }
        }
        // creates a new Inode representing a file, the file is named file_name
        Inode* new_file = new Inode(file_name, curr_inode, File, size, getTime());
        // adds the newly created file inode to the children of the current inode
        curr_inode->addChild(new_file);
    } else {
        cerr << "Error: touch command can only be used on folders." << endl;
    }
}
// change directories
void VFS::cd(string path) {
    // checks if the path is either empty or the root directory
    if (path.empty() || path == "/") {
        // change to root directory
        // update prev_inode before changing directory
        prev_inode = curr_inode; 
        curr_inode = root;
        return;
    } else if (path == "..") {
        // change to parent directory
        if (curr_inode->parent != nullptr) {
            // update prev_inode before changing directory
            prev_inode = curr_inode; 
            // changes curr_inode to its parent
            curr_inode = curr_inode->parent;
        }
        return;
    } else if (path == "-") {
        // Change to previous directory
        if (prev_inode != nullptr) {
            Inode* temp = curr_inode;
            curr_inode = prev_inode;
        //swap current and previous inodes
            prev_inode = temp; 
        }
        return;
    }
// For other path values, it attempts to find the inode corresponding to the given path
    Inode* target = getInode(path);
    // checks if the target inode was found and is a folder
    if (target != nullptr && target->getType() == Folder) {
// updates prev_inode to the current directory and changes curr_inode to the target directory
        prev_inode = curr_inode; 
        curr_inode = target;
    } else {
        cerr << "Error: Directory not found or not a folder." << endl;
    }
}


void VFS::rm(string path) {
    // find the inode based on the given path
    Inode* target = getInode(path);

    // check if the inode was not found or if it is the root inode
    if (target == nullptr || target == root) {
        cerr << "Error: File or folder not found or cannot delete root." << endl;
        return;
    }

    // Remove the inode from its parent's children list
    if (target->parent != nullptr) {
        target->parent->removeChild(target);
    }

    // Add the inode to the bin for possible recovery
    bin.enqueue(target);
    // path of the removed inode is also stored in bin_paths
    bin_paths.enqueue(path); 
}

// Display the size of a file or folder
void VFS::size(string path) {
    // Finds the inode corresponding to the given path using the getInode function
    Inode* target = getInode(path);

    if (target != nullptr) {
        // Calls the calculateSize function to calculate the total size of the target inode
        unsigned int totalSize = calculateSize(target);
        cout << "Size of " << path << ": " << totalSize << " bytes" << endl;
    } else {
        cerr << "Error: File or folder not found." << endl;
    }
}
// additional methods to help size function
unsigned int VFS::calculateSize(Inode* inode) {
    // Starts with the size of the provided inode
    unsigned int totalSize = inode->getSize();
// Checks if the inode is a folder
    if (inode->getType() == Folder) {
        // Gets the list of children inodes
        Vector<Inode*> children = inode->getChildren(); 
        // Iterates over each child inode
        for (size_t i = 0; i < children.size(); ++i) {
            // For each child inode, recursively calls calculateSize and adds the returned size to totalSize
            Inode* child = children[i];
            totalSize += calculateSize(child);
        }
    }

    return totalSize;
}

// Show the contents of the bin (deleted items)
void VFS::showbin() {
    if (bin.isEmpty()) {
        cout << "The bin is empty." << endl;
    } else {
        cout << "Contents of the bin: " ;
        // Creates a temporary copy of the bin
        Queue<Inode*> tempBin = bin; 
        // Temporary queue for paths
        Queue<string> tempBinPaths = bin_paths; 
// Iterates as long as the temporary bin queue is not empty
        while (!tempBin.isEmpty()) {
            // Removes and retrieves the front inode from the temporary bin queue
            Inode* item = tempBin.dequeue();
            // removes and retrieves the front path from the temporary bin paths queue
            string itemPath = tempBinPaths.dequeue(); 
// Prints the path, size, and creation time of the dequeued inode
            cout << itemPath << " (" << item->getSize() << " bytes, " << item->getCreationTime() << ")" << endl;
        }
    }
}

// Empty the bin (delete items permanently)
void VFS::emptybin() {
    // Iterates as long as the bin is not empty
    while (!bin.isEmpty()) {
        // Dequeues an inode from the bin
        Inode* item = bin.dequeue();
        // Deletes the dequeued inode and sets the pointer to null
        delete item;
        item = nullptr;
    }
    // clears the bin queue itself
    bin.clear();
    // clears the bin_paths queue
    bin_paths.clear();
    cout<<"Bin got cleared"<<endl;
}

// defines the recover method in the VFS class
void VFS::recover() {
    // Checks if the bin is empty
    if (bin.isEmpty()) {
        cerr << "Error: Bin is empty, no items to recover." << endl;
        return;
    }

    // Get the oldest inode and its original path
    // retrieves (and removes) the oldest inode from the bi
    Inode* item = bin.dequeue();
    // retrieves (and removes) the oldest inode from the bin
    string originalPath = bin_paths.dequeue();


    // extracts the parent path from the original pat
    string parentPath = originalPath.substr(0, originalPath.find_last_of('/'));
 // retrieves the inode corresponding to the parent path
    Inode* parentInode = getInode(parentPath);
    // checks if the parent inode is null or not a folder
    if (parentInode == nullptr || parentInode->getType() != Folder) {
        cerr << "Error: Original path does not exist anymore." << endl;
        delete item; // Important to avoid memory leak
        return;
    }

    // check if an inode with the same name already exists in the original location
    string itemName = item->getName();
//    Retrieves the children of the parent inod
    Vector<Inode*> children = parentInode->getChildren();
    // Iterates through the children of the parent inode
    for (size_t i = 0; i < children.size(); ++i) {
        // Checks if any child inode has the same name as the inode to be recovered
        if (children[i]->getName() == itemName) {
            cerr << "Error: An item with the same name already exists in the original location." << endl;
            delete item; // Important to avoid memory leak
            return;
        }
    }

    // Add the inode back to its original location
    parentInode->addChild(item);
    cout << "Recovered " << itemName << " to " << originalPath << endl;
}

// Clean up and exit the programG
void VFS::exit() {
    cout << "Exiting the program." << endl;
}
// retrieves the current date
string VFS:: getTime() {
    // declares a string named data to store the date
            string data;
    // declares a pointer to FILE, named stream
            FILE * stream;
// defines a constant max_buffer, representing the maximum buffer size for reading output from the command
            const int max_buffer = 256;
// declares a character array buffer of size max_buffer to store the output read from the command
            char buffer[max_buffer];
    // Command to get the current date
            string cmd = "date +%Y-%m-%d"; 
// popen function starts the process and creates a pipe to read its output
            stream = popen(cmd.c_str(), "r");
//checks if the stream was successfully opened
            if (stream) {
                while (!feof(stream))
                // characters are appended to the data string
                    if (fgets(buffer, max_buffer, stream) != NULL) data.append(buffer);
            // Closes the stream and thereby the process started by popen
                pclose(stream);
            }
            return data;
        }
// #endif

