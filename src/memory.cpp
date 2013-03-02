#include "memory.h"

#include "c/types.h"

namespace memory
{

info::info(size_t amount, size_t page_size, pml4_entry *pml4, pdp_entry* pdp, pd_entry *pd)
    : amount(amount), page_size(page_size), pml4(pml4), pdp(pdp), pd(pd)
{}

info::~info()
{
}

size_t
info::pages() const
{
    return amount / page_size;
}

}
