#include <gtest/gtest.h>
#include "ds/singly_linked_list.hpp"

TEST(SinglyLinkedListTest, BasicOperations){
	SinglyLinkedList<int> L;
	EXPECT_EQ(L.size(), 0u);
	EXPECT_TRUE(L.empty());

	// push_back and insert
	L.push_back(10);
	L.push_back(20);
	L.push_back(40);
	L.insert(2, 30); // 10,20,30,40
	EXPECT_EQ(L.size(), 4u);
	EXPECT_EQ(L.at(0), 10);
	EXPECT_EQ(L.at(1), 20);
	EXPECT_EQ(L.at(2), 30);
	EXPECT_EQ(L.at(3), 40);

	// set
	L.set(0, 1);
	L.set(2, 2);
	L.set(3, 3); // 1,20,2,3
	EXPECT_EQ(L.at(0), 1);
	EXPECT_EQ(L.at(1), 20);
	EXPECT_EQ(L.at(2), 2);
	EXPECT_EQ(L.at(3), 3);

	// push_front
	L.push_front(0); // 0,1,20,2,3
	EXPECT_EQ(L.at(0), 0);

	// pop_front
	L.pop_front(); // 1,20,2,3
	EXPECT_EQ(L.front(), 1);

	// pop_back
	L.pop_back(); // 1,20,2
	EXPECT_EQ(L.back(), 2);

	// contains / index_of
	EXPECT_TRUE(L.contains(20));
	EXPECT_EQ(L.index_of(20), 1);
	EXPECT_FALSE(L.contains(999));
	EXPECT_EQ(L.index_of(999), -1);

	// erase middle
	L.erase(1); // remove 20 -> 1,2
	EXPECT_EQ(L.size(), 2u);
	EXPECT_EQ(L.at(0), 1);
	EXPECT_EQ(L.at(1), 2);

	// clear
	EXPECT_NO_THROW(L.clear());
	EXPECT_EQ(L.size(), 0u);
	EXPECT_TRUE(L.empty());
}

TEST(SinglyLinkedListTest, ExceptionsAndCopies){
	SinglyLinkedList<int> L;
	EXPECT_THROW(L.at(0), std::out_of_range);
	EXPECT_THROW(L.pop_front(), std::out_of_range);
	EXPECT_THROW(L.pop_back(), std::out_of_range);

	// copy constructor deep copy
	SinglyLinkedList<int> A;
	A.push_back(5);
	A.push_back(6);
	A.push_back(7);
	SinglyLinkedList<int> B(A);
	EXPECT_EQ(B.size(), 3u);
	EXPECT_EQ(B.at(0), 5);
	A.set(0, 42);
	EXPECT_EQ(B.at(0), 5); // B unchanged

	// copy assignment
	SinglyLinkedList<int> C;
	EXPECT_NO_THROW(C = A);
	EXPECT_EQ(C.size(), A.size());
	for (unsigned int i = 0; i < A.size(); ++i) EXPECT_EQ(C.at(i), A.at(i));
}

