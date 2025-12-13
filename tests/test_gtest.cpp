#include <gtest/gtest.h>
#include <string>
#include <sstream>
#include <algorithm>
#include "Stack.h"
#include "Queue.h"

// ========== Тесты для Stack ==========

TEST(StackTest, DefaultConstructor) {
    Stack<int> s;
    EXPECT_TRUE(s.is_empty());
    EXPECT_EQ(s.size(), 0);
}

TEST(StackTest, PushAndTop) {
    Stack<int> s;
    s.push(1);
    EXPECT_FALSE(s.is_empty());
    EXPECT_EQ(s.size(), 1);
    EXPECT_EQ(s.get_front(), 1);

    s.push(2);
    EXPECT_EQ(s.size(), 2);
    EXPECT_EQ(s.get_front(), 2);
}

TEST(StackTest, Pop) {
    Stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);

    s.pop();
    EXPECT_EQ(s.size(), 2);
    EXPECT_EQ(s.get_front(), 2);
}

TEST(StackTest, CopyConstructor) {
    Stack<int> s1;
    s1.push(1);
    s1.push(2);
    s1.push(3);

    Stack<int> s2 = s1;
    EXPECT_EQ(s1.size(), 3);
    EXPECT_EQ(s2.size(), 3);
    EXPECT_EQ(s1.get_front(), 3);
    EXPECT_EQ(s2.get_front(), 3);
}

TEST(StackTest, MoveConstructor) {
    Stack<int> s1;
    s1.push(1);
    s1.push(2);

    Stack<int> s2 = std::move(s1);
    EXPECT_TRUE(s1.is_empty());
    EXPECT_EQ(s2.size(), 2);
    EXPECT_EQ(s2.get_front(), 2);
}

TEST(StackTest, CopyAssignment) {
    Stack<int> s1;
    s1.push(1);
    s1.push(2);

    Stack<int> s2;
    s2 = s1;
    EXPECT_EQ(s1.size(), 2);
    EXPECT_EQ(s2.size(), 2);
    EXPECT_EQ(s1.get_front(), 2);
    EXPECT_EQ(s2.get_front(), 2);
}

TEST(StackTest, MoveAssignment) {
    Stack<int> s1;
    s1.push(1);
    s1.push(2);

    Stack<int> s2;
    s2 = std::move(s1);
    EXPECT_TRUE(s1.is_empty());
    EXPECT_EQ(s2.size(), 2);
    EXPECT_EQ(s2.get_front(), 2);
}

TEST(StackTest, Iterators) {
    Stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);

    int sum = 0;
    for (auto it = s.begin(); it != s.end(); ++it) {
        sum += *it;
    }
    EXPECT_EQ(sum, 6);
}

TEST(StackTest, ConstIterators) {
    Stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);

    const Stack<int>& cs = s;
    int sum = 0;
    for (auto it = cs.begin(); it != cs.end(); ++it) {
        sum += *it;
    }
    EXPECT_EQ(sum, 6);
}

TEST(StackTest, RangeBasedFor) {
    Stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);

    int sum = 0;
    for (const auto& item : s) {
        sum += item;
    }
    EXPECT_EQ(sum, 6);
}

TEST(StackTest, IteratorModification) {
    Stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);

    for (auto it = s.begin(); it != s.end(); ++it) {
        *it *= 2;
    }

    EXPECT_EQ(s.get_front(), 6);
    s.pop();
    EXPECT_EQ(s.get_front(), 4);
    s.pop();
    EXPECT_EQ(s.get_front(), 2);
}

TEST(StackTest, Stack_Iterator) {
    Stack<int> s;
    s.push(10);
    s.push(20);
    s.push(30);

    // Константный итератор
    Stack<int>::const_iterator cit = s.cbegin();
    EXPECT_EQ(*cit, 30);
    ++cit;
    EXPECT_EQ(*cit, 20);
    cit++;
    EXPECT_EQ(*cit, 10);
    ++cit;
    EXPECT_EQ(cit, s.cend());

    // Неконстантный итератор
    Stack<int>::iterator it = s.begin();
    EXPECT_EQ(*it, 30);
    ++it;
    EXPECT_EQ(*it, 20);
    it++;
    EXPECT_EQ(*it, 10);
    ++it;
    EXPECT_EQ(it, s.end());

    std::stringstream sout;
    sout << s;
    EXPECT_EQ(sout.str(), "30 20 10");
}

