#ifndef BITSET_HPP
#define BITSET_HPP
#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <bitset>
#include <cmath>


class Bitset{
public:

  //Default Constructor that creates a bitset of 8 all being set to zero
  Bitset();

  //Constructor that creates a bitset of size parameter "size". returns invalid if parameter is less than or equal to 0
  Bitset(intmax_t size);

  // TODO COMMENT
  Bitset(const std::string & value);

  // TODO COMMENT
  ~Bitset();

  Bitset(const Bitset & ) = delete;
  Bitset & operator=(const Bitset &) = delete;

  // TODO COMMENT
  intmax_t size() const;

  // TODO COMMENT
  bool good() const;

  // TODO COMMENT
  void set(intmax_t index);

  // TODO COMMENT
  void reset(intmax_t index);

  // TODO COMMENT
  void toggle(intmax_t index);

  // TODO COMMENT
  bool test(intmax_t index);

  // TODO COMMENT
  std::string asString() const;

private:

  bool valid=true;
  uint8_t* valid_bit_set;
};

#endif
