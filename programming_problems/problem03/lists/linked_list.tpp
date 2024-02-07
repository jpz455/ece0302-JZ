#include "linked_list.hpp"

template <typename T>
LinkedList<T>::LinkedList():headptr(nullptr),listSize(0){}

template <typename T>
LinkedList<T>::~LinkedList()
{
  clear();
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& x):headptr(nullptr),listSize(0)
{
  Node<T> *presentNode = x.headptr;
  while(presentNode!=nullptr){
    insert(listSize,presentNode->getItem());
    presentNode=presentNode->getNext();
  }

}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList<T> x)
{
  swap(x);
  return *this;
}

template <typename T>
void LinkedList<T>::swap(LinkedList& x) 
{
  std::swap(headptr,x.headptr);
  std::swap(listSize,x.listSize);
}

template <typename T>
bool LinkedList<T>::isEmpty() const noexcept
{
  return (listSize==0);
}

template <typename T>
std::size_t LinkedList<T>::getLength() const noexcept
{
  return listSize;
}

template <typename T>
bool LinkedList<T>::insert(std::size_t position, const T& item)
{
  if (position > listSize) {
        return false;
    }
    if (position == 0) {
        headptr = new Node<T>(item, headptr);
    } else {
        Node<T>* current = headptr;
        for (std::size_t i = 0; i < position - 1; ++i) {
            current = current->getNext();
        }
        current->setNext(new Node<T>(item, current->getNext()));
    }
    ++listSize;
    return true;
}

template <typename T>
bool LinkedList<T>::remove(std::size_t position)
{
  if (position >= listSize || isEmpty()) {
        return false;
    }
    Node<T>* temp = nullptr;
    if (position == 0) {
        temp = headptr;
        headptr = headptr->getNext();
    } else {
        Node<T>* current = headptr;
        for (std::size_t i = 0; i < position - 1; ++i) {
            current = current->getNext();
        }
        temp = current->getNext();
        current->setNext(temp->getNext());
    }
    delete temp;
    --listSize;
    return true;
}

template <typename T>
void LinkedList<T>::clear()
{
  while (!isEmpty()) {
        remove(0);
    }
}

template <typename T>
T LinkedList<T>::getEntry(std::size_t position) const
{
  if (position >= listSize) {
       return T();
  }
    Node<T>* current = headptr;
    for (std::size_t i = 0; i < position; ++i) {
        current = current->getNext();
    }
    return current->getItem();
}

template <typename T>
void LinkedList<T>::setEntry(std::size_t position, const T& newValue)
{
  if (position < listSize) {
        Node<T>* current = headptr;
        for (std::size_t i = 0; i < position; ++i) {
            current = current->getNext();
        }
        current->setItem(newValue);
    }
}
