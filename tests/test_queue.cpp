#include <gtest/gtest.h>

#include <queue>
#include <random>
#include <stdexcept>
#include <string>

#include "ds/queue.hpp"

TEST(QueueTest, NewQueueIsEmpty) {
    const Queue<int> queue;
    EXPECT_TRUE(queue.empty());
    EXPECT_EQ(queue.size(), 0u);
}

TEST(QueueTest, EmptyQueueRejectsAccessAndRemoval) {
    Queue<int> queue;
    EXPECT_THROW(queue.front(), std::out_of_range);
    EXPECT_THROW(queue.back(), std::out_of_range);
    EXPECT_THROW(queue.pop(), std::out_of_range);
    EXPECT_TRUE(queue.empty());
    EXPECT_EQ(queue.size(), 0u);
}

TEST(QueueTest, PushAddsAtBackAndPreservesFront) {
    Queue<int> queue;
    queue.push(10);
    EXPECT_FALSE(queue.empty());
    EXPECT_EQ(queue.size(), 1u);
    EXPECT_EQ(queue.front(), 10);
    EXPECT_EQ(queue.back(), 10);

    queue.push(20);
    queue.push(30);
    EXPECT_EQ(queue.size(), 3u);
    EXPECT_EQ(queue.front(), 10);
    EXPECT_EQ(queue.back(), 30);
}

TEST(QueueTest, ConstObserversDoNotRemoveElements) {
    Queue<int> queue;
    queue.push(10);
    queue.push(20);
    const Queue<int>& view = queue;
    for (int i = 0; i < 3; ++i) {
        EXPECT_EQ(view.front(), 10);
        EXPECT_EQ(view.back(), 20);
        EXPECT_EQ(view.size(), 2u);
        EXPECT_FALSE(view.empty());
    }
}

TEST(QueueTest, PopRemovesElementsInFifoOrder) {
    Queue<int> queue;
    queue.push(10);
    queue.push(20);
    queue.push(30);
    unsigned int remaining = 3;
    for (int expected : {10, 20, 30}) {
        ASSERT_FALSE(queue.empty());
        EXPECT_EQ(queue.front(), expected);
        EXPECT_EQ(queue.back(), 30);
        queue.pop();
        EXPECT_EQ(queue.size(), --remaining);
    }
    EXPECT_TRUE(queue.empty());
    EXPECT_THROW(queue.front(), std::out_of_range);
    EXPECT_THROW(queue.back(), std::out_of_range);
    EXPECT_THROW(queue.pop(), std::out_of_range);
}

TEST(QueueTest, QueueCanBeReusedAfterRemovingLastElement) {
    Queue<int> queue;
    for (int value : {10, 20, 30}) {
        queue.push(value);
        EXPECT_EQ(queue.front(), value);
        EXPECT_EQ(queue.back(), value);
        EXPECT_EQ(queue.size(), 1u);
        queue.pop();
        EXPECT_TRUE(queue.empty());
        EXPECT_EQ(queue.size(), 0u);
    }
}

TEST(QueueTest, InterleavedPushAndPopPreserveOrderAndDuplicates) {
    Queue<int> queue;
    queue.push(5);
    queue.push(5);
    queue.pop();
    queue.push(-1);
    queue.push(0);
    EXPECT_EQ(queue.size(), 3u);
    EXPECT_EQ(queue.back(), 0);
    for (int expected : {5, -1, 0}) {
        ASSERT_FALSE(queue.empty());
        EXPECT_EQ(queue.front(), expected);
        queue.pop();
    }
    EXPECT_TRUE(queue.empty());
}

TEST(QueueTest, ClearIsIdempotentAndQueueCanBeReused) {
    Queue<int> queue;
    EXPECT_NO_THROW(queue.clear());
    queue.push(10);
    queue.push(20);
    queue.clear();
    EXPECT_TRUE(queue.empty());
    EXPECT_EQ(queue.size(), 0u);
    EXPECT_THROW(queue.front(), std::out_of_range);
    EXPECT_THROW(queue.back(), std::out_of_range);
    EXPECT_THROW(queue.pop(), std::out_of_range);
    EXPECT_NO_THROW(queue.clear());

    queue.push(99);
    EXPECT_EQ(queue.size(), 1u);
    EXPECT_EQ(queue.front(), 99);
    EXPECT_EQ(queue.back(), 99);
}

