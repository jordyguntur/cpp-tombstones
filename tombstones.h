/////////////////////////////////////////////////////////////////////////////
// tombstones.h, expected interface for CSC254 assignment 5
/////////////////////////////////////////////////////////////////////////////

#if !defined(__TOMBSTONES_H__)
#define __TOMBSTONES_H__

template <class T> class Pointer;
template <class T> void free(Pointer<T>& obj);

template <class T> class Pointer {
private:
  T*  pData;
public:

    // Default constructor, set to null
    Pointer<T>() : pData(nullptr) {}
    
    // Constructor to copy pointer
    Pointer<T>(Pointer<T>& rhs) 
    {
        // Transfer rhs to pData
        pData = rhs.pData;

        // Set rhs to 0
        // {Question} Is there another way to delete rhs?
        rhs.pData = 0;
    }

    // Constructor for a pointer to object
    Pointer<T>(T* pVal) : pData(pVal) {}

    // Destroy a pointer
    ~Pointer<T>()
    {
        delete pData;
    }

    // Dereferencer
    T& operator*() const
    {
        return *pData;
    }

    // Field Dereferecer
    T* operator->() const
    {
        return pData;
    }

    // Assignment to our pointer
    Pointer<T>& operator=(const Pointer<T>& rhs)
    {
        if(this == &rhs) {
            return *this;
        }

        delete pData;

        pData = rhs.pData;
        rhs.pData = 0;

        return *this;
    }

    // Delete the object that is being pointed at
    friend void free<T>(Pointer<T>& rhs)
    {
        
    }


    bool operator==(const Pointer<T>&) const;
    bool operator!=(const Pointer<T>&) const;
    bool operator==(const int) const;
    
    // true iff Pointer is null and int is zero
    bool operator!=(const int) const;
    // false iff Pointer is null and int is zero
};


#endif // __TOMBSTONES_H__
