#pragma once
#ifndef UTILITY_SH1B6N55
#define UTILITY_SH1B6N55

template <typename T>
T && move(T &&t)
{
    return static_cast<T &&>(t);
}

template <typename T>
T&& forward(T &&t)
{
    return static_cast<T &&>(t);
}

#endif /* end of include guard: UTILITY_SH1B6N55 */
