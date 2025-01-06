#pragma once

#include <stack>

template<class Base, class T, int d>
struct Reverse_Swapper
{
  Base& base;
  std::stack<T>& indexes;
  Reverse_Swapper<Base,T,d-1> nextR;
  
  Reverse_Swapper(Base& base_, std::stack<T>& indexes_) : base(base_), indexes(indexes_), nextR(base_,indexes_) { }
  auto& apply_indexes()
    {
      auto& to_return = nextR.apply_indexes()[indexes.top()];
      indexes.pop();
      return to_return;
    }
};

template<class Base, class T>
struct Reverse_Swapper<Base,T,1>
{
  Base& base;
  std::stack<T>& indexes;
  Reverse_Swapper(Base& base_, std::stack<T>& indexes_) : base(base_), indexes(indexes_) { }
  auto& apply_indexes()
    {
      auto& to_return = base[indexes.top()];
      indexes.pop();
      return to_return;
    }
};

template<class Base, class T, int d, int max=d>
struct Array_Index_Swapper
{
  Base& base;
  std::stack<T>& indexes;
  Array_Index_Swapper<Base,T,d-1,max> nextD;

  Array_Index_Swapper(Base& base_, std::stack<T>& indexes_) : base(base_), indexes(indexes_), nextD(base_, indexes_) { }
  
  auto& operator[](T x)
    {
      indexes.push(x);
      return nextD;
    }
};

template<class Base, class T, int max>
struct Array_Index_Swapper<Base,T,1,max>
{
  Base& base;
  std::stack<T>& indexes;
  Array_Index_Swapper(Base& base_, std::stack<T>& indexes_) : base(base_), indexes(indexes_) { }
  auto& operator[](T x) {
    indexes.push(x);
    return Reverse_Swapper<Base,T,max>(base,indexes).apply_indexes();
  }
};
