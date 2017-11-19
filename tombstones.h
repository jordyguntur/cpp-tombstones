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
  T** ptStone;
public:

    // Default constructor
    Pointer<T>() : tStone(0), ptStone(0) {}
    
    // Copy constructor
    Pointer<T>(Pointer<T>& rhs) : tStone(rhs.tStone), ptStone(rhs.ptStone) {}

    // Boostrapping Constructor
    Pointer<T>(T* pVal)
    {
        // std::cout << "MERP: " << pVal << std::endl;
        tStone = pVal;      // Tombstone contains the address of the object
        ptStone = &tStone;  // Pointer contains the address of the tombstone    
    }

    // Destroy a pointer
    ~Pointer<T>()
    {
        delete tStone;
        
    }

    // Dereferencer
    T& operator*() const
    {
        return *tStone;
    }

    // Field Dereferecer
    T* operator->() const
    {
        return tStone;
    }

    // Assignment to our pointer
    Pointer<T>& operator=(const Pointer<T>& rhs)
    {
        // Self Assignment Check
        if(this == &rhs) {
            return *this;
        }
        
        tStone = rhs.tStone;
        ptStone = rhs.ptStone;

        return *this;
    }

    // Delete the object that is being pointed at
    friend void free(Pointer<T>&);
    
    bool operator==(const Pointer<T>&) const;
    bool operator!=(const Pointer<T>&) const;
    bool operator==(const int) const;
    
    // true iff Pointer is null and int is zero
    bool operator!=(const int) const;
    // false iff Pointer is null and int is zero
};


#endif // __TOMBSTONES_H__
