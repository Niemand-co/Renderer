#ifndef RENGINE_MEMORYMANAGER_H
#define RENGINE_MEMORYMANAGER_H

#include "Allocator.h"

namespace REngine{

    void* Allocate(unsigned int size);

    void Free(void* p, unsigned int size);
    
}

#endif