#ifndef NODE_HPP
#define NODE_HPP

#include "Node.h"

template<typename T>
Node<T>::Node(const T& value) 
    : data(value), next(nullptr) {}

template<typename T>
Node<T>::Node(T&& value) 
    : data(std::move(value)), next(nullptr) {}

#endif // NODE_HPP