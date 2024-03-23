#include "list.hpp"

template <typename T>
List<T>::List()
{
  //TODO
}

template <typename T>
List<T>::~List()
{
  //TODO
}

template <typename T>
List<T>::List(const List<T>& x)
{
  elements = x.elements;
}

template <typename T>
List<T>& List<T>::operator=(List<T> x)
{
  swap(x); 
    return *this;
}

template <typename T>
void List<T>::swap(List<T>& x) 
{
  elements.swap(x.elements);
}

template <typename T>
bool List<T>::isEmpty() const noexcept
{
  return elements.empty(); 
}

template <typename T>
std::size_t List<T>::getLength() const noexcept
{
  return elements.size();
}

template <typename T>
void List<T>::insert(std::size_t position, const T& item)
{
  if (position <= elements.size()) {
        elements.insert(elements.begin() + position, item);
    } else {
        throw std::out_of_range("Position out of range");
    }
}

template <typename T>
void List<T>::remove(std::size_t position)
{
  if (position < elements.size()) {
        elements.erase(elements.begin() + position);
    } else {
        // Handle out-of-range position
        throw std::out_of_range("Position out of range");
    }
}

template <typename T>
void List<T>::clear()
{
  elements.clear();
}

template <typename T>
T List<T>::getEntry(std::size_t position) const
{
  if (position < elements.size()) {
        return elements[position];
    } else {
        // Handle out-of-range position
        throw std::out_of_range("Position out of range");
    }
}

template <typename T>
void List<T>::setEntry(std::size_t position, const T& newValue)
{
   if (position < elements.size()) {
        elements[position] = newValue;
    } else {
        // Handle out-of-range position
        throw std::out_of_range("Position out of range");
    }
}
