#include "Allocator.h"
#include <math.h>
#include <cstring>

namespace REngine{

    template<typename T>
    T Max(T a, T b){
        return a > b ? a : b;
    }

    Allocator::Allocator(unsigned int dataSize, unsigned int pageSize, unsigned int alignment)
     : m_pageList(nullptr), m_freeList(nullptr){

        Reset(dataSize, pageSize, alignment);

    }

    Allocator::~Allocator(){

        FreeAll();
        
    }

    void Allocator::Reset(unsigned int dataSize, unsigned int pageSize, unsigned int alignment){

        m_dataSize = dataSize;
        m_pageSize = pageSize;

        unsigned int maxHeaderSize = Max(static_cast<unsigned>(sizeof(BlockHeader)), m_dataSize);
        
        m_alignmentSize = (maxHeaderSize % alignment) ? (alignment - maxHeaderSize % alignment) : 0;

        m_blockSize = maxHeaderSize + m_alignmentSize;

        m_blockPerPage = (m_pageSize - sizeof(PageHeader)) / m_blockSize; 

    }

    void* Allocator::Allocate(){

        if(!m_freeList){

            PageHeader* newPage = reinterpret_cast<PageHeader*>(new char[m_pageSize]);
            ++m_numPages;
            m_numBlocks += m_blockPerPage;
            m_numFreeBlocks += m_blockPerPage;

            if(m_pageList)newPage->next = m_pageList;
            m_pageList = newPage;

            BlockHeader* curBlock = newPage->Blocks();
            for(unsigned int i = 0; i < m_blockPerPage - 1; ++i){

                curBlock->next = NextBlock(curBlock);
                curBlock = NextBlock(curBlock);
                
            }
            curBlock->next = nullptr;

            m_freeList = newPage->Blocks();
            
        }

        BlockHeader* freeBlock = m_freeList;
        m_freeList = m_freeList->next;
        --m_numFreeBlocks;

        return freeBlock;
        
    }

    void Allocator::Free(void* p){

        BlockHeader* block = reinterpret_cast<BlockHeader*>(p);

        FillFreeBlock(block);

        block->next = m_freeList;
        m_freeList = block;
        ++m_numFreeBlocks;
        
    }

    void Allocator::FreeAll(){

        PageHeader* pageWalker = m_pageList;
        while(pageWalker){

            PageHeader* curPage = pageWalker;
            pageWalker = pageWalker->next;

            delete[] reinterpret_cast<char*>(curPage);
            
        }

        m_pageList = nullptr;
        m_freeList = nullptr;

        m_numPages = 0;
        m_numBlocks = 0;
        m_numFreeBlocks = 0;
        
    }

    void Allocator::FillFreePage(PageHeader* p){

        p->next = nullptr;

        BlockHeader* curBlock = p->Blocks();
        for(unsigned int i = 0; i < m_blockPerPage; ++i){

            FillFreeBlock(curBlock);
            curBlock = NextBlock(curBlock);
            
        }
        
    }

    void Allocator::FillFreeBlock(BlockHeader* p){

        std::memset(p, PATTERN_FREE, m_blockSize - m_alignmentSize);

        std::memset(reinterpret_cast<char*>(p) + m_blockSize - m_alignmentSize, PATTERN_ALIGN, m_alignmentSize);
        
    }

    void Allocator::FillAllocateBlock(BlockHeader* p){

        std::memset(p, PATTERN_ALLOC, m_blockSize - m_alignmentSize);

        std::memset(reinterpret_cast<char*>(p) + m_blockSize - m_alignmentSize, PATTERN_ALIGN, m_alignmentSize);
        
    }

    Allocator::BlockHeader* Allocator::NextBlock(BlockHeader* p){

        return reinterpret_cast<BlockHeader*>(reinterpret_cast<char*>(p) + m_blockSize);
        
    }
    
}