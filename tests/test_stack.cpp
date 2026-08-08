#include <gtest/gtest.h>

#include <string>

#include "ds/stack.hpp"

TEST(StackTest, NewStackIsEmpty) {
    Stack<int> stack;

    EXPECT_TRUE(stack.empty());
    EXPECT_EQ(stack.size(), 0u);
}

TEST(StackTest, PushAddsElementsToTop) {
    Stack<int> stack;

    stack.push(10);
    EXPECT_EQ(stack.top(), 10);
    EXPECT_EQ(stack.size(), 1u);

    stack.push(20);
    EXPECT_EQ(stack.top(), 20);
    EXPECT_EQ(stack.size(), 2u);
    EXPECT_FALSE(stack.empty());
}

TEST(StackTest, TopDoesNotRemoveElement) {
    Stack<int> stack;
    stack.push(10);
    stack.push(20);

    EXPECT_EQ(stack.top(), 20);
    EXPECT_EQ(stack.top(), 20);
    EXPECT_EQ(stack.size(), 2u);
}

TEST(StackTest, PopRemovesElementsInLifoOrder) {
    Stack<int> stack;
    stack.push(10);
    stack.push(20);
    stack.push(30);

    EXPECT_EQ(stack.top(), 30);
    stack.pop();
    EXPECT_EQ(stack.top(), 20);
    EXPECT_EQ(stack.size(), 2u);

    stack.pop();
    EXPECT_EQ(stack.top(), 10);
    EXPECT_EQ(stack.size(), 1u);

    stack.pop();
    EXPECT_TRUE(stack.empty());
    EXPECT_EQ(stack.size(), 0u);
}

TEST(StackTest, TopAndPopThrowWhenStackIsEmpty) {
    Stack<int> stack;

    EXPECT_THROW(stack.top(), std::out_of_range);
    EXPECT_THROW(stack.pop(), std::out_of_range);
    EXPECT_TRUE(stack.empty());
    EXPECT_EQ(stack.size(), 0u);
}

TEST(StackTest, ClearEmptiesStackAndCanBeCalledRepeatedly) {
    Stack<int> stack;
    stack.push(10);
    stack.push(20);

    stack.clear();
    EXPECT_TRUE(stack.empty());
    EXPECT_EQ(stack.size(), 0u);
    EXPECT_THROW(stack.top(), std::out_of_range);

    EXPECT_NO_THROW(stack.clear());
    EXPECT_TRUE(stack.empty());
}

TEST(StackTest, StackCanBeReusedAfterClear) {
    Stack<int> stack;
    stack.push(10);
    stack.clear();

    stack.push(99);

    EXPECT_FALSE(stack.empty());
    EXPECT_EQ(stack.size(), 1u);
    EXPECT_EQ(stack.top(), 99);
}

TEST(StackTest, ConstStackSupportsObserverMethods) {
    Stack<int> mutable_stack;
    mutable_stack.push(10);
    mutable_stack.push(20);

    const Stack<int> stack(mutable_stack);

    EXPECT_FALSE(stack.empty());
    EXPECT_EQ(stack.size(), 2u);
    EXPECT_EQ(stack.top(), 20);
}

TEST(StackTest, CopyConstructorCreatesIndependentStack) {
    Stack<int> original;
    original.push(10);
    original.push(20);

    Stack<int> copy(original);
    original.pop();

    EXPECT_EQ(original.top(), 10);
    EXPECT_EQ(original.size(), 1u);
    EXPECT_EQ(copy.top(), 20);
    EXPECT_EQ(copy.size(), 2u);
}

TEST(StackTest, CopyAssignmentReplacesExistingContents) {
    Stack<int> source;
    source.push(10);
    source.push(20);

    Stack<int> destination;
    destination.push(1);
    destination.push(2);
    destination.push(3);

    destination = source;
    source.pop();

    EXPECT_EQ(source.top(), 10);
    EXPECT_EQ(source.size(), 1u);
    EXPECT_EQ(destination.top(), 20);
    EXPECT_EQ(destination.size(), 2u);
}

TEST(StackTest, SelfAssignmentPreservesContents) {
    Stack<int> stack;
    stack.push(10);
    stack.push(20);

    stack = stack;

    EXPECT_EQ(stack.size(), 2u);
    EXPECT_EQ(stack.top(), 20);
    stack.pop();
    EXPECT_EQ(stack.top(), 10);
}

TEST(StackTest, SupportsStringValues) {
    Stack<std::string> stack;

    stack.push("first");
    stack.push("second");

    EXPECT_EQ(stack.top(), "second");
    stack.pop();
    EXPECT_EQ(stack.top(), "first");
}
