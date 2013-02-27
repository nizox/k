#include "video.h"
#include "allocator.h"

#include "c/string.h"

//
// allocator class
//

allocator::allocator(kheap::brk& brk)
    : brk_(brk), wide_chunk_(0)
{ }

allocator::~allocator()
{}

void*
allocator::malloc(size_t size)
{
    size_t      chk_size = this->chunk_size(size);
    chunk*      chk;

    if (!chk_size)
        return 0;

    if (chk_size <= small_chunk_size)
        chk = bins_.pop(chk_size);
    else
        chk = large_chunks_.pop(chk_size);

    if (!chk)
      {
        if ((chk = this->get_new_chunk(chk_size)) == 0)
            return 0;
      }

    return (void *)(chk + 1);
}

void*
allocator::realloc(void* ptr, size_t size)
{
    chunk*      chk = ((chunk*)ptr) - 1;

    if (chk->size >= size)
        return ptr;

    void*       tmp = this->malloc(size);

    if (tmp != 0)
        ::memcpy(tmp, ptr, chk->size);

    this->free(ptr);
    return tmp;
}

void*
allocator::calloc(size_t num, size_t size)
{
    void*       ptr = malloc(num * size);

    if (ptr)
        return ::memset(ptr, 0, num * size);
    return ptr;
}

void
allocator::free(void *ptr)
{
    chunk*      chk = ((chunk*)ptr) - 1;

    if (ptr < brk_.start() || ptr >= brk_.end())
      {
        video   screen;
        video::attribute error(video::red, video::black);

        screen << error << "Invalid pointer passed to free: " << ptr << std::endl;
      }

    if (chk->size <= small_chunk_size)
        bins_.push(chk);
    else
        large_chunks_.push(chk);
}

allocator::return_type
allocator::get(size_t size)
{
    return return_type(*this, size);
}

inline size_t
allocator::chunk_size(size_t size) const
{
    return size / chunk_header_size * chunk_header_size
        + (size % chunk_header_size ? chunk_header_size : 0);
}

allocator::chunk*
allocator::get_new_chunk(size_t size)
{
    chunk*      chk;

    if ((chk = this->trim_wide_chunk(size)) != 0)
        return chk;

    size_t      req_size = size;

    if (wide_chunk_ != 0)
        req_size -= wide_chunk_->size;

    // current chunk header
    req_size += chunk_header_size;

    req_size = this->page_number(req_size) * brk_.info().page_size;

    if (!brk_.set(req_size))
        return 0;

    chunk*       tmp = (chunk*)brk_.get();

    if (wide_chunk_ != 0)
        wide_chunk_->size += req_size;
    else
      {
        wide_chunk_ = tmp;
        wide_chunk_->size = req_size;
      }

    return this->trim_wide_chunk(size);
}

allocator::chunk*
allocator::trim_wide_chunk(size_t size)
{
    if (wide_chunk_ != 0 && wide_chunk_->size >= size)
      {
        chunk*      chk = wide_chunk_;

        if (wide_chunk_->size == size)
            wide_chunk_ = 0;
        else if (wide_chunk_->size > size)
          {
            wide_chunk_ = (chunk*)(((uintptr_t)wide_chunk_) + chunk_header_size + size);
            wide_chunk_->size = chk->size - size;
          }

        chk->size = size;
        return chk;
      }

    return 0;
}

inline size_t
allocator::page_number(size_t size)
{
    size_t      page_size = brk_.info().page_size;

    return size / page_size * page_size + size % page_size != 0;
}

//
// bins class
//

allocator::bins::bins()
{
    ::memset(bins_, 0, sizeof(bins_));
}

allocator::bins::~bins()
{}

inline size_t
allocator::bins::index(size_t size) const
{
    return size / chunk_header_size - 1;
}

void
allocator::bins::push(chunk* chk)
{
    size_t      idx = index(chk->size);

    chk->next = bins_[idx];
    bins_[idx] = chk;
}

allocator::chunk*
allocator::bins::pop(size_t size)
{
    size_t      i;

    for (i = index(size); i < number; ++i)
      {
        if (bins_[i] != 0)
          {
            video screen;

            chunk*  chk = bins_[i];
            screen.printf("index: %d\n", i);
            screen.printf("chunk: %p\n", chk);
            bins_[i] = chk->next;
            return chk;
          }
      }
    return 0;
}

//
// large_chunks class
//

allocator::large_chunks::large_chunks()
    : large_chunks_(0)
{}

allocator::large_chunks::~large_chunks()
{}

void
allocator::large_chunks::push(chunk* chk)
{
    chk->next = large_chunks_;
    large_chunks_ = chk;
}

allocator::chunk*
allocator::large_chunks::pop(size_t size)
{
    chunk*      chk = large_chunks_;
    chunk*      prev = 0;

    while (chk != 0)
      {
        if (chk->size >= size)
          {
            if (!prev)
                large_chunks_ = chk->next;
            else
                prev->next = chk->next;
            return chk;
          }

        prev = chk;
        chk = chk->next;
      }
    return 0;
}
