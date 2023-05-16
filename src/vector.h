#ifndef _TRACYSTL_VECTOR_H_
#define _TRACYSTL_VECTOR_H_

#include "allocator.h"
#include "iterator.h"
#include <cstddef> // For std::size_t
// #include <memory>  // For std::allocator

namespace tracystl {

template <class T>
class Vector {
 public:
  typedef T value_type;
  typedef value_type* iterator;
  typedef tracystl::Allocator<value_type> allocator_type;
  typedef typename allocator_type::size_type size_type;
  typedef typename allocator_type::reference reference;
  typedef typename allocator_type::const_reference const_reference;
  // take advantage of static member function
  typedef tracystl::Allocator<value_type> data_allocator;
  typedef const value_type* const_iterator;

 private:
  iterator begin_;
  iterator end_;
  iterator capacity_;

 public:
  Vector() : begin_(nullptr), end_(nullptr), capacity_(nullptr) {}
  ~Vector() {
    data_allocator::destroy(begin_, end_);
    data_allocator::deallocate(begin_, capacity());
  }

  iterator begin() { return begin_; }
  const_iterator begin() const noexcept { return begin_; }

  iterator end() { return end_; }
  const_iterator end() const noexcept { return end_; }

  size_t size() const { return static_cast<size_type>(end_ - begin_); }
  size_t capacity() const { return static_cast<size_type>(capacity_ - begin_); }

  bool empty() const { return begin_ == end_; }

  reference operator[](size_t n) { return *(begin_ + n); }
  const reference operator[](size_t n) const { return *(begin_ + n); }

  void clear(){end_ = begin_;}

  void push_back(const value_type& value);

  void pop_back() { --end_; }

  reference front() { return *begin_; }

  const_reference front() const { return *begin_; }

  reference back() { return *(end_ - 1); }

  const_reference back() const { return *(end_ - 1); }

  // void insert(iterator ){

  // }

};

template <class T>
void Vector<T>::push_back(const value_type& value) {
  if(end_ == capacity_){
    const size_t old_size = size();
    const size_t new_size = old_size != 0 ? 2 * old_size : 1;
    // printf("new_size: %zu\n", new_size);
    iterator new_begin = data_allocator::allocate(new_size);

    for(size_t i = 0; i < old_size; ++i){
      data_allocator::construct(new_begin + i, *(begin_ + i));
      data_allocator::destroy(begin_ + i);
    }

    data_allocator::deallocate(begin_);
    printf("new_begin: %p\n", new_begin);
    printf("begin_: %p\n", begin_);
    begin_ = static_cast<iterator>(new_begin);
    //new_begin;
    end_ = new_begin + old_size;
    capacity_ = new_begin + new_size;
  }
  data_allocator::construct(end_, value);
  end_++;
}

}  // namespace tracystl

#endif  // TRACYSTL_VECTOR_H_
