#ifndef CONTAINERS_H
#define CONTAINERS_H

#include "Exception.h"
#include <iostream>
#include <iterator>

template<typename T>
class fwd_container {
public:
    class iterator_base {
    public:
        virtual ~iterator_base() = default;
        virtual void* get_node() = 0;
        virtual const void* get_node() const = 0;
        virtual T& deref() = 0;
        virtual void increment() = 0;
        virtual iterator_base* clone() const = 0;
        virtual bool equals(const iterator_base* other) const = 0;
    };

    class const_iterator_base {
    public:
        virtual ~const_iterator_base() = default;
        virtual const void* get_node() const = 0;
        virtual const T& deref() const = 0;
        virtual void increment() = 0;
        virtual const_iterator_base* clone() const = 0;
        virtual bool equals(const const_iterator_base* other) const = 0;
    };

    class iterator;
    class const_iterator;
    
    virtual ~fwd_container() = default;
    
    virtual void push(const T& value) = 0;
    virtual void push(T&& value) = 0;
    virtual void pop() = 0;
    virtual T& get_front() = 0;
    virtual const T& get_front() const = 0;
    virtual bool is_empty() const = 0;
    virtual size_t size() const = 0;
    
    virtual iterator begin() = 0;
    virtual iterator end() = 0;
    virtual const_iterator cbegin() const = 0;
    virtual const_iterator cend() const = 0;
    
    const_iterator begin() const { return cbegin(); }
    const_iterator end() const { return cend(); }
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const fwd_container<T>& container);

template<typename T>
std::istream& operator>>(std::istream& is, fwd_container<T>& container);

#include "Containers.hpp"
#endif // CONTAINERS_H