#pragma once
#ifndef VECTOR_N5KHI9IQ
#define VECTOR_N5KHI9IQ

#include "c/types.h"
#include "c/string.h"

#include "cplusplus.h"
#include "allocator.h"

namespace kl {
    
namespace defail {
    
template <typename T, size_t default_size>
class vector
{
 public:

  using iterator = T*;
  using const_iterator = T const *;
  using size_type = size_t;
  using value_type = T;
  using pointer = T*;
  using const_pointer = T *const;

  vector()
      : vec{nullptr}
      , size{0}
      , alloc_size{0}
      , A{*global_allocator::get_allocator()}
  {
      vec = (pointer)A.malloc(default_size * sizeof(T));
      alloc_size = default_size;
  }

  void
  push_back(T const &val)
  {
      if (this->size < this->alloc_size)
      {
          this->vec[this->size] = val;
          this->size += 1;
      } 
      else
      {
          int err;

          this->resize(default_size);
          this->vec[this->size] = val;
          this->size += 1;
      }
  }

  void
  resize(size_t size)
  {
      size_t next_alloc_size;
      T *tmpptr;

      /*check for overflow*/
      if (((this->alloc_size + size) * sizeof(T)) < this->alloc_size)
      {
          next_alloc_size = default_size;
      }
      else
      {
          next_alloc_size = (this->alloc_size + size) * sizeof(T);
      }
      tmpptr = (pointer)A.realloc(this->vec, next_alloc_size);
      if (tmpptr != nullptr)
      {
          this->vec = tmpptr;
          this->alloc_size = next_alloc_size / sizeof(T);
      }
      return ;
  }

  void
  pop_back()
  {
      T *it = &this->vec[this->size - 1];
      this->erase(it);
  }

  T const &
  back()
  {
      if (this->size != 0)
          return this->vec[this->size - 1];
      else
          return this->vec[0];
  }

  void
  erase(T *it)
  {
      if (it > (this->vec + this->size))
      {
          return ;
      }
      else
      {
          size_t n = 0;

          T *dest = it;
          T *src = it + 1;
          n = (uintptr_t)&this->vec[this->size] - (uintptr_t)src;
          memmove(dest, src, n);
          this->size--;
      }
  }

  bool
  empty() const
  {
      return this->size > 0 ? false : true;
  }

  iterator
  begin() const
  { return &this->vec[0]; }

  iterator
  end() const
  { return &this->vec[this->size]; }

  const_iterator
  cbegin() const
  { return &this->vec[0]; }

  const_iterator
  cend() const
  { return &this->vec[this->size]; }

  ~vector()
  {
      delete vec;
  }
 private:
  T*        vec;
  size_t    size;
  size_t    alloc_size;
  allocator& A;
};

} /* _defail */

template <typename T>
using vector = defail::vector<T, 64>;

} /* kl */


#endif /* end of include guard: VECTOR_N5KHI9IQ */
