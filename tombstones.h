/////////////////////////////////////////////////////////////////////////////
// tombstones.h, expected interface for CSC254 assignment 5
/////////////////////////////////////////////////////////////////////////////

#if !defined(__TOMBSTONES_H__)
#define __TOMBSTONES_H__

#include <iostream>
#include <stdlib.h>

template <class T> class Pointer;
template <class T> void free(Pointer<T>& obj);

template <class T> class Tombstone
{
public:
    int refCount;
    T* pointee;

    Tombstone<T>() : pointee(0), refCount(0) {}
    Tombstone<T>(T* ptrIn) : pointee(ptrIn), refCount(1) {}

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

template <class T> class Pointer 
{
private:
    Tombstone<T>* tStone;
public:
    // Default constructor
    Pointer<T>() : tStone()
    {    
        std::cout << "Default Constructor" << std::endl;
    }
    
    // Copy constructor
    Pointer<T>(Pointer<T>& rhs) : tStone(rhs.tStone)
    {        
        std::cout << "Copy Constructor" << std::endl;
        tStone->addRef();
        // std::cout << tStone->refCount << " = " << rhs.tStone->refCount << std::endl;
    }

    // Boostrapping Constructor
    Pointer<T>(T* pVal)
    {
        std::cout << "Boostrapping Constructor" << std::endl;
        tStone = new Tombstone<T>();
        tStone->pointee = pVal;
        tStone->addRef();
        // std::cout << tStone->refCount << std::endl;
    }

    // Destroy a pointer
    ~Pointer<T>()
    {
        std::cout << "Destructor" << std::endl;
        tStone->release();
        // std::cout << tStone->refCount << std::endl;
        if(tStone->refCount <= 0) {
            delete tStone;
        }
    }

    // Dereferencer
    T& operator*() const
    {
        std::cout << "Dereference" << std::endl;
        return *tStone->pointee;
    }

    // Field Dereferencer
    T* operator->() const
    {
        std::cout << "Field Dereferencer" << std::endl;
        return tStone->pointee;
    }

    // Assignment to our pointer
    Pointer<T>& operator=(const Pointer<T>& rhs)
    {   
        std::cout << "Assignment" << std::endl;

        if(tStone->refCount == 0) {
        }
        
        tStone = rhs.tStone;
        tStone->addRef();
        return *this;
    }
    
    // Delete the object that is being pointed at
    friend void free(Pointer<T>& rhs)
    {
        std::cout << "Free" << std::endl;
        std::cout << rhs.tStone->refCount << std::endl;
        
        if(rhs.tStone->refCount == 0 && rhs.tStone) {
            delete rhs.tStone->pointee;
            delete rhs.tStone;
        }

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
        return (number == 0) && (tStone == 0);
        // true iff Pointer is null and int is zero
    }
    
    bool operator!=(const int number) const
    {
        return !(number == 0);
        // false iff Pointer is null and int is zero    
    }
    
    // bool operator==(const int n, const Pointer<T>& t) 
    // { 
    //     return t == n; 
    // }

    // bool operator!=(const int n, const Pointer<T>& t) 
    // {
    //     return t != n; 
    // }
    
};


#endif // __TOMBSTONES_H__
