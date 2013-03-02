#pragma once
#ifndef FUNCTION_BF3ML3EI
#define FUNCTION_BF3ML3EI

#include "utility.h"

namespace kl {
    
namespace detail {

template <typename Hold>
struct holder
{
  holder(Hold _h) : h(_h){}
  Hold h;
};

template <typename callable, typename return_type, typename ...types_args>
return_type caller(void *_holder, types_args && ... args)
{
  holder<callable>* h = reinterpret_cast<holder<callable>*>(_holder);

  return h->h(kl::forward<types_args>(args)...);
}

template <typename callable, typename ...types_args>
void void_caller(void *_holder, types_args && ... args)
{
  holder<callable>* h = reinterpret_cast<holder<callable>*>(_holder);

  h->h(kl::forward<types_args>(args)...);
}
} /* detail */

template <typename Sign>
struct function;

template <typename return_type, typename ...args_types>
struct function<return_type (args_types...)>
{
  typedef return_type sign_type(args_types...);
  typedef return_type caller_type(void *, args_types && ...);

  function()
      : _holder{nullptr}
      , _caller{nullptr}
  {
  }

  template <typename callable>
  function(callable &&c)
  {
    this->_holder = new detail::holder<callable>{kl::forward(c)};
    this->_caller = &detail::caller<callable, return_type, args_types && ...>;
  }

  template <typename callable>
  function &operator = (callable &&c)
  {
    this->_holder = new detail::holder<callable>{kl::forward(c)};
    this->_caller = &detail::caller<callable, return_type, args_types && ...>;
    return *this;
  }

  return_type operator()(args_types && ... args) const
  {
    return this->_caller(this->_holder, kl::forward<args_types>(args)...);
  }

  ~function()
  {
      if (_holder != nullptr)
          delete  (detail::holder *)_holder;
  }

 private:
  void *_holder;
  caller_type *_caller;
};

template <typename ...args_types>
struct function<void (args_types...)>
{
  typedef void sign_type(args_types...);
  typedef void caller_type(void *, args_types && ...);

  function()
      : _holder{nullptr}
      , _caller{nullptr}
  {
  }

  template <typename callable>
  function(callable &&c)
  {
    this->_holder = new detail::holder<callable>{kl::forward(c)};
    this->_caller = &detail::void_caller<callable, args_types && ...>;
  }

  template <typename callable>
  function &operator = (callable &&c)
  {
    this->_holder = new detail::holder<callable>{kl::forward(c)};
    this->_caller = &detail::caller<callable, args_types && ...>;
    return *this;
  }

  void operator()(args_types && ... args) const
  {
    this->_caller(this->_holder, kl::forward<args_types>(args)...);
  }

  ~function()
  {
      if (_holder != nullptr)
          delete  (detail::holder *)_holder;
  }

 private:
  void *_holder;
  caller_type *_caller;
};

} /* kl */

#endif /* end of include guard: FUNCTION_BF3ML3EI */
