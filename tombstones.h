/////////////////////////////////////////////////////////////////////////////
// tombstones.h, expected interface for CSC254 assignment 5
/////////////////////////////////////////////////////////////////////////////

/*
--------------------------------------------------------------------------------------
University of Rochester
CSC 254 -- Fall 2017
Assignment 05: Tombstones
Jordy Guntur, Marcelo Gheiler
--------------------------------------------------------------------------------------
*/


#if !defined(__TOMBSTONES_H__)
#define __TOMBSTONES_H__

#include <iostream>
#include <stdlib.h>

template <class T> class Pointer;
template <class T> void free(Pointer<T>& obj);

// Class to represent a tombstone
template <class T> class Tombstone
{
public:
    int refCount;       // Reference Count
    T* pointee;         // Pointer to object
    bool isFree;        // Whether tombstone has beem freed or not

    Tombstone<T>() : pointee(0), refCount(0), isFree(false) {}                  // Default Constructor
    Tombstone<T>(T* ptrIn) : pointee(ptrIn), refCount(1), isFree(false) {}      // Boostrapping Constructor

    void addRef() {
        refCount++;
    }

    void release() {
        refCount--;
    }
    
    int refCountCheck() {
        return refCount;
    }
};

// Pointer Class
template <class T> class Pointer 
{
private:
    Tombstone<T>* tStone;
public:
    
    // Default constructor
    Pointer<T>() : tStone()
    {    
        // std::cout << "Default Constructor" << std::endl;
    }
    
    // Copy constructor
    Pointer<T>(Pointer<T>& rhs) : tStone(rhs.tStone)
    {        
        // std::cout << "Copy Constructor" << std::endl;
        tStone->refCount = 0;
        tStone->addRef();
    }

    // Boostrapping Constructor
    Pointer<T>(T* pVal)
    {
        // std::cout << "Boostrapping Constructor" << std::endl;

        tStone = new Tombstone<T>();
        tStone->pointee = pVal;
        tStone->addRef();
    }

    // Destroy a pointer
    ~Pointer<T>()
    {
        // std::cout << "Destructor" << std::endl;
        // std::cout << "Reference Count: " << tStone->refCount << std::endl;

        // Decrement the reference count
        tStone->release();          
        
        // If a pointer is being destroyed, the ref count is 0, and the pointee is not null, it is a memory leak
        if(tStone->refCount == 0 && tStone->pointee != NULL) {
            std::cout << "######################################################" << std::endl;
            std::cout << "Error: Memory Leak." << std::endl;
            std::cout << "######################################################" << std::endl;
            exit(-1);
        }
    }

    // Dereferencer
    T& operator*() const
    {
        // std::cout << "Dereferencer" << std::endl;

        // If the pointee is null while dereferencing, it is a dangling pointer
        if(tStone->pointee == NULL) {
            std::cout << "######################################################" << std::endl;
            std::cout << "Error: Dangling Pointer Exception." << std::endl;
            std::cout << "######################################################" << std::endl;
            exit(-1);
        } else {
            return *tStone->pointee;
        }
    }

    // Field Dereferencer
    T* operator->() const
    {
        // std::cout << "Field Dereferencer" << std::endl;
        if(tStone->pointee == NULL) {
            std::cout << "######################################################" << std::endl;
            std::cout << "Error: Dangling Pointer Exception." << std::endl;
            std::cout << "######################################################" << std::endl;
            exit(-1);
        } else {
            return tStone->pointee;
        }
        
    }

    // Assignment to our pointer
    Pointer<T>& operator=(const Pointer<T>& rhs)
    {   
        // std::cout << "Assignment" << std::endl;    
        tStone = rhs.tStone;
        tStone->addRef();
        return *this;
    }
    
    // Delete the object that is being pointed at
    friend void free(Pointer<T>& rhs)
    {
        // std::cout << "Free" << std::endl;

        // if the pointer is null when freeing, we know it is uninitialized
        if(rhs == 0) {
            std::cout << "######################################################" << std::endl;
            std::cout << "Error: Releasing uninitialized pointer. Exiting program." << std::endl;
            std::cout << "######################################################" << std::endl;
            exit(-1);
        }
        
        // This checks whether the pointer has already freed
        if(rhs.tStone->isFree == true)   {
            std::cout << "######################################################" << std::endl;
            std::cout << "Error: Pointer already freed. Exiting program." << std::endl;
            std::cout << "######################################################" << std::endl;
            exit(-1);
        }
        rhs.tStone->isFree = true;

        delete(rhs.tStone->pointee);
        rhs.tStone->pointee = NULL;
        rhs = NULL;
    }
    
    bool operator==(const Pointer<T>& ptrIn) const
    {
        if(tStone == ptrIn.tStone) {
            return true;
        } else {    
            return false;
        }
    }

    bool operator!=(const Pointer<T>& ptrIn) const
    {
        return (tStone != ptrIn.tStone);
    }

    bool operator==(const int number) const
    {
        // true iff Pointer is null and int is zero
        return (number == 0) && (tStone == 0);
        
    }
    
    bool operator!=(const int number) const
    {
        // false iff Pointer is null and int is zero    
        return !(number == 0);
        
    }
};


#endif // __TOMBSTONES_H__
