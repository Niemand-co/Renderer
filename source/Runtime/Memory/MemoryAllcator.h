#include "MemoryManager.h"

namespace REngine{

    template<typename T>
    T* New(){

        return new (Allocate(sizeof(T))) T();

    }

    template<typename T, typename A0>
    T* New(A0 a0){

        return new (Allocate(sizeof(T))) T(a0);
        
    }

    template<typename T, typename A0, typename A1>
    T* New(A0 a0, A1 a1){

        return new (Allocate(sizeof(T))) T(a0, a1);
        
    }

    template<typename T>
    void Delete(T* p){

        reinterpret_cast<T*>(p);
        Free(p, sizeof(T));
        
    }
    
}