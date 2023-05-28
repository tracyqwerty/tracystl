#ifndef _TRACYSTL_DEQUE_H_
#define _TRACYSTL_DEQUE_H_
#include "allocator.h"

namespace tracystl {

#ifndef DEQUE_MAP_INIT_SIZE
#define DEQUE_MAP_INIT_SIZE 8
#endif

template <class T> struct deque_buf_size {
  // value must >= 16
  static constexpr size_t value = sizeof(T) < 256 ? 4096 / sizeof(T) : 16;
};
template <class T> class Deque {
public:
  // they don't depend on a nested type. It is already clear to the compiler
  // that tracystl::allocator<T *> is a type, so typename is not required in
  // this context.
  typedef tracystl::allocator<T> allocator_type;
  typedef tracystl::allocator<T> data_allocator;
  typedef tracystl::allocator<T *> map_allocator;

  typedef typename allocator_type::value_type value_type;
  typedef typename allocator_type::pointer pointer;
  typedef typename allocator_type::const_pointer const_pointer;
  typedef typename allocator_type::reference reference;
  typedef typename allocator_type::const_reference const_reference;
  typedef typename allocator_type::size_type size_type;
  typedef typename allocator_type::difference_type difference_type;
  typedef pointer *map_pointer;
  typedef const_pointer *const_map_pointer;
};

} // namespace tracystl
#endif // !_TRACYSTL_DEQUE_H_