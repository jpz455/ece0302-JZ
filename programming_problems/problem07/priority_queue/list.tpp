#include "list.hpp"

template <typename T>
List<T>::List()
{
  headptr=nullptr;
  listSize=0;
}

template <typename T>
List<T>::~List()
{
 clear(); 
}

template <typename T>
List<T>::List(const List<T>& x)
{
  headptr=nullptr;
  listSize=0;
  Node<T> *presentNode = x.headptr; //assign new node to parameter list
  while(presentNode!=nullptr){ //loops through every pointer of the list
    insert(listSize,presentNode->getItem()); //insert item from original list to current node pointer
    presentNode=presentNode->getNext(); //increment node
  }
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
  std::swap(headptr,x.headptr);
  std::swap(listSize,x.listSize);
}

template <typename T>
bool List<T>::isEmpty() const noexcept
{
  return (listSize==0);
}

template <typename T>
std::size_t List<T>::getLength() const noexcept
{
  return listSize;
}

template <typename T>
void List<T>::insert(std::size_t position, const T& item)
{
 if (position > listSize||position < 0) {
        throw std::range_error("out of range");
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
}

template <typename T>
void List<T>::remove(std::size_t position)
{
 if (position >= listSize || isEmpty()) {
        throw std::range_error("Invalid");
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
}

template <typename T>
void List<T>::clear()
{
 while (!isEmpty()) { //have to increment through multiple pointers for every item in the list 
        remove(0);    //cannot just set size to 0 and set head pointer to null
    }
}

template <typename T>
T List<T>::getEntry(std::size_t position) const
{
    if (position >= listSize || position < 0) { 
        throw std::range_error("Invalid position");
    }
    Node<T>* current = headptr; //temporary node pointer to head pointer
    for (std::size_t i = 0; i < position; ++i) {
        current = current->getNext(); //increment placeholder pointer until position wanted
    }
    return current->getItem(); //return that index
}

template <typename T>
void List<T>::setEntry(std::size_t position, const T& newValue)
{
 if (position >= listSize || position < 0) { 
        throw std::range_error("Invalid position");
    }
   if (position < listSize) { //can only set entry for position within the list size
        Node<T>* current = headptr; //temporary pointer to find the entry
        for (std::size_t i = 0; i < position; ++i) {
            current = current->getNext(); //increment temporary pointer to find the entry
        }
        current->setItem(newValue); //set that pointer to parameter value
    }
}