TEST(StackTest, Stack_For) {
    Stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);

    const Stack<int>& r = s;
    int expected1[] = {3, 2, 1};
    int idx = 0;
    for (const auto& v : r) EXPECT_EQ(v, expected1[idx++]);

    idx = 0;
    for (auto& v : s) v *= 2;

    int expected2[] = {6, 4, 2};
    idx = 0;
    for (const auto& v : s) EXPECT_EQ(v, expected2[idx++]);
}

TEST(StackTest, Stack_PushPopCopy) {
    Stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);

    s.pop();
    s.push(10);
    s.push(20);

    Stack<int> copy_s(s);

    int expected_orig[] = {20, 10, 2, 1};
    int idx = 0;
    for (const auto& v : copy_s) EXPECT_EQ(v, expected_orig[idx++]);

    copy_s.pop();
    copy_s.pop();
    copy_s.push(99);
    copy_s.push(98);
    copy_s.push(97);

    idx = 0;
    for (const auto& v : s) EXPECT_EQ(v, expected_orig[idx++]);

    int expected_copy[] = {97, 98, 99, 2, 1};
    idx = 0;
    for (const auto& v : copy_s) EXPECT_EQ(v, expected_copy[idx++]);
}

TEST(StackTest, Stack_IO) {
    Stack<int> s;
    s.push(0);

    std::stringstream sin("1 2 3 4 5");
    sin >> s;

    EXPECT_EQ(s.size(), 6);

    int expected[] = {5, 4, 3, 2, 1, 0};
    int idx = 0;
    for (const auto& v : s) EXPECT_EQ(v, expected[idx++]);

    std::stringstream sout;
    sout << s;
    std::string expected_str = "5 4 3 2 1 0";
    EXPECT_EQ(sout.str(), expected_str);
}

// ========== Тесты для Queue ==========

TEST(QueueTest, DefaultConstructor) {
    Queue<int> q;
    EXPECT_TRUE(q.is_empty());
    EXPECT_EQ(q.size(), 0);
}

TEST(QueueTest, PushAndFront) {
    Queue<int> q;
    q.push(1);
    EXPECT_FALSE(q.is_empty());
    EXPECT_EQ(q.size(), 1);
    EXPECT_EQ(q.get_front(), 1);

    q.push(2);
    EXPECT_EQ(q.size(), 2);
    EXPECT_EQ(q.get_front(), 1);
}

TEST(QueueTest, Pop) {
    Queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);

    q.pop();
    EXPECT_EQ(q.size(), 2);
    EXPECT_EQ(q.get_front(), 2);
}

TEST(QueueTest, CopyConstructor) {
    Queue<int> q1;
    q1.push(1);
    q1.push(2);
    q1.push(3);

    Queue<int> q2 = q1;
    EXPECT_EQ(q1.size(), 3);
    EXPECT_EQ(q2.size(), 3);
    EXPECT_EQ(q1.get_front(), 1);
    EXPECT_EQ(q2.get_front(), 1);
}

TEST(QueueTest, MoveConstructor) {
    Queue<int> q1;
    q1.push(1);
    q1.push(2);

    Queue<int> q2 = std::move(q1);
    EXPECT_TRUE(q1.is_empty());
    EXPECT_EQ(q2.size(), 2);
    EXPECT_EQ(q2.get_front(), 1);
}

TEST(QueueTest, CopyAssignment) {
    Queue<int> q1;
    q1.push(1);
    q1.push(2);

    Queue<int> q2;
    q2 = q1;
    EXPECT_EQ(q1.size(), 2);
    EXPECT_EQ(q2.size(), 2);
    EXPECT_EQ(q1.get_front(), 1);
    EXPECT_EQ(q2.get_front(), 1);
}

TEST(QueueTest, MoveAssignment) {
    Queue<int> q1;
    q1.push(1);
    q1.push(2);

    Queue<int> q2;
    q2 = std::move(q1);
    EXPECT_TRUE(q1.is_empty());
    EXPECT_EQ(q2.size(), 2);
    EXPECT_EQ(q2.get_front(), 1);
}

