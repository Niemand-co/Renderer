#include "MemoryManager.h"
#include <stdlib.h>

namespace REngine{

    static const unsigned int k_blockSizes[] = {

        4,  8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48,
        52, 56, 60, 64, 68, 72, 76, 80, 84, 88, 92, 96, 
        
        128, 160, 192, 224, 256, 288, 320, 352, 384, 
        416, 448, 480, 512, 544, 576, 608, 640, 
        
        704, 768, 832, 896, 960, 1024
        
    };

    static const unsigned int k_pageSize = 8192;
    static const unsigned int k_alignment = 4;

    static const unsigned int k_numBlockSizes = sizeof(k_blockSizes) / sizeof(k_blockSizes[0]);

    static const unsigned int k_maxBlockSize = k_blockSizes[k_numBlockSizes - 1];

    static unsigned int* s_blockSizeLookUp = nullptr;
    static Allocator s_allocators[k_numBlockSizes];

    static Allocator* LookUpAllocator(unsigned int size){

        static bool s_initialized = false;

        if(!s_initialized){

            s_blockSizeLookUp = new unsigned int[k_maxBlockSize + 1];
            unsigned int j = 0;
            for(unsigned int i = 0; i <= k_numBlockSizes; ++i){

                if(i > k_blockSizes[j])
                    ++j;

                s_blockSizeLookUp[i] = j;
                
            }

            for(unsigned int i = 0; i < k_numBlockSizes; ++i){

                s_allocators[i].Reset(k_blockSizes[i], k_pageSize, k_alignment);
                
            }

            s_initialized = true;
            
        }

        if(size <= k_maxBlockSize)
            return s_allocators + s_blockSizeLookUp[size];
        else
            return nullptr;
    }

    void* Allocate(unsigned int size){

        Allocator* alloc = LookUpAllocator(size);
        if(alloc)
            return alloc->Allocate();
        else
            return std::malloc(size);
        
    }

    void Free(void* p, unsigned int size){

        Allocator* alloc = LookUpAllocator(size);
        if(alloc)
            alloc->Free(p);
        else
            std::free(p);
        
    }
    
}