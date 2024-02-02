#include "limited_size_bag.hpp"

template<typename T>
LimitedSizeBag<T>::LimitedSizeBag() {
  bagSize=0;
  *fixedBag=0;
}
  
template<typename T>
bool LimitedSizeBag<T>::add(const T& item)
{
  if(bagSize<maxsize){
   fixedBag[bagSize]=item;
   bagSize++;
   return true;
  }
  else
  return false;
}

template<typename T>
bool LimitedSizeBag<T>::remove(const T& item)
{
  if(bagSize!=0){
    for(int i=0;i<bagSize;i++){
      if(fixedBag[i]==item){
        for(int j=i;j<bagSize;++j){
          fixedBag[j]=fixedBag[j+1];
        }
        bagSize--;
      }
    }
  return true;
  }
  else
  return false;
}

template<typename T>
bool LimitedSizeBag<T>::isEmpty() const
{
  if(bagSize==0){
    return true;
  }
  else
  return false;
}

template<typename T>
std::size_t LimitedSizeBag<T>::getCurrentSize() const
{
  return bagSize;
}

template<typename T>
bool LimitedSizeBag<T>::contains(const T& item) const
{  
  for(int i =0;i<bagSize;i++){
    if(fixedBag[i]==item){
      return true;
    }
  }
  return false;
}

template<typename T>
void LimitedSizeBag<T>::clear(){
  bagSize=0;
}

template<typename T>
std::size_t LimitedSizeBag<T>::getFrequencyOf(const T & item) const
{
  int frequency=0;
  for(int i=0;i<bagSize;i++){
    if(fixedBag[i]==item){
      frequency++;
    }
  }

  return frequency;
};
