#ifndef LINKED_DEQUE
#define LINKED_DEQUE

#include "DLinkedList.hpp"
#include "exceptions/DequeEmptyException.hpp"
#include <iostream>

template <typename T> class LinkedDeque {
public:
  LinkedDeque() : D(), numElem(0) {}
  int size() const {return numElem;}
  bool empty() const {return numElem == 0;}

  const T &front() const noexcept(false);
  const T &back() const noexcept(false);

  void insertFront(const T &e);
  void insertBack(const T &e);

  void removeFront() noexcept(false);
  void removeBack() noexcept(false);

  void print();

private:
  DLinkedList<T> D;
  int numElem;
};

template <typename T> const T &LinkedDeque<T>::front() const noexcept(false) {
  if (empty()) {
    throw DequeEmptyException("Front of empty deque");
  }
  return D.front();
}

template <typename T> const T &LinkedDeque<T>::back() const noexcept(false) {
  if (empty()) {
    throw DequeEmptyException("Back of empty deque");
  }
  return D.back();
}

template <typename T> void LinkedDeque<T>::insertFront(const T &e) {
  D.addFront(e);
  numElem++;

}

template <typename T> void LinkedDeque<T>::insertBack(const T &e) {
  D.addBack(e);
  numElem++;
}

template <typename T> void LinkedDeque<T>::removeFront() noexcept(false) {
  if (empty()) {
    throw DequeEmptyException("removeFront of empty deque");
  }
  D.removeFront();
  numElem--;
}

template <typename T> void LinkedDeque<T>::removeBack() noexcept(false) {
  if (empty()) {
    throw DequeEmptyException("removeBack of empty deque");
  }
  D.removeBack();
  numElem--;
}

template <typename T> void LinkedDeque<T>::print() {
    LinkedDeque<T> p;

  while (!empty()) {
    std::cout << front() << " ";
    p.insertFront(front());
    removeFront();
  }
  std::cout << std::endl;

  while (!p.empty()) {
    insertFront(p.front());
    p.removeFront();
  }
}



#endif