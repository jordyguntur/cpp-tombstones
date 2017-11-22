University of Rochester
CSC 254 -- Fall 2017
Assignment 05: Tombstones
Jordy Guntur (jguntur@u.rochester.edu)
Marcelo Gheiler (mgheiler@u.rochester.edu)

Files Submitted

tombstones.h
	foo1.cpp
	foo2.cpp
	foo3.cpp
	foo4.cpp
	foo5.cpp
	foo6.cpp
	foo7.cpp
	foo8.cpp
	README.txt

How to run:

To compile:
	g++ foo1.cpp

To run:
	./a.out

Overview:
	To implement our own pointer using a tombstone we first created a tombstone class in the template. Much like the diagram provided in the companion site, our tombstone has a reference count and a pointer to the object (pointee). In addition, we added a boolean to check whether or not it has already been freed as well as increment/decrement functions.

	In our pointer template, our default constructor sets everything in the tombstone to null. Our copy constructor, copies the tombstone of what is passed in and increments the reference count. The bootstrapping constructor creates a new tombstone, assigns the pointee the increments the reference count. When destroying a pointer, we decrement the reference count with a check for memory leaks. If the reference count is 0 after decrementing and the pointee is not null, we know that it is a memory leak. This is because if the pointer is destroyed but the pointee is not null and the ref count is 0, there is a leak in memory. Our dereferencer checks for a dangling pointer. When dereferencing, if the pointee is null, we know that it is a dangling pointer. We did the same for the field dereferencer. The assignment to our pointer copies the tombstone and increments the reference count. Our free function does its job of deleting the pointee and pointer. The rest of the bool operations work as they are intended to.

	Our program prints out a message then exits on errors. We assumed that was the intent of the test cases.

	Note: print statements can be uncommented to see which functions were called or to check the reference count

Sample Test Cases Output:

foo1.cpp
	foo1: OK

foo2.cpp
	######################################################
	Error: Pointer already freed. Exiting program.
	######################################################

foo3.cpp
	foo3: OK

foo4.cpp
	######################################################
	Error: Releasing uninitialized pointer. Exiting program.
	######################################################

foo5.cpp
	######################################################
	Error: Memory Leak.
	######################################################

foo6.cpp
	######################################################
	Error: Memory Leak.
	######################################################

foo7.cpp
	######################################################
	Error: Dangling Pointer Exception.
	######################################################

foo8.cpp
	######################################################
	Error: Memory Leak.
	######################################################



