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

    bool                set(intptr_t inc);
    void*               get() const;
    void*               start() const;
    void*               end() const;

    size_t              size() const;                   // in bytes
    uintptr_t           limit() const;                  // in bytes

    bool                ok() const;

private:
    uintmax_t*          brk_;
    uintmax_t*          start_;
    uintmax_t*          end_;

    uintptr_t           limit_;

    const memory::info& meminfo_;

    bool                ok_;
};

}

#endif /* end of include guard: KERNEL_KHEAP_H */
