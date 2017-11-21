/////////////////////////////////////////////////////////////////////////////
// tombstones.h, expected interface for CSC254 assignment 5
/////////////////////////////////////////////////////////////////////////////

#if !defined(__TOMBSTONES_H__)
#define __TOMBSTONES_H__

#include <iostream>
#include <stdlib.h>

template <class T> class Pointer;
template <class T> void free(Pointer<T>& obj);

template <class T> class Pointer {
private:
  T* tStone;
  int refCount;
public:

    // Default constructor
    Pointer<T>() : tStone(0)
    {    
        // std::cout << "Default Constructor: " << this << std::endl;
        refCount = 0;
    }
    
    // Copy constructor
    Pointer<T>(Pointer<T>& rhs)
    {
        // std::cout << "Copy Constructor: " << this << std::endl;
        tStone = rhs.tStone;
        refCount = 0;
        refCount++;
    }

    // Boostrapping Constructor
    Pointer<T>(T* pVal)
    {
        // std::cout << "Boostrapping Constructor: " << this << std::endl;
        tStone = pVal;
        refCount = 0;
    }

    // Destroy a pointer
    ~Pointer<T>()
    {
        refCount--;
        // std::cout << "Destruction: " << this << " Reference Count: " << refCount << std::endl;
    }

    // Dereferencer
    T& operator*() const
    {
        return *tStone;
    }

    // Field Dereferencer
    T* operator->() const
    {
        return tStone;
    }

    // Assignment to our pointer
    Pointer<T>& operator=(const Pointer<T>& rhs)
    {   
        // std::cout << "ASSIGNMENT " << std::endl;
        // std::cout << this << " = to " << &rhs << std::endl;        
        refCount++;
        tStone = rhs.tStone;
        // std::cout << this << " = to " << &rhs << std::endl;
        
        return *this;
    }
    
    // Delete the object that is being pointed at
    friend void free(Pointer<T>& ptr)
    {
        ptr.tStone = 0;
        if(ptr.tStone != 0) {
            free(&*ptr);    
        } else {
            std::cout << "Throw an error" << std::endl;
        }
    }
    
    bool operator==(const Pointer<T>& ptrIn) const
    {
        if(ptrIn.tStone == tStone) {
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
