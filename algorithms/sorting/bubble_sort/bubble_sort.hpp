#ifndef __BUBBLE_SORT_HPP__
#define __BUBBLE_SORT_HPP__

#include <type_traits>

namespace dsa
{

template <typename Itr, typename Comp = std::less<typename std::iterator_traits<Itr>::value_type>>
void
bubble_sort(Itr first, Itr last, Comp comp = Comp())
{
  do
    {
      bool is_swapped__ = false;

      for(auto prev = first, curr = std::next(first); curr != last; ++curr, ++prev)
        {
          if(comp(*curr, *prev))
            {
              std::iter_swap(prev, curr);
              is_swapped__ = true;
            }
        }

      if(!is_swapped__)
        break;
    }
  while(true);
};

} // namespace dsa

#endif