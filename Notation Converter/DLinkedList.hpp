#ifndef DLINKEDLIST
#define DLINKEDLIST

template <typename E> class DNode {
public:
  DNode() {}

private:
  E elem;
  DNode<E> *prev;
  DNode<E> *next;

  template <typename T> friend class DLinkedList;
};

template <typename E> class DLinkedList {
public:
  DLinkedList();
  ~DLinkedList();
  bool empty() const;
  const E &front() const;
  const E &back() const;
  void addFront(const E &e);
  void addBack(const E &e);
  void removeFront();
  void removeBack();
  int getSize() { return nElem; }

private:
  int nElem = 0;
  DNode<E> *header;
  DNode<E> *trailer;

protected:
  void add(DNode<E> *v, const E &e);
  void remove(DNode<E> *v);
};

// default constuctor
template <typename E> DLinkedList<E>::DLinkedList() {
  // create sentinel nodes
  header = new DNode<E>;
  trailer = new DNode<E>;

  // point them to each other
  header->next = trailer;
  trailer->prev = header;
}

template <typename E> bool DLinkedList<E>::empty() const {
  return header->next == trailer;
}

template <typename E> const E &DLinkedList<E>::front() const {
  return header->next->elem;
}

template <typename E> const E &DLinkedList<E>::back() const {
  return trailer->prev->elem;
}

template <typename E> DLinkedList<E>::~DLinkedList() {
  while (!empty())
    removeFront();
  delete header;
  delete trailer;
}

// insert new node before node 'v'
template <typename E> void DLinkedList<E>::add(DNode<E> *v, const E &e) {
  DNode<E> *u = new DNode<E>;
  u->elem = e;
  u->next = v;
  u->prev = v->prev;

  u->prev->next = u;
  v->prev = u;

  nElem++;
}

template <typename E> void DLinkedList<E>::remove(DNode<E> *v) {
  DNode<E> *u = v->prev;
  DNode<E> *w = v->next;
  u->next = w;
  w->prev = u;
  delete v;

  nElem--;
}

template <typename E> void DLinkedList<E>::addFront(const E &e) {
  add(header->next, e);
}

template <typename E> void DLinkedList<E>::addBack(const E &e) {
  add(trailer, e);
}

template <typename E> void DLinkedList<E>::removeFront() {
  remove(header->next);
}

template <typename E> void DLinkedList<E>::removeBack() {
  remove(trailer->prev);
}

#endif