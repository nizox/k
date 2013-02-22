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

    size_t              size() const;
    size_t              limit() const;

    bool                ok() const;

private:
    uintptr_t*          brk_;
    uintptr_t*          start_;
    uintptr_t*          end_;

    size_t              size_;
    size_t              limit_;

    const memory::info& meminfo_;

    bool                ok_;
};

}

#endif /* end of include guard: KERNEL_KHEAP_H */
