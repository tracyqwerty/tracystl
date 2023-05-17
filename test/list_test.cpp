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

TEST_F(ListTest, TestIterator) {
    int value = 0;
    for(auto it = list.begin(); it != list.end(); ++it, ++value) {
        EXPECT_EQ(*it, value);
    }
}
