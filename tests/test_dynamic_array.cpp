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

TEST(DynamicArrayTest, Insertion){
    DynamicArray<int> arr;

    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);
    arr.push_back(4);
    arr.push_back(5);

    EXPECT_EQ(arr.size(), 5);
    EXPECT_EQ(arr.capacity(), 8);  
    EXPECT_FALSE(arr.empty());

    arr.insert(0, 99);
    EXPECT_EQ(arr.at(1),1);
    EXPECT_EQ(arr.at(2),2);

    arr.insert(3,99); 
    EXPECT_EQ(arr.at(1),1);
    EXPECT_EQ(arr.at(2),2);
    EXPECT_EQ(arr.at(4),3);
    EXPECT_EQ(arr.at(5),4);

    arr.insert(7,99); 
    EXPECT_EQ(arr.at(1),1);
    EXPECT_EQ(arr.at(2),2);
    EXPECT_EQ(arr.at(4),3);
    EXPECT_EQ(arr.at(5),4);

    EXPECT_EQ(arr.at(0), 99);
    EXPECT_EQ(arr.at(3), 99);
    EXPECT_EQ(arr.at(7), 99);
}

TEST(DynamicArray, PopBack){
    DynamicArray<int> arr;

    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);
    arr.push_back(4);
    arr.push_back(5);

    arr.pop_back();

    EXPECT_EQ(arr.size(), 4);
}

TEST(DynamicArray, Erase){
    DynamicArray<int> arr;

    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);
    arr.push_back(4);
    arr.push_back(5);

    arr.erase(2);

    EXPECT_EQ(arr.size(), 4);

    EXPECT_EQ(arr.at(2), 4);
}

TEST(DynamicArray, Erases){
    DynamicArray<int> arr;

    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);
    arr.push_back(4);
    arr.push_back(5);

    arr.erase(2);

    EXPECT_EQ(arr.size(), 4);

    EXPECT_EQ(arr.at(2), 4);
}

TEST(DynamicArray, Eras){
    DynamicArray<int> arr;

    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);
    arr.push_back(4);
    arr.push_back(5);

    arr.erase(2);

    EXPECT_EQ(arr.size(), 4);

    EXPECT_EQ(arr.at(2), 4);
}

TEST(DynamicArray, sett){
    DynamicArray<int> arr;

    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);
    arr.push_back(4);
    arr.push_back(5);

    arr.set(2, 99);

    EXPECT_EQ(arr.at(2), 99);

}

TEST(DynamicArray, cleaning){
    DynamicArray<int> arr;

    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);
    arr.push_back(4);
    arr.push_back(5);

    arr.clear();

    EXPECT_TRUE(arr.empty());
    
}

TEST(DynamicArray, cont){
    DynamicArray<int> arr;

    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);
    arr.push_back(4);
    arr.push_back(5);

    EXPECT_TRUE(arr.contains(3));
    
}

TEST(DynamicArray, ind){
    DynamicArray<int> arr;

    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);
    arr.push_back(4);
    arr.push_back(5);

    EXPECT_EQ(arr.index_of(3),2);
    
}