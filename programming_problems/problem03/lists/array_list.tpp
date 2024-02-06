#include "array_list.hpp"

template <typename T>
ArrayList<T>::ArrayList(): AbstractList<T>(),listSize(0),arrayList(nullptr){}

template <typename T>
ArrayList<T>::~ArrayList() {
  delete [] arrayList;
}

template <typename T>
ArrayList<T>::ArrayList(const ArrayList& rhs): AbstractList<T>(), listSize(rhs.listSize){
  arrayList = new T[listSize];
  std::copy(rhs.arrayList,rhs.arrayList+listSize,arrayList);

}

template <typename T>
ArrayList<T>& ArrayList<T>::operator=(ArrayList rhs){
  swap(rhs);
  return *this;
}

template <typename T>
void ArrayList<T>::swap(ArrayList& rhs) {
  std::swap(arrayList,rhs.arrayList);
  std::swap(listSize,rhs.listSize);
}

template <typename T>
bool ArrayList<T>::isEmpty() const noexcept {
  if(listSize==0){
    return true;
  }
  else
  return false;
}

template <typename T>
std::size_t ArrayList<T>::getLength() const noexcept {
  return listSize;
}

template <typename T>
bool ArrayList<T>::insert(std::size_t position, const T& item){
  if (position > listSize) {
        return false;
    }
    T* newArray = new T[listSize + 1]; 
    std::copy(arrayList, arrayList + position, newArray); 
    newArray[position] = item; 
    std::copy(arrayList + position, arrayList + listSize, newArray + position + 1); 
    delete[] arrayList; 
    arrayList = newArray; 
    ++listSize; 
    return true;
}


template <typename T>
bool ArrayList<T>::remove(std::size_t position){
  if (position >= listSize) {
        return false;
    }
    for (std::size_t i = position; i < listSize - 1; ++i) {
        arrayList[i] = arrayList[i + 1];
    }
    --listSize;
    return true;
}

template <typename T>
void ArrayList<T>::clear() {
  listSize=0;
  arrayList=nullptr;
}

template <typename T>
T ArrayList<T>::getEntry(std::size_t position) const {
  if (position >= listSize) {
        return T();
    }
    return arrayList[position];
}

template <typename T>
void ArrayList<T>::setEntry(std::size_t position, const T& newValue) {
  if (position < listSize) {
        arrayList[position] = newValue;
    }
}