TEST(QueueTest, Iterators) {
    Queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);

    int sum = 0;
    for (auto it = q.begin(); it != q.end(); ++it) {
        sum += *it;
    }
    EXPECT_EQ(sum, 6);
}

TEST(QueueTest, RangeBasedFor) {
    Queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);

    int sum = 0;
    for (const auto& item : q) {
        sum += item;
    }
    EXPECT_EQ(sum, 6);
}

// ========== Тесты для разных типов данных ==========

TEST(StringStackTest, BasicOperations) {
    Stack<std::string> s;
    s.push("hello");
    s.push("world");
    
    EXPECT_EQ(s.size(), 2);
    EXPECT_EQ(s.get_front(), "world");
    
    s.pop();
    EXPECT_EQ(s.get_front(), "hello");
}

TEST(StringQueueTest, BasicOperations) {
    Queue<std::string> q;
    q.push("first");
    q.push("second");
    
    EXPECT_EQ(q.size(), 2);
    EXPECT_EQ(q.get_front(), "first");
    
    q.pop();
    EXPECT_EQ(q.get_front(), "second");
}

TEST(DoubleStackTest, BasicOperations) {
    Stack<double> s;
    s.push(3.14);
    s.push(2.71);
    
    EXPECT_EQ(s.size(), 2);
    EXPECT_DOUBLE_EQ(s.get_front(), 2.71);
    
    s.pop();
    EXPECT_DOUBLE_EQ(s.get_front(), 3.14);
}

// ========== Тесты исключений ==========

TEST(StackExceptionTest, PopEmpty) {
    Stack<int> s;
    EXPECT_THROW(s.pop(), ContainerException);
}

TEST(StackExceptionTest, FrontEmpty) {
    Stack<int> s;
    EXPECT_THROW(s.get_front(), ContainerException);
}

TEST(QueueExceptionTest, PopEmpty) {
    Queue<int> q;
    EXPECT_THROW(q.pop(), ContainerException);
}

TEST(QueueExceptionTest, FrontEmpty) {
    Queue<int> q;
    EXPECT_THROW(q.get_front(), ContainerException);
}

// ========== Тесты полиморфизма ==========

TEST(PolymorphismTest, BaseContainer) {
    Stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);
    
    Queue<int> q;
    q.push(10);
    q.push(20);
    q.push(30);

    fwd_container<int>* containers[] = {&s, &q};
    
    EXPECT_EQ(containers[0]->size(), 3);
    EXPECT_EQ(containers[1]->size(), 3);
    EXPECT_EQ(containers[0]->get_front(), 3);
    EXPECT_EQ(containers[1]->get_front(), 10);
    
    std::stringstream ss1, ss2;
    ss1 << *containers[0];
    ss2 << *containers[1];
    EXPECT_EQ(ss1.str(), "3 2 1");
    EXPECT_EQ(ss2.str(), "10 20 30");
}

// ========== Тесты STL алгоритмов ==========

TEST(STLAlgorithmsTest, StackAlgorithms) {
    Stack<int> s;
    for (int i = 1; i <= 5; ++i) s.push(i);

    auto it = std::find_if(s.begin(), s.end(), [](int v) { return v % 2 == 0; });
    EXPECT_NE(it, s.end());
    EXPECT_EQ(*it, 4);

    int sum = 0;
    std::for_each(s.begin(), s.end(), [&sum](int v) { sum += v; });
    EXPECT_EQ(sum, 15);

    int count_even = std::count_if(s.begin(), s.end(), [](int v) { return v % 2 == 0; });
    EXPECT_EQ(count_even, 2);
}

TEST(STLAlgorithmsTest, QueueAlgorithms) {
    Queue<int> q;
    for (int i = 1; i <= 5; ++i) q.push(i);

    auto it = std::find_if(q.begin(), q.end(), [](int v) { return v % 2 == 0; });
    EXPECT_NE(it, q.end());
    EXPECT_EQ(*it, 2);

    int sum = 0;
    std::for_each(q.begin(), q.end(), [&sum](int v) { sum += v; });
    EXPECT_EQ(sum, 15);
}

// ========== Основная функция ==========

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}