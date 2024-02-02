#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "dynamic_bag.hpp"

// force template expansion for ints
template class DynamicBag<int>;

TEST_CASE("Calling all public members", "[DynamicBag]"){
  DynamicBag<int> b;

  b.add(0);
  b.remove(0);
  b.isEmpty();
  b.getCurrentSize();
  b.clear();
  b.getFrequencyOf(0);
  b.contains(0);
}

TEST_CASE("Default Construction with empty verification","[DynamicBag]"){
  DynamicBag<int> b;
  REQUIRE(b.getCurrentSize()==0);
  REQUIRE(b.isEmpty()==true);
}

TEST_CASE("Swap test", "[DynamicBag]") {
    DynamicBag<int> bag1;
    bag1.add(1);
    bag1.add(2);

    DynamicBag<int> bag2;
    bag2.add(3);
    bag2.add(4);

    bag1.swap(bag2);

    REQUIRE(bag1.contains(3) == 1);
    REQUIRE(bag1.contains(4)== 1);

    REQUIRE(bag2.contains(1) == 1);
    REQUIRE(bag2.contains(2) == 1);
}

TEST_CASE("Add method","[DynamicBag]"){
  DynamicBag<int> b;
  REQUIRE(b.getCurrentSize()==0);
  for(int i=0;i<10;i++){
    b.add(i);
  }
  for(int i=0;i<10;i++){
    REQUIRE(b.contains(i)==1);
  }
  REQUIRE(b.getCurrentSize()==10);
}

TEST_CASE("Remove method","DynamicBag"){
  DynamicBag<int> b;
  for(int i=0;i<11;i++){
    b.add(i);
  }
  REQUIRE(b.getCurrentSize()==11);
  b.remove(0);
  REQUIRE(b.getCurrentSize()==10);
  REQUIRE(b.contains(0)==0);
}

TEST_CASE("Copy constructor testing with clear method","[DynamicBag]"){
  int test[]={0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30};
  
  DynamicBag<int> bag1;
  for(int i=0;i<sizeof(test);i++){
    bag1.add(test[i]);
  }

  DynamicBag<int> bag2 = bag1;
  REQUIRE(bag2.getCurrentSize()==bag1.getCurrentSize());
  for(int i=0;i<sizeof(test);i++){
    REQUIRE(bag2.contains(test[i])==bag1.contains(test[i]));
  }

  bag1.clear();
  bag2=bag1;
  REQUIRE(bag2.getCurrentSize()==0);
}

TEST_CASE("Copy Assignment testing","[DynamicBag]"){
  DynamicBag<double> bag1;
  for(int i=0;i<100;i++){
    bag1.add(8.4*1);
  }
  DynamicBag<double>bag2;
  bag2=bag1;
  REQUIRE(bag2.getCurrentSize()==bag1.getCurrentSize());
  for(int i=0;i<100;i++){
    REQUIRE(bag2.contains(i)==bag1.contains(i));
    REQUIRE(bag2.getFrequencyOf(i)==bag1.getFrequencyOf(i));
  }

}
