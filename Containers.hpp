#ifndef CONTAINERS_HPP
#define CONTAINERS_HPP

#include "Containers.h"

template<typename T>
class fwd_container<T>::iterator {
private:
    iterator_base* impl;
    
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;
    
    iterator() : impl(nullptr) {}
    explicit iterator(iterator_base* impl_) : impl(impl_) {}
    
    iterator(const iterator& other) : impl(other.impl ? other.impl->clone() : nullptr) {}
    iterator(iterator&& other) noexcept : impl(other.impl) {
        other.impl = nullptr;
    }
    
    ~iterator() { delete impl; }
    
    iterator& operator=(const iterator& other) {
        if (this != &other) {
            delete impl;
            impl = other.impl ? other.impl->clone() : nullptr;
        }
        return *this;
    }
    
    iterator& operator=(iterator&& other) noexcept {
        if (this != &other) {
            delete impl;
            impl = other.impl;
            other.impl = nullptr;
        }
        return *this;
    }
    
    reference operator*() {
        return impl->deref();
    }
    
    pointer operator->() {
        return &impl->deref();
    }
    
    iterator& operator++() {
        impl->increment();
        return *this;
    }
    
    iterator operator++(int) {
        iterator temp = *this;
        ++(*this);
        return temp;
    }
    
    bool operator==(const iterator& other) const {
        if (!impl && !other.impl) return true;
        if (!impl || !other.impl) return false;
        return impl->equals(other.impl);
    }
    
    bool operator!=(const iterator& other) const {
        return !(*this == other);
    }
    
    bool operator==(const const_iterator& other) const;
    bool operator!=(const const_iterator& other) const;
};

template<typename T>
class fwd_container<T>::const_iterator {
private:
    const_iterator_base* impl;
    
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = const T*;
    using reference = const T&;
    
    const_iterator() : impl(nullptr) {}
    explicit const_iterator(const_iterator_base* impl_) : impl(impl_) {}
    
    const_iterator(const const_iterator& other) : impl(other.impl ? other.impl->clone() : nullptr) {}
    const_iterator(const_iterator&& other) noexcept : impl(other.impl) {
        other.impl = nullptr;
    }
    
    ~const_iterator() { delete impl; }
    
    const_iterator& operator=(const const_iterator& other) {
        if (this != &other) {
            delete impl;
            impl = other.impl ? other.impl->clone() : nullptr;
        }
        return *this;
    }
    
    const_iterator& operator=(const_iterator&& other) noexcept {
        if (this != &other) {
            delete impl;
            impl = other.impl;
            other.impl = nullptr;
        }
        return *this;
    }
    
    reference operator*() const {
        return impl->deref();
    }
    
    pointer operator->() const {
        return &impl->deref();
    }
    
    const_iterator& operator++() {
        impl->increment();
        return *this;
    }
    
    const_iterator operator++(int) {
        const_iterator temp = *this;
        ++(*this);
        return temp;
    }
    
    bool operator==(const const_iterator& other) const {
        if (!impl && !other.impl) return true;
        if (!impl || !other.impl) return false;
        return impl->equals(other.impl);
    }
    
    bool operator!=(const const_iterator& other) const {
        return !(*this == other);
    }
    
    bool operator==(const iterator& other) const;
    bool operator!=(const iterator& other) const;
};

template<typename T>
bool fwd_container<T>::iterator::operator==(const const_iterator& other) const {
    if (!impl && !other.impl) return true;
    if (!impl || !other.impl) return false;
    return impl->get_node() == other.impl->get_node();
}

template<typename T>
bool fwd_container<T>::iterator::operator!=(const const_iterator& other) const {
    return !(*this == other);
}

template<typename T>
bool fwd_container<T>::const_iterator::operator==(const iterator& other) const {
    if (!impl && !other.impl) return true;
    if (!impl || !other.impl) return false;
    return impl->get_node() == other.impl->get_node();
}

template<typename T>
bool fwd_container<T>::const_iterator::operator!=(const iterator& other) const {
    return !(*this == other);
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const fwd_container<T>& container) {
    bool first = true;
    for (const auto& item : container) {
        if (!first) os << " ";
        os << item;
        first = false;
    }
    return os;
}

template<typename T>
std::istream& operator>>(std::istream& is, fwd_container<T>& container) {
    T value;
    while (is >> value) {
        container.push(value);
    }
    return is;
}

#endif // CONTAINERS_HPP