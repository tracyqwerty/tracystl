#ifndef _TRACYSTL_VECTOR_H_
#define _TRACYSTL_VECTOR_H_

#include "allocator.h"
#include "iterator.h"
// #include <cstddef> // For std::size_t
// #include <memory>  // For std::allocator

namespace tracystl {

template <class T>
class Vector {
 public:
  typedef T value_type;
  typedef value_type* iterator;
  typedef const value_type* const_iterator;

 private:
  iterator start_;
  iterator finish_;
  iterator end_of_storage_;

 public:
  Vector() : start_(0), finish_(0), end_of_storage_(0) {}
  ~Vector() {
    clear();
    Allocator<value_type>::deallocate(start_);
  }

  iterator begin() { return start_; }
  const_iterator begin() const { return start_; }

  iterator end() { return finish_; }
  const_iterator end() const { return finish_; }

  size_t size() const { return size_t(end() - begin()); }
  size_t capacity() const { return size_t(end_of_storage_ - begin()); }

  bool empty() const { return begin() == end(); }

  value_type& operator[](size_t n) { return *(begin() + n); }
  const value_type& operator[](size_t n) const { return *(begin() + n); }

  void clear();

  void push_back(const value_type& value);
};

template <class T>
void Vector<T>::clear() {
  if (start_) {
    Allocator<value_type>::destroy(start_, finish_);
    finish_ = start_;
  }
}

template <class T>
void Vector<T>::push_back(const value_type& value) {
  if (finish_ != end_of_storage_) {
    Allocator<value_type>::construct(finish_, value);
    ++finish_;
  } else {
    // Need to reallocate
    const size_t old_size = size();
    const size_t len = old_size != 0 ? 2 * old_size : 1;

    iterator new_start = Allocator<value_type>::allocate(len);
    iterator new_finish = new_start;

    new_finish = std::uninitialized_copy(start_, finish_, new_start);

    clear();
    Allocator<value_type>::deallocate(start_);

    start_ = new_start;
    finish_ = new_finish;
    end_of_storage_ = new_start + len;

    Allocator<value_type>::construct(finish_, value);
    ++finish_;
  }
}

}  // namespace tracystl

#endif  // TRACYSTL_VECTOR_H_
