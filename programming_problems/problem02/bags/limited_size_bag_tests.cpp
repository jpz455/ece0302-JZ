#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "limited_size_bag.hpp"

// force template expansion for ints
template class LimitedSizeBag<int>;

TEST_CASE("Calling all public members", "[LimitedSizeBag]"){
  LimitedSizeBag<int> b;

  b.add(0);
  b.remove(0);
  b.isEmpty();
  b.getCurrentSize();
  b.clear();
  b.getFrequencyOf(0);
  b.contains(0);

}

TEST_CASE("Default Construction","[LimitedSizeBag]"){
  LimitedSizeBag<int> b;
  REQUIRE(b.getCurrentSize()==0);
  REQUIRE(b.isEmpty()==1);
}

TEST_CASE("Testing add method","[LimitedSizeBag]"){
  LimitedSizeBag<double> bag;

  for(int i=0;i<80;i++){
    bag.add(i);
  }
  for(int i=0;i<bag.getCurrentSize();i++){
    REQUIRE(bag.contains(i)==1);
  }
}

TEST_CASE("Testing remove and clear method method","[LimitedSizeBag]"){
  LimitedSizeBag<int> b;

  for(int i=0;i<LimitedSizeBag<int>::maxsize;i++){
    b.add(i);
  }
  REQUIRE(b.getCurrentSize()==100);
  for(int i=0;i<LimitedSizeBag<int>::maxsize;i+=2){
    REQUIRE(b.remove(i));
  }
  REQUIRE(b.getCurrentSize()==LimitedSizeBag<int>::maxsize/2);

  b.clear();
  REQUIRE(b.isEmpty()==1);
  REQUIRE(b.getCurrentSize()==0);
  
}
TEST_CASE("Testing Frequency method","[LimitedSizeBag]"){
  LimitedSizeBag<int> bag;

  for(int i=0;i<LimitedSizeBag<int>::maxsize;i+=10){
    bag.add(10);
  }
  REQUIRE(bag.getFrequencyOf(10)==10);
}