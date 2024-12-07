#pragma once

#include <string>
#include <tuple>
#include <vector>

#include <ext/stdio_filebuf.h>
using __gnu_cxx::stdio_filebuf;

#define get_streams(x) \
  __gnu_cxx::stdio_filebuf<char> x##_in_(get<0>(x),std::ios::in);       \
  __gnu_cxx::stdio_filebuf<char> x##_out_(get<1>(x),std::ios::out);     \
  std::istream x##_in(&x##_in_);                                        \
  std::ostream x##_out(&x##_out_)

std::tuple<int,int,pid_t> spawn(const std::vector<std::string>& tokens);
