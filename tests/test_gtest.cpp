#include <gtest/gtest.h>
#include <string>
#include <sstream>
#include <algorithm>
#include "Stack.h"
#include "Queue.h"

// ========== Тесты для Stack (20 тестов) ==========

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

    int expected1[] = {3, 2, 1};
    int idx = 0;
    for (const auto& v : s) EXPECT_EQ(v, expected1[idx++]);

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

TEST(StackTest, ComplexOperations) {
    Stack<int> s;
    
    for (int i = 0; i < 100; ++i) {
        s.push(i);
    }
    EXPECT_EQ(s.size(), 100);
    EXPECT_EQ(s.get_front(), 99);
    
    for (int i = 99; i >= 50; --i) {
        EXPECT_EQ(s.get_front(), i);
        s.pop();
    }
    EXPECT_EQ(s.size(), 50);
    
    s.push(1000);
    s.push(2000);
    s.pop();
    s.push(3000);
    
    EXPECT_EQ(s.get_front(), 3000);
    EXPECT_EQ(s.size(), 52);
}

TEST(StackTest, AssignmentChain) {
    Stack<int> s1, s2, s3;
    
    s1.push(1);
    s1.push(2);
    s1.push(3);
    
    s2 = s1;
    s3 = s2 = s1;
    
    EXPECT_EQ(s1.size(), 3);
    EXPECT_EQ(s2.size(), 3);
    EXPECT_EQ(s3.size(), 3);
    
    s1.push(4);
    EXPECT_EQ(s1.size(), 4);
    EXPECT_EQ(s2.size(), 3);
    EXPECT_EQ(s3.size(), 3);
}

TEST(StackTest, SelfAssignment) {
    Stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);
    
    s = s;
    
    EXPECT_EQ(s.size(), 3);
    
    int expected[] = {3, 2, 1};
    int idx = 0;
    for (const auto& v : s) {
        EXPECT_EQ(v, expected[idx++]);
    }
}

// ========== Тесты для Queue (20 тестов) ==========

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

TEST(QueueTest, IteratorModification) {
    Queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);

    for (auto it = q.begin(); it != q.end(); ++it) {
        *it *= 2;
    }

    EXPECT_EQ(q.get_front(), 2);
    q.pop();
    EXPECT_EQ(q.get_front(), 4);
    q.pop();
    EXPECT_EQ(q.get_front(), 6);
}

TEST(QueueTest, Queue_Iterator) {
    Queue<int> q;
    q.push(10);
    q.push(20);
    q.push(30);

    Queue<int>::iterator it = q.begin();
    EXPECT_EQ(*it, 10);
    ++it;
    EXPECT_EQ(*it, 20);
    it++;
    EXPECT_EQ(*it, 30);
    ++it;
    EXPECT_EQ(it, q.end());

    std::stringstream sout;
    sout << q;
    EXPECT_EQ(sout.str(), "10 20 30");
}

TEST(QueueTest, Queue_For) {
    Queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);

    int expected1[] = {1, 2, 3};
    int idx = 0;
    for (const auto& v : q) EXPECT_EQ(v, expected1[idx++]);

    idx = 0;
    for (auto& v : q) v *= 2;

    int expected2[] = {2, 4, 6};
    idx = 0;
    for (const auto& v : q) EXPECT_EQ(v, expected2[idx++]);
}

TEST(QueueTest, Queue_PushPopCopy) {
    Queue<int> q1;
    q1.push(1);
    q1.push(2);
    q1.push(3);

    q1.pop();
    q1.push(10);
    q1.push(20);

    Queue<int> q2 = q1;

    int expected_orig[] = {2, 3, 10, 20};
    int idx = 0;
    for (const auto& v : q1) EXPECT_EQ(v, expected_orig[idx++]);

    q2.pop();
    q2.pop();
    q2.push(99);
    q2.push(98);
    q2.push(97);

    idx = 0;
    int expected_copy[] = {10, 20, 99, 98, 97};
    idx = 0;
    for (const auto& v : q2) EXPECT_EQ(v, expected_copy[idx++]);
}

TEST(QueueTest, Queue_IO) {
    Queue<int> q;
    q.push(0);

    std::stringstream sin("1 2 3 4 5");
    sin >> q;

    EXPECT_EQ(q.size(), 6);

    int expected[] = {0, 1, 2, 3, 4, 5};
    int idx = 0;
    for (const auto& v : q) EXPECT_EQ(v, expected[idx++]);

    std::stringstream sout;
    sout << q;
    std::string expected_str = "0 1 2 3 4 5";
    EXPECT_EQ(sout.str(), expected_str);
}

TEST(QueueTest, ComplexOperations) {
    Queue<int> q;
    
    for (int i = 0; i < 100; ++i) {
        q.push(i);
    }
    EXPECT_EQ(q.size(), 100);
    EXPECT_EQ(q.get_front(), 0);
    
    for (int i = 0; i < 50; ++i) {
        EXPECT_EQ(q.get_front(), i);
        q.pop();
    }
    EXPECT_EQ(q.size(), 50);
    
    q.push(1000);
    q.push(2000);
    q.pop();
    q.push(3000);
    
    EXPECT_EQ(q.get_front(), 51);
    EXPECT_EQ(q.size(), 52);
}

TEST(QueueTest, AssignmentChain) {
    Queue<int> q1, q2, q3;
    
    q1.push(1);
    q1.push(2);
    q1.push(3);
    
    q2 = q1;
    q3 = q2 = q1;
    
    EXPECT_EQ(q1.size(), 3);
    EXPECT_EQ(q2.size(), 3);
    EXPECT_EQ(q3.size(), 3);
    
    q1.push(4);
    EXPECT_EQ(q1.size(), 4);
    EXPECT_EQ(q2.size(), 3);
    EXPECT_EQ(q3.size(), 3);
}

TEST(QueueTest, SelfAssignment) {
    Queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);
    
    q = q;
    
    EXPECT_EQ(q.size(), 3);
    
    int expected[] = {1, 2, 3};
    int idx = 0;
    for (const auto& v : q) {
        EXPECT_EQ(v, expected[idx++]);
    }
}

// ========== Тесты для разных типов данных (3 теста) ==========

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

// ========== Тесты исключений (4 теста) ==========

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

// ========== Тесты полиморфизма (1 тест) ==========

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

// ========== Тесты STL алгоритмов (2 теста) ==========

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

TEST(QueueTest, LargeQueueOperations) {
    Queue<int> q;
    const int N = 1000;
    
    // Добавляем много элементов
    for (int i = 0; i < N; ++i) {
        q.push(i);
    }
    EXPECT_EQ(q.size(), N);
    EXPECT_EQ(q.get_front(), 0);
    
    // Удаляем половину
    for (int i = 0; i < N/2; ++i) {
        EXPECT_EQ(q.get_front(), i);
        q.pop();
    }
    EXPECT_EQ(q.size(), N/2);
    
    // Добавляем еще элементы
    for (int i = 0; i < N/2; ++i) {
        q.push(i + N);
    }
    EXPECT_EQ(q.size(), N);
    
    // Проверяем порядок оставшихся элементов
    for (int i = N/2; i < N; ++i) {
        EXPECT_EQ(q.get_front(), i);
        q.pop();
    }
    
    // Проверяем порядок добавленных элементов
    for (int i = 0; i < N/2; ++i) {
        EXPECT_EQ(q.get_front(), i + N);
        q.pop();
    }
    
    EXPECT_TRUE(q.is_empty());
}
