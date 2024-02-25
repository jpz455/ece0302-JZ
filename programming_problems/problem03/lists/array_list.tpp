#include "array_list.hpp"

template <typename T>
ArrayList<T>::ArrayList(): AbstractList<T>(){
  listSize=0;
  arrayList=nullptr;
}

template <typename T>
ArrayList<T>::~ArrayList() {
  delete [] arrayList; //deallocating
}

template <typename T>
ArrayList<T>::ArrayList(const ArrayList& rhs): AbstractList<T>() {
  listSize=rhs.listSize;
  arrayList = new T[listSize]; //allocating with new size
  std::copy(rhs.arrayList,rhs.arrayList+listSize,arrayList); //copying all elements from 0 to listSize from parameter to arrayList
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
  if (position > listSize) { //out of bounds index unable to insert
        return false;
  }
    T* newArray = new T[listSize + 1]; //reallocating with additional size
    std::copy(arrayList, arrayList + position, newArray); //copying elements up to parameter position to new list
    newArray[position] = item; //assigning position item
    std::copy(arrayList + position, arrayList + listSize, newArray + position + 1); //copying elements one index past position to the end to new array
    delete[] arrayList; //deallocating 
    arrayList = newArray; 
    ++listSize; 
    return true;
}

template <typename T>
bool ArrayList<T>::remove(std::size_t position){
  if (position >= listSize) {//out of bounds unable to remove item
        return false;
    }
    for (std::size_t i = position; i < listSize - 1; ++i) {
        arrayList[i] = arrayList[i + 1]; //overwriting position with next index then shifting everything else down one index
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
  if (position >= listSize) {//out of bounds entry return empty object
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

int gcd(int n, int m){
  if(m==0)
      return n;
  if (n<m){
    int temp = n;
    n=m;
    m=temp;
  }
int r = n%m;
return gcd(m,r);    
}
