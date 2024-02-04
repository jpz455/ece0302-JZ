#include "dynamic_bag.hpp"

//default constructor
template<typename T>
DynamicBag<T>::DynamicBag() {
  size=0;
  ptr=nullptr;
}

template<typename T>
DynamicBag<T>::DynamicBag(const DynamicBag<T>& x){
  size=x.size;
  ptr= new T[x.size];
  std::copy(x.ptr,x.ptr+size,ptr);//copies elements from refernce x to new pointer ptr
}
    
template<typename T>
DynamicBag<T>::~DynamicBag(){
  delete [] ptr;//deallocating
}
  
template<typename T>
DynamicBag<T>& DynamicBag<T>::operator=(DynamicBag<T> x)
{  
  swap(x); //swaps x and "this"
  return *this; //returns new "this"
}

template<typename T>
void DynamicBag<T>::swap(DynamicBag<T>& x){
  
  std::swap(ptr,x.ptr);//swaps from pointer to reference x
  std::swap(size,x.size);//swaps size of ptr and reference x

}

template<typename T>
bool DynamicBag<T>::add(const T& item)
{
 T* newPtr = new T[size + 1];
 if(ptr){//if ptr isnt null
    std::copy(ptr, ptr + size, newPtr);//copies elements from ptr to new ptr
    delete[] ptr;//deallocating old ptr
 }
    ptr = newPtr;//assigning old ptr to the copied version
    ptr[size++]=item;//appending item refernce to bag ptr
    return true;
}




template<typename T>
bool DynamicBag<T>::remove(const T& item)
{
  for(size_t i=size-1;i>=0;i--){
    if(ptr[i]==item){
      T* tempBag= new T[size-1];//new pointer of smaller size
      std::copy(ptr,ptr+i,tempBag);//copies elements from ptr (to index i) to temp bag
      std::copy(ptr+i+1,ptr+size--,tempBag+i);//copies elements from index i+1 to end of ptr to temp bag
      delete [] ptr;//deallocating
      ptr=tempBag;
      return true;
    }
  }
  return false;
}


template<typename T>
bool DynamicBag<T>::isEmpty() const
{
  if(size==0){
    return true;
  }
  else
  return false;
}

template<typename T>
std::size_t DynamicBag<T>::getCurrentSize() const{
  return size;
}

template<typename T>
bool DynamicBag<T>::contains(const T& item) const
{  
  for(size_t i=0;i<size;i++){
    if(ptr[i]==item){
      return true;
    }
  }
  return false;
}

template<typename T>
void DynamicBag<T>::clear(){
  size=0;
}

template<typename T>
std::size_t DynamicBag<T>::getFrequencyOf(const T & item) const
{
  size_t count=0;
  for(size_t i=0;i<size;i++){
    if(ptr[i]==item){
      count++;
    }
  }
  return count;
};