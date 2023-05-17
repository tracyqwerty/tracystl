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

  void unlink() {
    prev_= next_ = as_base();
  }

};

template <class T>
struct  list_node : public list_node_base<T>{
  // typedefs are not inherited. 
  typedef typename node_traits<T>::base_ptr base_ptr;
  typedef typename node_traits<T>::node_ptr node_ptr;

  T data_;

  // the base class part of a derived object must be initialized before the derived class's constructor can run.
  list_node() : list_node_base<T>(), data_() {}
  list_node(const T& d) : list_node_base<T>(), data_(d) {}
  list_node(T&& d) : list_node_base<T>(), data_(std::move(d)) {}

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
  list_iterator(const self& x) : node_(x.node_) {}

  bool operator==(const self& x) const { return node_ == x.node_; }
  bool operator!=(const self& x) const { return node_ != x.node_; }

  reference operator*() const { return node_->as_node()->data_; }
  pointer operator->() const { return &(operator*()); }

  self& operator++() {
    node_ = node_->next_;
    return *this;
  }
  self operator++(int) {
    self tmp = *this;
    ++*this;
    return tmp;
  }
  self& operator--() {
    node_ = node_->prev_;
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
  typedef tracystl::Allocator<list_node_base<T>> base_allocator;
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
  ~List(){
    clear();
    node_allocator::deallocate(node_->as_node());
  }
  void clear(){
    base_ptr cur = node_->next_;
    while(cur != node_){
      base_ptr tmp = cur;
      cur = cur->next_;
      node_allocator::destroy(tmp->as_node());
      node_allocator::deallocate(tmp->as_node());
    }
    node_->unlink();
    size_ = 0;
  }
  
  void push_back(const T& value){
    insert(end(), value);
  }

  void push_back(T&& value){
    insert(end(), std::move(value));
  }

  void push_front(const T& value){
    insert(begin(), value);
  }

  void push_front(T&& value){
    insert(begin(), std::move(value));
  }

  void pop_back(){
    erase(--end());
  }

  void pop_front(){
    erase(begin());
  }

  iterator begin(){
    return node_->next_;
  }

  const_iterator begin() const{
    return node_->next_;
  }

  iterator end(){
    return node_;
  }

  const_iterator end() const{
    return node_;
  }

  bool empty() const{
    return size_ == 0;
  }

  size_type size() const{
    return size_;
  }

  reference front(){
    return *begin();
  }

  const_reference front() const{
    return *begin();
  }

  reference back(){
    return *(--end());
  }

  const_reference back() const{
    return *(--end());
  }

  iterator insert(iterator pos, const value_type& value){
    node_ptr new_node = create_node(value);
    new_node->next_ = pos.node_;
    new_node->prev_ = pos.node_->prev_;
    pos.node_->prev_->next_ = new_node;
    pos.node_->prev_ = new_node;
    ++size_;
    return new_node;
  }

  iterator insert(iterator pos, const value_type&& value){
    node_ptr new_node = create_node(std::move(value));
    new_node->next_ = pos.node_;
    new_node->prev_ = pos.node_->prev_;
    pos.node_->prev_->next_ = new_node;
    pos.node_->prev_ = new_node;
    ++size_;
    return new_node;
  }

  iterator erase(iterator pos){
    base_ptr next_node = pos.node_->next_;
    base_ptr prev_node = pos.node_->prev_;
    prev_node->next_ = next_node;
    next_node->prev_ = prev_node;
    node_allocator::destroy(pos.node_->as_node());
    node_allocator::deallocate(pos.node_->as_node());
    --size_;
    return next_node->as_node();
  }

  iterator erase(iterator first, iterator last){
    base_ptr prev_node = first.node_->prev_;
    base_ptr next_node = last.node_;
    prev_node->next_ = next_node;
    next_node->prev_ = prev_node;
    while(first != last){
      base_ptr tmp = first.node_;
      ++first;
      data_allocator::destroy(tmp->as_node()->data_);
      node_allocator::deallocate(tmp);
      --size_;
    }
    return next_node->as_node();
  }

  // void resize(size_type new_size){
  //   resize(new_size, T());
  // }

  // void resize(size_type new_size, const T& value){
  //   iterator cur = begin();
  //   size_type len = 0;
  //   while(cur != end() && len < new_size){
  //     ++cur;
  //     ++len;
  //   }
  //   if(len == new_size){
  //     erase(cur, end());
  //   }else{
  //     insert(end(), new_size - len, value);
  //   }
  // }

  // void swap(List& rhs){
  //   std::swap(node_, rhs.node_);
  //   std::swap(size_, rhs.size_);
  // }

  // void merge(List& rhs){
  //   iterator first1 = begin();
  //   iterator last1 = end();
  //   iterator first2 = rhs.begin();
  //   iterator last2 = rhs.end();
  //   while(first1 != last1 && first2 != last2){
  //     if(*first2 < *first1){
  //       iterator next = first2;
  //       transfer(first1, first2, ++next);
  //       first2 = next;
  //     }else{
  //       ++first1;
  //     }
  //   }
  //   if(first2 != last2){
  //     transfer(last1, first2, last2);
  //   }
  //   size_ += rhs.size_;
  //   rhs.size_ = 0;
  //   rhs.node_->unlink();
  // }

  // void splice(iterator pos, List& rhs){
  //   if(!rhs.empty()){
  //     transfer(pos, rhs.begin(), rhs.end());
  //     size_ += rhs.size_;
  //     rhs.size_ = 0;
  //     rhs.node_->unlink();
  //   }
  // }

  // void splice(iterator pos, List& rhs, iterator it){
  //   iterator next = it;
  //   ++next;
  //   if(pos == it || pos == next){
  //     return;
  //   }
  //   transfer(pos, it, next);
  //   ++size_;
  //   --rhs.size_;
  // }

  // void splice(iterator pos, List& rhs, iterator first, iterator last){
  //   if(first != last){
  //     transfer(pos, first, last);
  //     size_ += last - first;
  //     rhs.size_ -= last - first;
  //   }
  // }

  // void remove(const T& value){
  //   iterator first = begin();
  //   iterator last = end();
  //   while(first != last){
  //     iterator next = first;
  //     ++next;
  //     if(*first == value){
  //       erase(first);
  //     }
  //     first = next;
  //   }
  // }

  // void reverse(){
  //   if(size_ == 0 || size_ == 1){
  //     return;
  //   }
  //   iterator first = begin();
  //   ++first;
  //   while(first != end()){
  //     iterator old = first;
  //     ++first;
  //     transfer(begin(), old, first);
  //   }
  // }

  // void unique(){
  //   iterator first = begin();
  //   iterator last = end();
  //   if(first == last){
  //     return;
  //   }
  //   iterator next = first;
  //   while(++next != last){
  //     if(*first == *next){
  //       erase(next);
  //     }else{
  //       first = next;
  //     }
  //     next = first;
  //   }
  // }

  // void sort(){
  //   if(size_ == 0 || size_ == 1){
  //     return;
  //   }
  //   List carry;
  //   List counter[64];
  //   int fill = 0;
  //   while(!empty()){
  //     carry.splice(carry.begin(), *this, begin());
  //     int i = 0;
  //     while(i < fill && !counter[i].empty()){
  //       counter[i].merge(carry);
  //       carry.swap(counter[i++]);
  //     }
  //     carry.swap(counter[i]);
  //     if(i == fill){
  //       ++fill;
  //     }
  //   }
  //   for(int i = 1; i < fill; ++i){
  //     counter[i].merge(counter[i - 1]);
  //   }
  //   swap(counter[fill - 1]);
  // }
private:
  node_ptr create_node(const T& value){
    node_ptr new_node = node_allocator::allocate(1);
    node_allocator::construct(new_node, value);
    return new_node;
  }
  
};

}  // namespace tracystl

#endif  // TRACYSTL_LIST_H_
