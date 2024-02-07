#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "array_list.hpp"

//force class expansion
template class ArrayList<int>;

TEST_CASE( "Test", "[ArrayList]" ) {

  ArrayList<int> list;
}

TEST_CASE("Test empty List", "[ArrayList]") {
    ArrayList<int> list;
      
      REQUIRE(list.isEmpty());
      REQUIRE(list.getLength() == 0);

}
    
TEST_CASE("Test insert and getting entry", "[ArrayList]") {
        ArrayList<int> list;
        list.insert(0, 10);
        list.insert(1, 20);
        list.insert(2, 30);

        REQUIRE(list.getLength() == 3);
        REQUIRE(list.getEntry(0) == 10);
        REQUIRE(list.getEntry(1) == 20);
        REQUIRE(list.getEntry(2) == 30);
}

TEST_CASE("Test remove", "[ArrayList]") {
   ArrayList<int> list;
        list.insert(0, 10);
        list.insert(1, 20);
        list.insert(2, 30);

        REQUIRE(list.remove(1) == true);
        REQUIRE(list.getLength() == 2);
        REQUIRE(list.getEntry(0) == 10);
        REQUIRE(list.getEntry(1) == 30);

        REQUIRE(list.remove(0) == true);
        REQUIRE(list.remove(0) == true);
        REQUIRE(list.isEmpty());
}

TEST_CASE("Test clear", "[ArrayList]") {
    ArrayList<int> list;
        list.insert(0, 10);
        list.insert(1, 20);
        list.insert(2, 30);

        list.clear();

        REQUIRE(list.isEmpty());
        REQUIRE(list.getLength() == 0);
}

TEST_CASE("Test setting entry", "[ArrayList]") {
    ArrayList<int> list;
        list.insert(0, 10);
        list.insert(1, 20);
        list.insert(2, 30);

        list.setEntry(1, 25);
        REQUIRE(list.getEntry(1) == 25);

      
        list.setEntry(5, 50);
}
TEST_CASE("Testing invalid bounds and inserts", "[ArrayList]") {
    ArrayList<int> list;
        list.insert(0, 10);
        list.insert(1, 20);
        list.insert(2, 30);

        REQUIRE(list.getEntry(5) == 0); 

      
        REQUIRE(list.insert(5, 50) == false);
    }
