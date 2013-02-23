#ifndef KERNEL_KHEAP_H
#define KERNEL_KHEAP_H

#include "c/types.h"
#include "c/memory.h"

#include "memory.h"

namespace kheap
{

class brk
{
public:
    brk(const memory::info& meminfo);
    ~brk();

    uintptr_t*          get() const;
    bool                set(intptr_t inc);

    uintptr_t           size() const;                   // in bytes
    uintptr_t           limit() const;                  // in bytes
    uintptr_t*          end() const { return end_; }

    bool                ok() const;

private:
    uintptr_t*          brk_;
    uintptr_t*          start_;
    uintptr_t*          end_;

    uintptr_t           size_;
    uintptr_t           limit_;

    const memory::info& meminfo_;

    bool                ok_;
};

}

#endif /* end of include guard: KERNEL_KHEAP_H */
