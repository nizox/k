#include "kheap.h"
#include "memory.h"
#include "video.h"

#include "c/print.h"
#include "c/types.h"

namespace kheap
{

brk::brk(const memory::info& meminfo)
    : brk_(0), meminfo_(meminfo), ok_(false)
{
    video::attribute    error(video::red, video::black);
    video               screen;
    size_t              i;
    size_t              pages = meminfo_.pages();

    /*
     * Find the first available memory page
     * works in case of identity mapping under 4GiB
     */
    for (i = 0; i < pages; ++i)
      {
        if (meminfo_.pd[i].p() && !meminfo_.pd[i].d())
            break;
      }

    if (i >= pages)
        screen << error << "Error: no clean page available" << std::endl;
    else
      {
        ok_ = true;
        start_ = meminfo_.pd[i].base_addr();
        brk_ = start_;
        limit_ = ((pages - i) / 2) * (meminfo.page_size);   // Kernel heap is half the available cleared memory
        end_ = (uintmax_t *)((uintmax_t)start_ + limit_);   // Double cast needed to get proper pointer values
      }
}

brk::~brk()
{}

bool
brk::set(intptr_t inc)
{
    uintptr_t*  save = brk_;

    brk_ = (uintmax_t*)((uintmax_t)brk_ + inc);
    if (brk_ < start_ || brk_ > end_) {
          brk_ = save;
          return false;
    }

    return true;
}

void*
brk::get() const
{ return static_cast<void*>(brk_); }

void*
brk::start() const
{ return start_; }

void*
brk::end() const
{ return end_; }

size_t
brk::size() const
{ return (size_t)(uintptr_t)brk_ - (uintptr_t)start_; }

uintptr_t
brk::limit() const
{ return (uintptr_t)limit_; }

bool
brk::ok() const
{ return ok_; }

}
