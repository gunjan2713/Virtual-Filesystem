# Specifies the dependencies for the final executable
output: main.o vector.o queue.o inode.o vfs.o
	# Compilation command that links these object files together into an executable
	# Ensure to include -g flag for debugging information
	g++ -g main.o vector.o queue.o inode.o vfs.o -o output

# Specifies target main.o that depends on source file main.cpp
main.o: main.cpp
	# Compilation command for main.o with -g flag
	g++ -c -g main.cpp
	
# Specifies target vfs.o that depends on vfs.cpp, vfs.hpp, vector.hpp, queue.hpp, and inode.hpp
vfs.o: vfs.cpp vfs.hpp vector.hpp queue.hpp inode.hpp
	# Compilation command for vfs.o with -g flag
	g++ -c -g vfs.cpp

# Specifies target inode.o that depends on inode.cpp, inode.hpp, vector.hpp, and queue.hpp
inode.o: inode.cpp inode.hpp vector.hpp queue.hpp
	# Compilation command for inode.o with -g flag
	g++ -c -g inode.cpp 
	
vector.o: vector.cpp vector.hpp
	# Compilation command for vector.o with -g flag
	g++ -c -g vector.cpp

# Specifies target queue.o that depends on queue.cpp and queue.hpp
queue.o: queue.cpp queue.hpp
	# Compilation command for queue.o with -g flag
	g++ -c -g queue.cpp

# Removes all the files in the current directory with the .o extension and the executable
clean:
	rm *.o output
