#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <stdexcept>
#include <string>

class ContainerException : public std::runtime_error {
public:
    explicit ContainerException(const std::string& message)
        : std::runtime_error("Container Error: " + message) {}
};

class IteratorException : public ContainerException {
public:
    explicit IteratorException(const std::string& message)
        : ContainerException("Iterator: " + message) {}
};

#endif // EXCEPTION_H