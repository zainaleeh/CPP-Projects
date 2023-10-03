#ifndef DEQUE_EMPTY_EXCEPTION
#define DEQUE_EMPTY_EXCEPTION

#include "RuntimeException.hpp"
#include <string>

class DequeEmptyException : public RuntimeException {
public:
  DequeEmptyException(const std::string &err) : RuntimeException(err) {}
};

#endif