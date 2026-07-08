#include <gtest/gtest.h>

#include "ds/dynamic_array.hpp"

/*
EXPECT_EQ(original.at(0), 1);
EXPECT_TRUE(arr.empty());
EXPECT_THROW(arr.at(2), std::out_of_range);

*/


TEST(DynamicArrayTest, PushBack){
    DynamicArray<int> arr;

    arr.push_back(1);
    EXPECT_EQ(arr.size(), 1);
    EXPECT_EQ(arr.capacity(), 1);
    EXPECT_FALSE(arr.empty());


}