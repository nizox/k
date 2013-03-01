#ifndef KERNEL_MEMORY_H_
#define KERNEL_MEMORY_H_

#include "c/memory.h"
#include "c/types.h"

namespace memory
{

#define get_set_bit(name, number)           \
bool        name () const                   \
{ return this->get_bit(number); }           \
                                            \
void        name (bool flag)                \
{                                           \
    this->set_bit(number, flag);            \
}

//
// Base Pagination entry for 2MiB pages
//
struct __attribute__((packed)) base_entry
{
    uint64_t            raw;        // raw form of the entry

    get_set_bit(p,	    0)          // page/table is present in physical address
    get_set_bit(rw,	    1)          // page/table in accessible in read or write
    get_set_bit(us,	    2)          // page/table has a user privillege
    get_set_bit(pwt,	3)          // cache write-back or write-through
    get_set_bit(pcd,	4)          // is cacheable
    get_set_bit(a,	    5)          // page/table is access (read and/or write)
    get_set_bit(ign,	6)          // ignored bit (pml4e/pdpe)
    get_set_bit(d,	    6)          // dirty page, has been written (pde)
    get_set_bit(ps,	    7)          // PDE.PS=1 means 2MiB pages (pdpe), else emans 4KiB (pde)
    get_set_bit(g,	    8)          // keep page in cache when modifying cr3 (pde)
    get_set_bit(pat,	12)         // Page attribute (pde)
    get_set_bit(nx,	    63)         // page/table not executable

    bool                get_bit(size_t number) const
      { return raw & (1 << number); }

    void                set_bit(size_t number, bool flag)
      {
        COND_SET_BIT(raw, flag, 1 << number);
      }

    uint64_t*           base_addr() const
      {
        uint64_t        copy = raw;

        copy >>= 12;
        copy <<= 12 + 12;
        copy >>= 12;
        return (uint64_t*)copy;
      }
};

typedef base_entry pml4_entry;
typedef base_entry pdp_entry;
typedef base_entry pd_entry;

#define PML4_SIZE   PURE64_PML4_SIZE;
#define PDP_SIZE    PURE64_PDP_SIZE;
#define PD_SIZE     PURE64_PD_SIZE;

pml4_entry* const   pml4 = (pml4_entry *)PURE64_PML4;
pdp_entry* const    pdp = (pdp_entry *)PURE64_PDP;
pd_entry* const     pd = (pd_entry *)PURE64_PD;

struct info
{
    /*
     * amount       -- (size_t) amount of memory in bytes
     * page_size    -- (size_t) size of a page in bytes
     * pml4         -- (pml4_entry *) pointer value to the PML4 table
     * pdp          -- (pdp_entry *) pointer value to the PDP table
     * pd           -- (pd_entry *) pointer value to the PD table
     */
    info(size_t amount, size_t page_size, pml4_entry *pml4, pdp_entry* pdp, pd_entry *pd);
    ~info();

    size_t      pages() const;

    size_t      amount;
    size_t      page_size;
    pml4_entry* pml4;
    pdp_entry*  pdp;
    pd_entry*   pd;
};

}

#endif /* end of include guard: KERNEL_MEMORY_H_ */
