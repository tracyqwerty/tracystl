#ifndef _TRACYSTL_ALLOCATOR_H_
#define _TRACYSTL_ALLOCATOR_H_
#include <cstddef>
#include <utility>
namespace tracystl {

template <class T>
class Allocator {
 public:
  // these are used as placeholder only
  typedef T value_type;
  typedef T* pointer;
  typedef const T* const_pointer;
  typedef T& reference;
  typedef const T& const_reference;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;

 public:
  static T* allocate();
  static T* allocate(size_t n);

  static void deallocate(T* ptr);
  static void deallocate(T* ptr, size_type n);

  static void construct(T* ptr);
  static void construct(T* ptr, const T& value);
  static void construct(T* ptr, T&& value);

  static void destroy(T* ptr);
  static void destroy(T* first, T* last);
};

template <class T>
T* Allocator<T>::allocate() {
  return static_cast<T*>(::operator new(sizeof(T)));
}

template <class T>
T* Allocator<T>::allocate(size_t n) {
  if (n == 0) {
    return nullptr;
  }
  // ::operator new(n * sizeof(T)) will call the operator new function in global namespace. 
  // It will allocate n * sizeof(T) bytes of memory and return a pointer to the first byte of the allocated memory. 
  // This function call will not call the constructor of the object.
  return static_cast<T*>(::operator new(n * sizeof(T)));
}

template <class T>
void Allocator<T>::deallocate(T* ptr) {
  if (ptr == nullptr) {
    return;   
  }
  // ::operator delete can automatically recognize the size of memory to be freed.
  ::operator delete(ptr);
}

template <class T>
void Allocator<T>::deallocate(T* ptr, size_type) {
  if (ptr == nullptr) {
    return;
  }
  ::operator delete(ptr);
}

template <class T>
void Allocator<T>::construct(T* ptr) {
  // here we use placement new expression. 
  // Placement new expression is a way to construct an object on already allocated memory.
  // It does not allocate new memory for the object, but construct the object directly at the provided pointer p.
  // In this example, we use placement new to construct an object of type T at p.
  new (ptr) T();
}

template <class T>
void Allocator<T>::construct(T* ptr, const T& value) {
  new (ptr) T(value);
}

template <class T>
void Allocator<T>::construct(T* ptr, T&& value) {
  new (ptr) T(std::move(value));
}

template <class T>
void Allocator<T>::destroy(T* ptr) {
  ptr->~T();
}

template <class T>
void Allocator<T>::destroy(T* first, T* last) {
  for (; first != last; ++first) {
    first->~T();
  }
}

}  // namespace tracystl
#endif  // TRACYSTL_ALLOCATOR_H