#include "dynamic_bag.hpp"

template<typename T>
DynamicBag<T>::DynamicBag() {
  size=0;
  ptr=nullptr;
}

template<typename T>
DynamicBag<T>::DynamicBag(const DynamicBag<T>& x){
  size=x.size;
  ptr= new T[x.size];
  for(size_t i=0;i<size;i++){
    *(ptr+i)=*(x.ptr+i);
  }
}
    
template<typename T>
DynamicBag<T>::~DynamicBag(){
  delete [] ptr;
}
  
template<typename T>
DynamicBag<T>& DynamicBag<T>::operator=(DynamicBag<T> x)
{  
  size=x.size;
  ptr=new T[x.size];
  for(size_t i=0;i<x.size;i++){
    *(ptr+i)=*(x.ptr+i);
  }
  return *this;
}

template<typename T>
void DynamicBag<T>::swap(DynamicBag<T>& x){
  
  std::swap(ptr,x.ptr);
  std::swap(size,x.size);

}

template<typename T>
bool DynamicBag<T>::add(const T& item)
{
    T *temp = ptr; 
    ptr = new T[size + 1]; 

    for (size_t i = 0; i < size; ++i) { 
        ptr[i] = temp[i];
    }
    ptr[size] = item; 
    size++; 

    delete[] temp; 

    return true; 
}




template<typename T>
bool DynamicBag<T>::remove(const T& item)
{
  for(size_t i=size-1;i>=0;i--){
    if(ptr[i]==item){
      T* tempBag= new T[size-1];
      std::copy(ptr,ptr+i,tempBag);
      std::copy(ptr+i+1,ptr+size--,tempBag+i);
      delete [] ptr;
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