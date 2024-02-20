#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "linked_list.hpp"
#include "sort.hpp"
#include <random>

// write your test cases here
TEST_CASE("Test case", "sorting"){

  LinkedList<int> lst;

  lst.insert(0, 100);
  lst.insert(1, 4);
  lst.insert(2, 10);
  lst.insert(3, 25);
  lst.insert(4, 11);

  LinkedList<int> sorted = sort(lst);

  // check sorted list
  REQUIRE(sorted.getEntry(0) == 4);
  REQUIRE(sorted.getEntry(1) == 10);
  REQUIRE(sorted.getEntry(2) == 11);
  REQUIRE(sorted.getEntry(3) == 25);
  REQUIRE(sorted.getEntry(4) == 100);
  
}

TEST_CASE("Test alphabet","[sorting]") {
    LinkedList<char> alphabet;
    char input[10] = {'a','b','c','d','e','f','g','h','i','j'};
    for(int i = 0; i < 10; ++i) {
        alphabet.insert(i, input[i]);
    }
    LinkedList<char> sorted = sort(alphabet);
    for(int k = 0; k < 10; ++k) {
        REQUIRE(sorted.getEntry(k) == input[k]);
    }
}

TEST_CASE("Sorting negative numbers","[sorting]"){
  LinkedList<int> num;

  num.insert(0,-9);
  num.insert(1,-10);
  num.insert(2,1);
  num.insert(3,-200);
  
  LinkedList<int> sorted = sort(num);

  REQUIRE(sorted.getEntry(0) == -200);
  REQUIRE(sorted.getEntry(1) == -10);
  REQUIRE(sorted.getEntry(2) == -9);
  REQUIRE(sorted.getEntry(3) == 1);

}

TEST_CASE("Sorting double types","[sorting]"){
  LinkedList<double> dub;

  dub.insert(0,9*M_PI);
  dub.insert(1,-2.8372);
  dub.insert(2,0);
  dub.insert(3,M_PI/2);
  dub.insert(4,M_PI);

  LinkedList<double> sorted = sort(dub);

  REQUIRE(sorted.getEntry(0)==-2.8372);
  REQUIRE(sorted.getEntry(1)==0);
  REQUIRE(sorted.getEntry(2)== M_PI/2);
  REQUIRE(sorted.getEntry(3)==M_PI);
  REQUIRE(sorted.getEntry(4)==9*M_PI);

}

TEST_CASE("Sorting strings", "[sorting]") {
    LinkedList<std::string> animals;

    animals.insert(0, "lion");
    animals.insert(1, "tiger");
    animals.insert(2,"bear");
    animals.insert(3, "panther");
    animals.insert(4, "dog");

    LinkedList<std::string> sorted = sort(animals);

    REQUIRE(sorted.getEntry(0) == "bear");
    REQUIRE(sorted.getEntry(1) == "dog");
    REQUIRE(sorted.getEntry(2) == "lion");
    REQUIRE(sorted.getEntry(3) == "panther");
    REQUIRE(sorted.getEntry(4) == "tiger");
}

TEST_CASE("Sorting a really long list of numbers", "[sorting]") {
    int num = 1000; 
    LinkedList<int> longList;

   for (int i = num - 1; i >= 0; --i) {
        longList.insert(0, i);
    }
    LinkedList<int> sorted = sort(longList);
    
    for (int i = 1; i < num; ++i) {
        REQUIRE(sorted.getEntry(i - 1) <= sorted.getEntry(i));
    }
}