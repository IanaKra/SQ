#include <iostream>
#include <string>
#include <sstream>
#include "Stack.h"
#include "Queue.h"

void demonstrateStack() {
    std::cout << "=== STACK DEMONSTRATION ===" << std::endl;

    Stack<int> s;
    std::cout << "Stack created. Empty: " << std::boolalpha << s.is_empty() << std::endl;
    std::cout << "Size: " << s.size() << std::endl;

    // Добавляем элементы
    std::cout << "\nPushing elements..." << std::endl;
    s.push(1);
    int val = 2;
    s.push(val);
    s.push(3);
    
    std::cout << "After pushing 1, 2, 3: " << s << std::endl;
    std::cout << "Size: " << s.size() << std::endl;
    std::cout << "Top element: " << s.get_front() << std::endl;

    // Удаляем элементы
    std::cout << "\nPopping elements..." << std::endl;
    s.pop();
    std::cout << "After pop: " << s << std::endl;
    std::cout << "Top element: " << s.get_front() << std::endl;

    // Копирование
    std::cout << "\nCopying stack..." << std::endl;
    Stack<int> s_copy = s;
    std::cout << "Original: " << s << std::endl;
    std::cout << "Copy: " << s_copy << std::endl;
    
    // Изменяем копию
    s_copy.push(99);
    std::cout << "After modifying copy:" << std::endl;
    std::cout << "Original: " << s << " (unchanged)" << std::endl;
    std::cout << "Copy: " << s_copy << std::endl;

    // Перемещение
    std::cout << "\nMoving stack..." << std::endl;
    Stack<int> s_moved = std::move(s);
    std::cout << "Moved stack: " << s_moved << std::endl;
    std::cout << "Original stack after move: " << s << " (empty)" << std::endl;
    std::cout << "Original is empty: " << s.is_empty() << std::endl;

    // Демонстрация итераторов
    std::cout << "\nStack elements using iterators: ";
    for (auto it = s_moved.begin(); it != s_moved.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Range-based for loop
    std::cout << "Stack elements using range-based for: ";
    for (const auto& item : s_moved) {
        std::cout << item << " ";
    }
    std::cout << std::endl;

    // cbegin/cend
    std::cout << "Stack elements using cbegin/cend: ";
    for (auto it = s_moved.cbegin(); it != s_moved.cend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

void demonstrateQueue() {
    std::cout << "\n\n=== QUEUE DEMONSTRATION ===" << std::endl;

    Queue<std::string> q;
    std::cout << "Queue created. Empty: " << std::boolalpha << q.is_empty() << std::endl;
    std::cout << "Size: " << q.size() << std::endl;

    // Добавляем элементы
    std::cout << "\nPushing elements..." << std::endl;
    q.push("First");
    q.push("Second");
    q.push("Third");
    
    std::cout << "After pushing three elements: " << q << std::endl;
    std::cout << "Size: " << q.size() << std::endl;
    std::cout << "Front element: " << q.get_front() << std::endl;

    // Удаляем элементы
    std::cout << "\nPopping elements..." << std::endl;
    q.pop();
    std::cout << "After pop: " << q << std::endl;
    std::cout << "Front element: " << q.get_front() << std::endl;
    std::cout << "Size: " << q.size() << std::endl;

    // Копирование
    std::cout << "\nCopying queue..." << std::endl;
    Queue<std::string> q_copy = q;
    std::cout << "Original: " << q << std::endl;
    std::cout << "Copy: " << q_copy << std::endl;
    
    // Изменяем копию
    q_copy.push("Copy_Element");
    std::cout << "After modifying copy:" << std::endl;
    std::cout << "Original: " << q << " (unchanged)" << std::endl;
    std::cout << "Copy: " << q_copy << std::endl;

    // Перемещение
    std::cout << "\nMoving queue..." << std::endl;
    Queue<std::string> q_moved = std::move(q);
    std::cout << "Moved queue: " << q_moved << std::endl;
    std::cout << "Original queue after move: " << q << " (empty)" << std::endl;
    std::cout << "Original is empty: " << q.is_empty() << std::endl;

    // Демонстрация итераторов
    std::cout << "\nQueue elements using iterators: ";
    for (auto it = q_moved.begin(); it != q_moved.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Range-based for loop
    std::cout << "Queue elements using range-based for: ";
    for (const auto& item : q_moved) {
        std::cout << item << " ";
    }
    std::cout << std::endl;

    // cbegin/cend
    std::cout << "Queue elements using cbegin/cend: ";
    for (auto it = q_moved.cbegin(); it != q_moved.cend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

void demonstrateExceptions() {
    std::cout << "\n\n=== EXCEPTION SAFETY DEMONSTRATION ===" << std::endl;
    
    std::cout << "\nTesting empty stack operations:" << std::endl;
    try {
        Stack<int> empty_stack;
        std::cout << "Attempting to pop from empty stack..." << std::endl;
        empty_stack.pop();
        std::cout << "ERROR: Should have thrown exception!" << std::endl;
    } catch (const ContainerException& e) {
        std::cout << "Caught expected exception: " << e.what() << std::endl;
    }
    
    try {
        Stack<int> empty_stack;
        std::cout << "Attempting to get front from empty stack..." << std::endl;
        empty_stack.get_front();
        std::cout << "ERROR: Should have thrown exception!" << std::endl;
    } catch (const ContainerException& e) {
        std::cout << "Caught expected exception: " << e.what() << std::endl;
    }
    
    std::cout << "\nTesting empty queue operations:" << std::endl;
    try {
        Queue<int> empty_queue;
        std::cout << "Attempting to pop from empty queue..." << std::endl;
        empty_queue.pop();
        std::cout << "ERROR: Should have thrown exception!" << std::endl;
    } catch (const ContainerException& e) {
        std::cout << "Caught expected exception: " << e.what() << std::endl;
    }
    
    try {
        Queue<int> empty_queue;
        std::cout << "Attempting to get front from empty queue..." << std::endl;
        empty_queue.get_front();
        std::cout << "ERROR: Should have thrown exception!" << std::endl;
    } catch (const ContainerException& e) {
        std::cout << "Caught expected exception: " << e.what() << std::endl;
    }
}

void demonstratePolymorphism() {
    std::cout << "\n\n=== POLYMORPHISM DEMONSTRATION ===" << std::endl;
    
    Stack<int>* stack = new Stack<int>();
    stack->push(1);
    stack->push(2);
    stack->push(3);

    Queue<int>* queue = new Queue<int>();
    queue->push(10);
    queue->push(20);
    queue->push(30);

    fwd_container<int>* container1 = stack;
    fwd_container<int>* container2 = queue;

    std::cout << "Stack via fwd_container pointer: " << *container1 << std::endl;
    std::cout << "Queue via fwd_container pointer: " << *container2 << std::endl;

    delete stack;
    delete queue;
}

int main() {
    try {
        demonstrateStack();
        demonstrateQueue();
        demonstrateExceptions();
        demonstratePolymorphism();

        std::cout << "\n\n=== ALL DEMONSTRATIONS COMPLETED SUCCESSFULLY ===" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}