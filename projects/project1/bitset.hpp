#ifndef BITSET_HPP
#define BITSET_HPP
#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <cmath>



class Bitset{
public:

  //Default Constructor that creates a bitset of length 8, all bits being set to zero
  Bitset();

  //Constructor that creates a bitset of length parameter "size". returns invalid if parameter is less than or equal to 0
  Bitset(intmax_t size);

  //String Constructor that creates a bitset off of string parameter. tests each character of the string for invalidity if != 1 or 0
  Bitset(const std::string & value);

  //delete memory allocated for pointer
  ~Bitset();

  Bitset(const Bitset & ) = delete;
  Bitset & operator=(const Bitset &) = delete;

  //Returns the size of the bitset. ex. would return 8 for default constructor bitset
  intmax_t size() const;

  //returns the value of the private member variable that holds the validity of the bitset which updates throughout the methods
  bool good() const;

  //Using the index parameter, the bit in that place is "set" to 1. if the index is not within range of the bitset then bitset becomes invalid
  void set(intmax_t index);

  //Using the parameter index value to "reset" the bit at that index to 0. bitset marked invalid if index is not within bitset range
  void reset(intmax_t index);

  //Parameter index switches the bitset at that index from the current value i.e. 0 to 1 or 1 to 0
  void toggle(intmax_t index);

  //Returns true if the given bit at the index parameter is =1. returns false if =0 or if the index is not within range of the bitset
  bool test(intmax_t index);

  //Returns the bitset as its string equivalent starting with MSB
  std::string asString() const;

private:

  uint8_t *ADTPtr;                                // pointer to first uint8_t element of array
    intmax_t BSsize;                                // num of bits
    bool isValid;
 
};

#endif
