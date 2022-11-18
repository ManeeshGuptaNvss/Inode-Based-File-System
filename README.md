
  

# Inode based file system

It is a virtual file system runs on top of the Linux file system.

### Prerequisites
-  The size of virtual disk is 512 MB.
- Code is written with respect to Linux file system and path hierarchy.
 - You need to install GNU g++ compiler ```sudo apt-get install g++ ```



  

### To run project

  

Compilation : run ```g++ main.cpp -o ibfs``` in the respective directory where source files are present.

Execution : run ```./ibfs``` to start the project.

  

### Operations supported by the application

> Operations outside the disk

 1. `create disk`: Creates an empty disk of size 500 MB.
 2. `mount disk`: Opens the specified disk for various file operations.
 3. `exit`: Close the application.

> After opening/mounting a particular disk, below mentioned operations can be performed on the disk

 1. `create file`: creates an empty text file.
2. `open file`: opens a particular file in read/write/append mode as specified in input, multiple files can be opened simultaneously.
3. `read file`: Displays the content of the file.
4. `write file`: Write fresh data to file(override previous data in file).
5. `append file`: Append new data to an existing file data.
6. `close file`: Closes the file.
7. `delete file`: Deletes the file.
8. `list of files`: List all files present in the current disk.
9. `list of opened files`: List all opened files and specify the mode they are open in.
10. `unmount`: Closes the currently mounted disk.

  

### Assumptions
 - While creating an empty disk a unique name will be given to it which will be used to mount it.
 - You may have multiple disks. You will open only 1 disk at a time.


# Inode-Based-File-System
