/** @file abstract_bag.hpp
 * Creating the user interface within abstract bag class
 * @author Jillian Zitcovich
 * @date 1/18/24
 */
#ifndef _ABSTRACT_BAG_HPP_
#define _ABSTRACT_BAG_HPP_
/** @class AbstractBag
 * Abstract bag class is the abstract class that other bags can be built from. This is the interface that other bag classes can
 * use as a base to add on more specificity
*/
#include <cstdlib>

template<typename T>class AbstractBag{
    public:
/**
 * getCurrentSize method returns the value of the size of the bag 
 * @post this method should return the size of the bag after running
 * @return size of the current object
*/
  virtual std::size_t getCurrentSize() const=0;
/**
 * Checks to see if the bag is empty and returns a boolean value that reflects its contents
 * @pre the bag is empty or it is occupied with something
 * @post a boolean value will be returned
 * @return true if the bag is empty, false if the bag is occupied
*/
  virtual bool isEmpty() const=0;
/**
 * Adds something to the current bag if there is enough room within the max size of the bag
 * @param entry is what is going to attempt to be added to the bag
 * @pre bag exists and the method is given a parameter for entry
 * @post the parameter will be added to the bag if there is enough room and increment the size, but return false if the bag is full
 * @throws if entry is attempting to be placed outside of the range, or size, of the bag
 * @return true is the entry was successfully placed in the bag and false if there was not enough room in the bag
*/
  virtual bool add(const T& entry)=0;
/**
 * Remove something from the bag if the bag has something in it
 * @param entry is what is wanted to be removed from the bag
 * @pre the bag exists and the method is given a parameter value for entry to be removed
 * @post if the bag was big enough and the index was found, the parameter was removed from the bag and the size of the bag was
 * decremented and all items were shifted accordingly
 * @throws if the entry wanting to be removed is outside the range of the bag
 * @return true is the entry was successfully removed from the bag and false if the bag was not big enough or if the index was unfound
*/
  virtual bool remove(const T& entry)=0;
/**
 * Resets the size of the bag to 0 which is like emptying the bag out from what it was previously holding
 * @post the bag size is =0 and the contents of what it was holding is cleared
*/
  virtual void clear()=0;

/**
 * Returns the number of times the given parameter appears within the bags contents
 * @param is what the method is finding the frequency of
 * @pre the bag exists and the method is given a parameter to find the frequency of
 * @post the number of times the parameter shows up in the bag is returned
 * @return the frequency of the parameter within the bag
*/
  virtual std::size_t getFrequencyOf(const T& entry) const=0;
/**
 * Returns a bool value to indicate whether or not the bag is containing the given parameter
 * @param entry is being tested to see if the bag contains it
 * @pre the bag exists and is given a value parameter for entry
 * @return true or false based on the bags contents and what the value of the parameter is
*/
  virtual bool contains(const T& entry) const=0;

};


#endif