TEST(QueueTest, CopyConstructorCreatesIndependentQueue) {
    Queue<int> original;
    original.push(10);
    original.push(20);
    Queue<int> copy(original);
    original.clear();
    original.push(99);

    EXPECT_EQ(copy.size(), 2u);
    EXPECT_EQ(copy.front(), 10);
    EXPECT_EQ(copy.back(), 20);
    copy.pop();
    EXPECT_EQ(copy.front(), 20);
    EXPECT_EQ(original.front(), 99);
    EXPECT_EQ(original.size(), 1u);
}

TEST(QueueTest, CopyConstructorHandlesEmptyQueue) {
    const Queue<int> original;
    Queue<int> copy(original);
    EXPECT_TRUE(copy.empty());
    EXPECT_EQ(copy.size(), 0u);
    copy.push(7);
    EXPECT_EQ(copy.front(), 7);
    EXPECT_TRUE(original.empty());
}

TEST(QueueTest, CopyAssignmentReplacesContentsAndIsIndependent) {
    Queue<int> source;
    source.push(10);
    source.push(20);
    Queue<int> destination;
    destination.push(1);
    destination.push(2);
    destination.push(3);
    destination = source;
    source.clear();

    EXPECT_EQ(destination.size(), 2u);
    EXPECT_EQ(destination.front(), 10);
    EXPECT_EQ(destination.back(), 20);
    destination.pop();
    EXPECT_EQ(destination.front(), 20);
    EXPECT_TRUE(source.empty());
}

TEST(QueueTest, CopyAssignmentHandlesEmptySourceAndDestination) {
    Queue<int> source;
    source.push(42);
    Queue<int> destination;
    destination = source;
    EXPECT_EQ(destination.size(), 1u);
    EXPECT_EQ(destination.front(), 42);

    const Queue<int> empty;
    destination = empty;
    EXPECT_TRUE(destination.empty());
    EXPECT_EQ(destination.size(), 0u);
    EXPECT_THROW(destination.front(), std::out_of_range);
    EXPECT_THROW(destination.back(), std::out_of_range);
    destination.push(7);
    EXPECT_EQ(destination.front(), 7);
    EXPECT_EQ(destination.back(), 7);
}

TEST(QueueTest, SelfAssignmentPreservesContents) {
    Queue<int> queue;
    queue = queue;
    EXPECT_TRUE(queue.empty());
    queue.push(10);
    queue.push(20);
    queue = queue;
    EXPECT_EQ(queue.size(), 2u);
    EXPECT_EQ(queue.front(), 10);
    EXPECT_EQ(queue.back(), 20);
    queue.pop();
    EXPECT_EQ(queue.front(), 20);
}

TEST(QueueTest, SupportsStringValuesAndCopiesPushedValue) {
    Queue<std::string> queue;
    std::string value = "first";
    queue.push(value);
    value = "changed";
    queue.push("second");
    EXPECT_EQ(queue.front(), "first");
    EXPECT_EQ(queue.back(), "second");
    queue.pop();
    EXPECT_EQ(queue.front(), "second");
    queue.pop();
    EXPECT_TRUE(queue.empty());
}

TEST(QueueTest, MixedOperationsMatchStandardQueue) {
    Queue<int> actual;
    std::queue<int> expected;
    std::mt19937 random(2026);
    for (int step = 0; step < 1000; ++step) {
        SCOPED_TRACE(step);
        const auto operation = random() % 10;
        if (operation < 6) {
            const int value = static_cast<int>(random() % 21) - 10;
            actual.push(value);
            expected.push(value);
        } else if (operation < 9) {
            if (expected.empty()) {
                EXPECT_THROW(actual.pop(), std::out_of_range);
            } else {
                actual.pop();
                expected.pop();
            }
        } else {
            actual.clear();
            while (!expected.empty()) expected.pop();
        }
        ASSERT_EQ(actual.size(), expected.size());
        ASSERT_EQ(actual.empty(), expected.empty());
        if (!expected.empty()) {
            EXPECT_EQ(actual.front(), expected.front());
            EXPECT_EQ(actual.back(), expected.back());
        } else {
            EXPECT_THROW(actual.front(), std::out_of_range);
            EXPECT_THROW(actual.back(), std::out_of_range);
        }
    }
    while (!expected.empty()) {
        ASSERT_FALSE(actual.empty());
        EXPECT_EQ(actual.front(), expected.front());
        actual.pop();
        expected.pop();
    }
    EXPECT_TRUE(actual.empty());
    EXPECT_EQ(actual.size(), 0u);
}
