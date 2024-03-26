#include "sorted_list.hpp"

template <typename T, typename L>
SortedList<T, L>::SortedList()
{
  // nothing to do, plist gets created on the stack
}

template <typename T, typename L>
SortedList<T, L>::SortedList(const SortedList<T, L> & x)
{
  plist = x.plist; // use copy assignment to implement copy construction
}

template <typename T, typename L>
SortedList<T, L>& SortedList<T, L>::operator=(SortedList<T, L> x)
{
  plist = x.plist;
  return *this;
}

template <typename T, typename L>
SortedList<T, L>::~SortedList()
{
  // plist destructor gets called automatically
}

template <typename T, typename L>
bool SortedList<T, L>::isEmpty() const noexcept
{
  return plist.isEmpty();
}

template <typename T, typename L>
std::size_t SortedList<T, L>::getLength() const noexcept
{
  return plist.getLength();
}

template <typename T, typename L>
void SortedList<T, L>::insert(const T& item)
{
  //if list is empty insert at first position
  if (isEmpty()) {
    plist.insert(0, item);
  } 
  else {
    //find index to insert
    int i = 0;
    while (i < getLength() && item > getEntry(i)) {
      i++;
    }
    //insert item at traversed index
    plist.insert(i, item);
  }
}

template <typename T, typename L>
void SortedList<T, L>::remove(const T& item)
{
  //cannot remove something from an empty list
  if(isEmpty()) 
  throw std::range_error("cannot remove from an empty list");

  bool occur = 0;
  int index = -1;
  //find item to be removed and index it occurs at if it is present in the list
  for (int i = 0; i < getLength()-1; i++) {
    if (getEntry(i) == item) {
      index = i;
      occur = true;
    }
  }
  //cannot remove item that is not within original list
  if (occur == false) {
    throw std::range_error("is not in list");
  } 
  else {
    plist.remove(index);
  }
}

template <typename T, typename L>
void SortedList<T, L>::removeAt(std::size_t position)
{
  plist.remove(position);
}

template <typename T, typename L>
void SortedList<T, L>::clear()
{
  plist.clear();
}

template <typename T, typename L>
T SortedList<T, L>::getEntry(std::size_t position) const
{
  return plist.getEntry(position);
}

template <typename T, typename L>
long int SortedList<T, L>::getPosition(const T& newValue)
{
  //cannot have an index of an empty list
  if (isEmpty()) {
    return -1;
  }

  int index = -1;
  for (int i = 0; i < getLength(); i++) {
    if (getEntry(i) == newValue) {
      index = i;
      return index;
    }
  }
  return index;
}