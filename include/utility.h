#pragma once
#ifndef UTILITY_2542WB4P
#define UTILITY_2542WB4P

namespace kl {

template <typename T>
T &&
forward(T &&t)
{
    return static_cast<T &&>(t);
}

template <typename T>
T &&
move(T &&t)
{
    return static_cast<T &&>(t);
}

} /* kl */


#endif /* end of include guard: UTILITY_2542WB4P */
