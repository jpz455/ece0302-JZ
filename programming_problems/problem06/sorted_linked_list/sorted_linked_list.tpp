#include "sorted_linked_list.hpp"
#include <stdexcept>

template <typename T>
SortedLinkedList<T>::SortedLinkedList(): LinkedList<T>()
{
}

template <typename T>
SortedLinkedList<T>::SortedLinkedList(LinkedList<T> unsorted_list) 
{
  for (int i = 0; i < unsorted_list.getLength(); ++i) {
        insert(unsorted_list.getEntry(i)); //sorting
    }
}

template <typename T>
SortedLinkedList<T>::SortedLinkedList(const SortedLinkedList<T> & x):
  LinkedList<T>(x)
{
}

template <typename T>
SortedLinkedList<T>& SortedLinkedList<T>::operator=(SortedLinkedList<T> x)
{
  LinkedList<T>::operator=(x);
  return *this;
}

template <typename T>
SortedLinkedList<T>::~SortedLinkedList()
{
  // base destructor gets called automatically
}

template <typename T>
bool SortedLinkedList<T>::isEmpty() const noexcept
{
  return LinkedList<T>::isEmpty();
}

template <typename T>
std::size_t SortedLinkedList<T>::getLength() const noexcept
{
  return LinkedList<T>::getLength();
}

template <typename T>
void SortedLinkedList<T>::insert(const T& item)
{
   std::size_t index = 0;
    if (isEmpty()) {
        LinkedList<T>::insert(index, item); //empty list means insert as first item
        return;
    }

    while (index < getLength() && item > getEntry(index)) {
        index++; ///traverse list
    }

    if (index > getLength()) {
        throw std::range_error("out of range"); //cannot insert something that it outside of the length
    }

    LinkedList<T>::insert(index, item);
}

template <typename T>
void SortedLinkedList<T>::remove(const T& item)
{
  if(isEmpty()) {
  throw std::range_error("cannot remove from empty list");
  }
  std::size_t index = 0;
  while(index < getLength()){
    if (getEntry(index) == item){ //find index of item to be removed
      break;
    }
    else{
      index++;
    }
  } 
  LinkedList<T>::remove(index + 1);
}

template <typename T>
void SortedLinkedList<T>::removeAt(std::size_t position)
{
 if (isEmpty()) {
        throw std::range_error("Cannot remove from an empty list");
    }
    if (position >= getLength() || position < 0) {
        throw std::range_error("Invalid position");
    }
    LinkedList<T>::remove(position);
}

template <typename T>
void SortedLinkedList<T>::clear()
{
  LinkedList<T>::clear();
}

template <typename T>
T SortedLinkedList<T>::getEntry(std::size_t position) const
{
 if(isEmpty() || position < 0 || position >= getLength()) {
    throw std::range_error("invalid");
  }
  return LinkedList<T>::getEntry(position);
}

template <typename T>
long int SortedLinkedList<T>::getPosition(const T& item)
{
   long int index = 0;
    while (index < getLength() && item > getEntry(index)) {
        index++;
    }
    if (index < getLength() && getEntry(index) == item) {
        return index;
    }
    return -1;
}
