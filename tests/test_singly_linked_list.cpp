#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "ds/singly_linked_list.hpp"

namespace {

template <typename T>
void expect_list_equals(const SinglyLinkedList<T>& list,
                        const std::vector<T>& expected) {
    ASSERT_EQ(list.size(), expected.size());

    for (std::size_t i = 0; i < expected.size(); ++i) {
        EXPECT_EQ(list.at(static_cast<unsigned int>(i)), expected[i]);
    }
}

}  // namespace

TEST(SinglyLinkedListTest, NewListIsEmpty) {
    SinglyLinkedList<int> list;

    EXPECT_EQ(list.size(), 0u);
    EXPECT_TRUE(list.empty());
    EXPECT_FALSE(list.contains(10));
    EXPECT_EQ(list.index_of(10), -1);
}

TEST(SinglyLinkedListTest, EmptyListRejectsElementAccessAndRemoval) {
    SinglyLinkedList<int> list;

    EXPECT_THROW(list.at(0), std::out_of_range);
    EXPECT_THROW(list.set(0, 10), std::out_of_range);
    EXPECT_THROW(list.front(), std::out_of_range);
    EXPECT_THROW(list.back(), std::out_of_range);
    EXPECT_THROW(list.pop_front(), std::out_of_range);
    EXPECT_THROW(list.pop_back(), std::out_of_range);
    EXPECT_THROW(list.erase(0), std::out_of_range);
}

TEST(SinglyLinkedListTest, PushFrontAndPushBackPreserveOrder) {
    SinglyLinkedList<int> list;

    list.push_back(20);
    list.push_front(10);
    list.push_back(30);
    list.push_front(0);

    expect_list_equals(list, std::vector<int>{0, 10, 20, 30});
    EXPECT_EQ(list.front(), 0);
    EXPECT_EQ(list.back(), 30);
    EXPECT_FALSE(list.empty());
}

TEST(SinglyLinkedListTest, InsertWorksAtBeginningMiddleAndEnd) {
    SinglyLinkedList<int> list;

    list.insert(0, 20);  // Insert into an empty list.
    list.insert(0, 10);  // Beginning.
    list.insert(2, 40);  // End.
    list.insert(2, 30);  // Middle.

    expect_list_equals(list, std::vector<int>{10, 20, 30, 40});
    EXPECT_EQ(list.front(), 10);
    EXPECT_EQ(list.back(), 40);
}

TEST(SinglyLinkedListTest, InsertRejectsPositionPastEnd) {
    SinglyLinkedList<int> list;

    EXPECT_THROW(list.insert(1, 10), std::out_of_range);

    list.push_back(10);
    EXPECT_THROW(list.insert(2, 20), std::out_of_range);
    expect_list_equals(list, std::vector<int>{10});
}

TEST(SinglyLinkedListTest, SetUpdatesFirstMiddleAndLastElements) {
    SinglyLinkedList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    list.set(0, 1);
    list.set(1, 2);
    list.set(2, 3);

    expect_list_equals(list, std::vector<int>{1, 2, 3});
    EXPECT_THROW(list.set(3, 4), std::out_of_range);
}

TEST(SinglyLinkedListTest, AtRejectsPositionEqualToOrPastSize) {
    SinglyLinkedList<int> list;
    list.push_back(10);
    list.push_back(20);

    EXPECT_EQ(list.at(0), 10);
    EXPECT_EQ(list.at(1), 20);
    EXPECT_THROW(list.at(2), std::out_of_range);
    EXPECT_THROW(list.at(100), std::out_of_range);
}

TEST(SinglyLinkedListTest, PopFrontHandlesManyAndSingleElementLists) {
    SinglyLinkedList<int> list;
    list.push_back(10);
    list.push_back(20);

    list.pop_front();
    expect_list_equals(list, std::vector<int>{20});
    EXPECT_EQ(list.front(), 20);
    EXPECT_EQ(list.back(), 20);

    list.pop_front();
    EXPECT_TRUE(list.empty());
    EXPECT_EQ(list.size(), 0u);
    EXPECT_THROW(list.front(), std::out_of_range);
    EXPECT_THROW(list.back(), std::out_of_range);
}

TEST(SinglyLinkedListTest, PopBackHandlesManyAndSingleElementLists) {
    SinglyLinkedList<int> list;
    list.push_back(10);
    list.push_back(20);

    list.pop_back();
    expect_list_equals(list, std::vector<int>{10});
    EXPECT_EQ(list.front(), 10);
    EXPECT_EQ(list.back(), 10);

    list.pop_back();
    EXPECT_TRUE(list.empty());
    EXPECT_EQ(list.size(), 0u);
    EXPECT_THROW(list.front(), std::out_of_range);
    EXPECT_THROW(list.back(), std::out_of_range);
}

