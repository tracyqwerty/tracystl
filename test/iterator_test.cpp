#include "../src/iterator.h"

#include <gtest/gtest.h>
TEST(IteratorTest, IteratorTraitsForRawPointer) {
    typedef tracystl::iterator_traits<int*> traits;

    static_assert(std::is_same_v<traits::iterator_category, tracystl::random_access_iterator_tag>,
                  "Incorrect iterator category for raw pointer");
    static_assert(std::is_same_v<traits::value_type, int>,
                  "Incorrect value type for raw pointer");
    static_assert(std::is_same_v<traits::difference_type, std::size_t>,
                  "Incorrect difference type for raw pointer");
    static_assert(std::is_same_v<traits::pointer, int*>,
                  "Incorrect pointer type for raw pointer");
    static_assert(std::is_same_v<traits::reference, int&>,
                  "Incorrect reference type for raw pointer");
}

TEST(IteratorTest, IteratorTraitsForConstRawPointer) {
    typedef tracystl::iterator_traits<const int*> traits;

    static_assert(std::is_same_v<traits::iterator_category, tracystl::random_access_iterator_tag>,
                  "Incorrect iterator category for const raw pointer");
    static_assert(std::is_same_v<traits::value_type, int>,
                  "Incorrect value type for const raw pointer");
    static_assert(std::is_same_v<traits::difference_type, std::size_t>,
                  "Incorrect difference type for const raw pointer");
    static_assert(std::is_same_v<traits::pointer, const int*>,
                  "Incorrect pointer type for const raw pointer");
    static_assert(std::is_same_v<traits::reference, const int&>,
                  "Incorrect reference type for const raw pointer");
}
