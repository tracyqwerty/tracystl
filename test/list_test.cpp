#include "gtest/gtest.h"
#include "../src/list.h"

class ListTest : public ::testing::Test {
protected:
    void SetUp() override {
        for (int i = 0; i < 5; ++i) {
            list.push_back(i);
        }
    }

    tracystl::List<int> list;
};

TEST_F(ListTest, PushBack) {
    list.push_back(5);
    EXPECT_EQ(list.back(), 5);
}

TEST_F(ListTest, PopBack) {
    list.pop_back();
    EXPECT_EQ(list.back(), 3);
}

TEST_F(ListTest, Size) {
    EXPECT_EQ(list.size(), 5);
}

TEST_F(ListTest, ClearAndEmpty) {
    EXPECT_FALSE(list.empty());
    list.clear();
    EXPECT_TRUE(list.empty());
}

TEST_F(ListTest, Iterator) {
    int value = 0;
    for(auto it = list.begin(); it != list.end(); ++it, ++value) {
        EXPECT_EQ(*it, value);
    }
}

TEST_F(ListTest, TestErase) {
    // Erase elements 2 and 3
    auto first = list.begin();
    auto last = first;
    std::advance(last, 2);        // Iterator to fourth element
    // test erase(iterator first, iterator last)
    list.erase(first, last);
    // test erase(iterator pos)
    list.erase(last);

    std::vector<int> expected_values = {3, 4};
    int i = 0;
    for(auto it = list.begin(); it != list.end(); ++it, ++i) {
        EXPECT_EQ(*it, expected_values[i]);
    }
}
