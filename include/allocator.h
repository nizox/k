#ifndef KERNEL_ALLOCATOR_H_
#define KERNEL_ALLOCATOR_H_

#include "c/kernel.h"
#include "c/types.h"
#include "c/memory.h"

#include "kheap.h"
#include "memory.h"

#include "video.h"

//
// Simple allocator based on the Doug Lea's malloc architecture.
//
// +-----------------------------------------------------------+
// | BINS |      LARGE_CHUNKS     |   WIDE_CHUNK               |
// +-----------------------------------------------------------+
//
// BINS is a table of lists of small chunks, access is O(1) in the best
// case and amortized in the worst case. The definition of small chunks
// depends on ``small_chunk_size''.
//
// LARGE_CHUNKS is, for the moment, implemented as a sigle linked
// list and keeps a track of chunks larger thant ``small_chunk_size''.
// A better implementation (heap, rbt, b-tree etc.) is possible
// in the future.
//
// The WIDE_CHUNK is the chunk containing the rest of the memory
// available to the allocator. This chunk is not to be returned by iself
// and serves as a reserve for later chunk requests.
//
// The allocator supposes it is the only one protagonist to make
// use of the given heap (in that case: the kernel heap). No external
// call to the heap should be made.
//
// TODO: test the allocator
// TODO: check and mark if the pointer is already free in allocator::free
// TODO: implement a better large chunks management (optional)
// TODO: implement merge and split (optional)

class allocator
{
public:

    // C++ trick base on cast operator to infer return type of a function
    class return_type
      {
    public:
        return_type(allocator& alloc, size_t size): alloc_(alloc), size_(size) {}
        template <typename T>
            operator T*()
              {
                return static_cast<T*>(alloc_.malloc(sizeof(T) * size_));
              }

    private:
        allocator&      alloc_;
        size_t          size_;
      };

    allocator(kheap::brk& brk);
    ~allocator();

    void*               malloc(size_t size);
    void*               realloc(void* ptr, size_t size);
    void*               calloc(size_t num, size_t size);

    void                free(void *ptr);

    return_type         get(size_t size = 1);

    template <typename T> bool
                        resize(T*& ptr, size_t size)
      {
        ptr = static_cast<T*>(realloc(ptr, size));
        if (!ptr)
            return false;
        return true;
      }

    template <typename T> void
                        release(T *ptr)
      {
        this->free(static_cast<void *>(ptr));
      }

private:

    struct __attribute__((packed)) chunk
      {
        uint64_t            size;
        chunk*              next;
      };

    static const uint16_t   small_chunk_size = 512;
    static const uint8_t    chunk_header_size = sizeof(chunk);
    static const uint8_t    chunk_min_size = chunk_header_size * 2;

    class bins
      {
    public:
        bins();
        ~bins();

        static const uint8_t    number = small_chunk_size / chunk_header_size;

        size_t                  index(size_t size) const;

        void                    push(chunk* chk);
        chunk*                  pop(size_t size);

    private:
        chunk*                  bins_[bins::number];
      };

    class large_chunks
      {
    public:
        large_chunks();
        ~large_chunks();

        void                    push(chunk* chk);
        chunk*                  pop(size_t size);

    private:
        chunk*                  large_chunks_;
      };

    kheap::brk&             brk_;
    chunk*                  wide_chunk_;
    large_chunks            large_chunks_;
    bins                    bins_;

    size_t              chunk_size(size_t size) const;
    chunk*              get_new_chunk(size_t size);
    chunk*              trim_wide_chunk(size_t size);
    size_t              page_number(size_t size);

};

#endif /* end of include guard: KERNEL_ALLOCATOR_H_ */
