#include "../src/allocator.h"

#include <gtest/gtest.h>

// using tracystl::Allocator;
typedef tracystl::Allocator<int> data_allocator;

TEST(AllocatorTest, AllocateAndDeallocate) {
  int* ptr = data_allocator::allocate(5);
  // assert not equal
  ASSERT_NE(ptr, nullptr);

  data_allocator::deallocate(ptr, 5);

  int* ptr2 = data_allocator::allocate();
  ASSERT_NE(ptr2, nullptr);
  data_allocator::deallocate(ptr2);
}

TEST(AllocatorTest, ConstructAndDestroy) {
  int* ptr = data_allocator::allocate(1);
  ASSERT_NE(ptr, nullptr);

  data_allocator::construct(ptr, 42);
  EXPECT_EQ(*ptr, 42);

  int* ptr2 = data_allocator::allocate(1);
  ASSERT_NE(ptr2, nullptr);

  // test construct(T* ptr, T&& value);
  // int(56) is an expression that creates a temporary int object with the value 56.
  // In C++, such an expression can generate a rvalue (temporary object) because it does not have a persistent memory location.
  data_allocator::construct(ptr2, int(56));
  EXPECT_EQ(*ptr2, 56);

  // first destroy the object pointed by ptr, then deallocate the memory
  data_allocator::destroy(ptr);
  data_allocator::deallocate(ptr, 1);

  data_allocator::destroy(ptr2);
  data_allocator::deallocate(ptr2, 1);
}