TEST(SinglyLinkedListTest, EraseWorksAtBeginningMiddleAndEnd) {
    SinglyLinkedList<int> list;
    for (int value : {10, 20, 30, 40, 50}) {
        list.push_back(value);
    }

    list.erase(0);
    expect_list_equals(list, std::vector<int>{20, 30, 40, 50});

    list.erase(1);
    expect_list_equals(list, std::vector<int>{20, 40, 50});

    list.erase(2);
    expect_list_equals(list, std::vector<int>{20, 40});
    EXPECT_EQ(list.front(), 20);
    EXPECT_EQ(list.back(), 40);
}

TEST(SinglyLinkedListTest, EraseHandlesSingleElementAndRejectsInvalidPosition) {
    SinglyLinkedList<int> list;
    list.push_back(10);

    EXPECT_THROW(list.erase(1), std::out_of_range);
    list.erase(0);

    EXPECT_TRUE(list.empty());
    EXPECT_EQ(list.size(), 0u);
    EXPECT_THROW(list.erase(0), std::out_of_range);
}

TEST(SinglyLinkedListTest, ContainsAndIndexOfUseFirstMatchingElement) {
    SinglyLinkedList<int> list;
    for (int value : {10, 20, 10, 30}) {
        list.push_back(value);
    }

    EXPECT_TRUE(list.contains(10));
    EXPECT_TRUE(list.contains(30));
    EXPECT_FALSE(list.contains(99));
    EXPECT_EQ(list.index_of(10), 0);
    EXPECT_EQ(list.index_of(20), 1);
    EXPECT_EQ(list.index_of(30), 3);
    EXPECT_EQ(list.index_of(99), -1);
}

TEST(SinglyLinkedListTest, ClearIsIdempotentAndListCanBeReused) {
    SinglyLinkedList<int> list;

    EXPECT_NO_THROW(list.clear());
    EXPECT_NO_THROW(list.clear());

    list.push_back(10);
    list.push_back(20);
    list.clear();

    EXPECT_TRUE(list.empty());
    EXPECT_EQ(list.size(), 0u);
    EXPECT_NO_THROW(list.clear());

    list.push_front(30);
    expect_list_equals(list, std::vector<int>{30});
    EXPECT_EQ(list.front(), 30);
    EXPECT_EQ(list.back(), 30);
}

TEST(SinglyLinkedListTest, CopyConstructorCreatesIndependentCopy) {
    SinglyLinkedList<int> original;
    original.push_back(10);
    original.push_back(20);
    original.push_back(30);

    SinglyLinkedList<int> copy(original);
    original.set(0, 99);
    original.pop_back();

    expect_list_equals(original, std::vector<int>{99, 20});
    expect_list_equals(copy, std::vector<int>{10, 20, 30});
}

TEST(SinglyLinkedListTest, CopyConstructorHandlesEmptyList) {
    SinglyLinkedList<int> original;
    SinglyLinkedList<int> copy(original);

    EXPECT_TRUE(copy.empty());
    EXPECT_EQ(copy.size(), 0u);
}

TEST(SinglyLinkedListTest, CopyAssignmentReplacesExistingElements) {
    SinglyLinkedList<int> source;
    source.push_back(10);
    source.push_back(20);

    SinglyLinkedList<int> destination;
    destination.push_back(1);
    destination.push_back(2);
    destination.push_back(3);

    destination = source;
    source.set(0, 99);

    expect_list_equals(source, std::vector<int>{99, 20});
    expect_list_equals(destination, std::vector<int>{10, 20});
}

TEST(SinglyLinkedListTest, CopyAssignmentHandlesEmptySourceAndSelfAssignment) {
    SinglyLinkedList<int> empty;
    SinglyLinkedList<int> list;
    list.push_back(10);
    list.push_back(20);

    list = list;
    expect_list_equals(list, std::vector<int>{10, 20});

    list = empty;
    EXPECT_TRUE(list.empty());
    EXPECT_EQ(list.size(), 0u);
}

TEST(SinglyLinkedListTest, SupportsStringValues) {
    SinglyLinkedList<std::string> list;

    list.push_back("beta");
    list.push_front("alpha");
    list.insert(2, "gamma");
    list.set(1, "BETA");

    expect_list_equals(
        list, std::vector<std::string>{"alpha", "BETA", "gamma"});
    EXPECT_TRUE(list.contains("BETA"));
    EXPECT_EQ(list.index_of("gamma"), 2);
}
