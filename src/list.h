#ifndef _TRACYSTL_LIST_H_
#define _TRACYSTL_LIST_H_

#include "allocator.h"
#include "iterator.h"
#include <cstddef> // For std::size_t

namespace tracystl {

template <class T> struct list_node_base;
template <class T> struct list_node;

template <class T>
struct node_traits{
  typedef list_node_base<T>* base_ptr;
  typedef list_node<T>* node_ptr;
};

template <class T>
struct list_node_base{
  typedef typename node_traits<T>::base_ptr base_ptr;
  typedef typename node_traits<T>::node_ptr node_ptr;

  base_ptr prev_;
  base_ptr next_;

  list_node_base() : prev_(nullptr), next_(nullptr) {}

  base_ptr as_base() {
    return static_cast<base_ptr>(this);
  }

  node_ptr as_node() {
    return static_cast<node_ptr>(this);
  }
};

template <class T>
struct  listnode : public list_node_base<T>{
  // typedefs are not inherited. 
  typedef typename node_traits<T>::base_ptr base_ptr;
  typedef typename node_traits<T>::node_ptr node_ptr;

  T data_;

  // the base class part of a derived object must be initialized before the derived class's constructor can run.
  listnode() : list_node_base<T>(), data_() {}
  listnode(const T& d) : list_node_base<T>(), data_(d) {}
  listnode(T&& d) : list_node_base<T>(), data_(std::move(d)) {}

  base_ptr as_base() {
    return static_cast<base_ptr>(this);
  }

  node_ptr as_node() {
    return static_cast<node_ptr>(this);
  }
};

template <class T>
struct  list_iterator: public tracystl::iterator<tracystl::bidirectional_iterator_tag, T>{
  typedef typename node_traits<T>::base_ptr base_ptr;
  typedef typename node_traits<T>::node_ptr node_ptr;
  typedef list_iterator<T> self;
  typedef T value_type;
  typedef T& reference;
  typedef T* pointer;
  typedef std::bidirectional_iterator_tag iterator_category;
  typedef std::ptrdiff_t difference_type;

  base_ptr node_;

  list_iterator() : node_(nullptr) {}
  list_iterator(base_ptr x) : node_(x) {}
  // TODO: Why not use x->as_base()
  list_iterator(node_ptr x) : node_(x->as_base()) {}
  list_iterator(const self& x) : node(x.node) {}

  bool operator==(const self& x) const { return node_ == x.node_; }
  bool operator!=(const self& x) const { return node_ != x.node_; }

  reference operator*() const { return node->as_node()->data; }
  pointer operator->() const { return &(operator*()); }

  self& operator++() {
    node_ = node_->next;
    return *this;
  }
  self operator++(int) {
    self tmp = *this;
    ++*this;
    return tmp;
  }
  self& operator--() {
    node_ = node_->prev;
    return *this;
  }
  self operator--(int) {
    self tmp = *this;
    --*this;
    return tmp;
  }
};

template <class T>
struct  list_const_iterator{
  typedef typename node_traits<T>::base_ptr base_ptr;
  typedef typename node_traits<T>::node_ptr node_ptr;
  typedef list_const_iterator<T> self;
  typedef T value_type;
  typedef const T& reference;
  typedef const T* pointer;
  typedef std::bidirectional_iterator_tag iterator_category;
  typedef std::ptrdiff_t difference_type;

  base_ptr node_;

  list_const_iterator() : node_(nullptr) {}
  list_const_iterator(base_ptr x) : node_(x) {}
  list_const_iterator(node_ptr x) : node_(x->as_base()) {}
  list_const_iterator(const self& x) : node_(x.node) {}
  list_const_iterator(const list_iterator<T>& x) : node_(x.node) {}

  bool operator==(const self& x) const { return node_ == x.node_; }
  bool operator!=(const self& x) const { return node_ != x.node_; }

  reference operator*() const { return node_->as_node()->data; }
  pointer operator->() const { return &(operator*()); }

  self& operator++() {
    node_ = node_->next;
    return *this;
  }
  self operator++(int) {
    self tmp = *this;
    ++*this;
    return tmp;
  }
  self& operator--() {
    node_ = node_->prev;
    return *this;
  }
  self operator--(int) {
    self tmp = *this;
    --*this;
    return tmp;
  }
};

template <class T>
class List{
public:
  typedef typename node_traits<T>::base_ptr base_ptr;
  typedef typename node_traits<T>::node_ptr node_ptr;
  typedef list_iterator<T> iterator;
  typedef list_const_iterator<T> const_iterator;
  typedef T value_type;
  typedef T& reference;
  typedef const T& const_reference;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;
  typedef tracystl::Allocator<T> allocator_type;
  typedef tracystl::Allocator<T> data_allocator;
  typedef tracystl::Allocator<list_node_base<T>> node_allocator;
  typedef tracystl::Allocator<list_node<T>> node_allocator;

private:
  size_type size_;
  base_ptr node_;

public:
  List() : size_(0) {
    node_ = node_allocator::allocate();
    node_->next_ = node_;
    node_->prev_ = node_;
  }
  


};

}  // namespace tracystl

#endif  // TRACYSTL_LIST_H_
