#include "../src/vector.h"

#include "../src/iterator.h"
#include "gtest/gtest.h"


using tracystl::iterator;
using tracystl::Vector;

TEST(VectorTest, DefaultConstructor) {
  Vector<int> vec;
  EXPECT_EQ(vec.size(), 0);
  EXPECT_EQ(vec.capacity(), 0);
  EXPECT_TRUE(vec.empty());
}

TEST(VectorTest, ElementAccess) {
  Vector<int> vec;
  Vector<int> new_vec;
  for (int i = 0; i < 5; ++i) {
    vec.push_back(i);
  }
  // T& operator=(int pos);
  new_vec = vec;
  // T& front();
  EXPECT_EQ(vec.front(), 0);
  // T& back();
  EXPECT_EQ(vec.back(), 4);
  // T& operator[](int pos);
  EXPECT_EQ(vec[2], 2);
  vec[2] = 1;
  EXPECT_EQ(vec[2], 1);
}

// TEST(VectorTest, Iterators) {
//   Vector<int> vec;
//   for (int i = 0; i < 5; ++i) {
//     vec.push_back(i);
//   }
//   Vector<int>::iterator begin = vec.begin();
//   Vector<int>::iterator end = vec.end();
//   // 这样写也可以，但是不符合C++的规范
//   iterator<int> begin2 = vec.begin();
//   EXPECT_EQ(*begin, 0);
//   EXPECT_EQ(*begin2, 0);
//   // EXPECT_EQ(*(end - 1), 4);
// }

TEST(VectorTest, Capacity) {
  Vector<int> vec;
  for (int i = 0; i < 5; ++i) {
    vec.push_back(i);
  }
  EXPECT_EQ(vec.size(), 5);
  EXPECT_EQ(vec.capacity(), 8);
  EXPECT_FALSE(vec.empty());
}

TEST(VectorTest, Modifiers) {
  Vector<int> vec;
  for (int i = 0; i < 3; ++i) {
    vec.push_back(i);
  }

  EXPECT_EQ(vec.size(), 3);
  EXPECT_EQ(vec[0], 0);
  EXPECT_EQ(vec[1], 1);
  EXPECT_EQ(vec[2], 2);

  vec.pop_back();
  EXPECT_EQ(vec.size(), 2);
  EXPECT_EQ(vec[0], 0);
  EXPECT_EQ(vec[1], 1);

  vec.clear();
  EXPECT_EQ(vec.size(), 0);
  EXPECT_TRUE(vec.empty());
  EXPECT_EQ(vec.capacity(), 4);

  for (int i = 0; i < 5; ++i) {
    vec.push_back(i);
  }
  // vec.insert(vec.begin() + 2, 3);
  // EXPECT_EQ(vec.size(), 6);
  // EXPECT_EQ(vec[2], 3);
}
