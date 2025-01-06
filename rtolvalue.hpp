#pragma once

#include <type_traits>

//From this StackOverflow post: https://stackoverflow.com/questions/41906213/how-can-i-take-the-address-of-a-temporary-rvalue-for-copying

template<typename T>
std::remove_reference_t<T>& rtolvalue(std::remove_reference_t<T> &&t)
{
  return static_cast<std::remove_reference_t<T> &>(t);
}
