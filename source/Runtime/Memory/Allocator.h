#ifndef RENGINE_ALLOCATOR_H
#define RENGINE_ALLOCATOR_H

#include "Foundation/BuildType.h"

namespace REngine{

    

    class Allocator{

    public:

        struct BlockHeader{

            BlockHeader* next;
        
        };

        struct PageHeader{

            PageHeader* next;

            BlockHeader *Blocks(void){
                return reinterpret_cast<BlockHeader*>(this + 1);
            }
            
        };

    public:

        static const unsigned char PATTERN_ALIGN = 0xFC;
        static const unsigned char PATTERN_ALLOC = 0xFD;
        static const unsigned char PATTERN_FREE  = 0xFE;

        Allocator(unsigned int dataSize, unsigned int pageSize, unsigned int alignment);

        ~Allocator();

        void Reset(unsigned int dataSize, unsigned int pageSize, unsigned int alignment);

        void* Allocate();

        void Free(void* p);

        void FreeAll();

    private:

        void FillFreePage(PageHeader* p);

        void FillFreeBlock(BlockHeader* p);

        void FillAllocateBlock(BlockHeader* p);

        BlockHeader* NextBlock(BlockHeader* p);

    private:

        PageHeader* m_pageList;
        BlockHeader* m_freeList;

        unsigned int m_dataSize;
        unsigned int m_pageSize;
        unsigned int m_alignmentSize;
        unsigned int m_blockSize;
        unsigned int m_blockPerPage;

        unsigned int m_numPages;
        unsigned int m_numBlocks;
        unsigned int m_numFreeBlocks;

        Allocator(const Allocator& clone);
        Allocator &operator=(const Allocator& rhs);

    };

}

#endif
        