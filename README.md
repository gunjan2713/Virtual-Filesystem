# Virtual-Filesystem
This project is a C++ implementation of a Virtual Filesystem (VFS) as part of the Data Structures course (CS-UH 1050) assignment. The VFS allows users to create, delete, and move folders and files within a tree-structured system. Each inode in the system contains metadata such as type (file or folder), size, and creation date. The system also features a Bin/Trash mechanism for managing deleted items, which can be emptied either manually or automatically.

The implementation emphasizes object-oriented programming principles and manual data structure creation, as STL containers are not permitted. It includes a command-line interface for user interaction, supporting commands for directory navigation, file manipulation, and system query operations. The project also explores error handling, efficient data management, and system persistence by loading and saving the filesystem state to disk.

Key functionalities include:
Creating and managing a hierarchical file system organized as a tree.
Navigating through directories and manipulating files with custom commands.
Implementing core filesystem features like mkdir, touch, cd, ls, mv, rm, and more, with additional support for find and recovery operations from the Bin/Trash.
