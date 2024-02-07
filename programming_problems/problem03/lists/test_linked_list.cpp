#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "linked_list.hpp"

template class LinkedList<int>;

TEST_CASE("Test empty List", "[LinkedList]") {
    LinkedList<int> list;

        REQUIRE(list.isEmpty());
        REQUIRE(list.getLength() == 0);
    }
TEST_CASE("Test insert and getting entry", "[LinkedList]") {
    LinkedList<int> list;
        list.insert(0, 10);
        list.insert(1, 20);
        list.insert(2, 30);

        REQUIRE(list.getLength() == 3);
        REQUIRE(list.getEntry(0) == 10);
        REQUIRE(list.getEntry(1) == 20);
        REQUIRE(list.getEntry(2) == 30);
    }
TEST_CASE("Test removing", "[LinkedList]") {
    LinkedList<int> list;
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

      
        REQUIRE(list.remove(0) == false);
    }

    TEST_CASE("Test clearing", "[LinkedList]") {
    LinkedList<int> list;
        list.insert(0, 10);
        list.insert(1, 20);
        list.insert(2, 30);

        list.clear();

        REQUIRE(list.isEmpty());
        REQUIRE(list.getLength() == 0);
    }

    TEST_CASE("Test set entry", "[LinkedList]") {
    LinkedList<int> list;
        list.insert(0, 10);
        list.insert(1, 20);
        list.insert(2, 30);

        list.setEntry(1, 25);
        REQUIRE(list.getEntry(1) == 25);

       
        list.setEntry(5, 50); 
    }

    TEST_CASE("Test invalid bounds", "[LinkedList]") {
    LinkedList<int> list;
        list.insert(0, 10);
        list.insert(1, 20);
        list.insert(2, 30);

        REQUIRE(list.getEntry(5) == 0); 
    }

    TEST_CASE("Test empty ", "[LinkedList]") {
    LinkedList<int> list;
        list.insert(0, 10);
        list.insert(1, 20);
        list.insert(2, 30);

        REQUIRE(list.getLength() == 3);
        REQUIRE_FALSE(list.isEmpty());

        list.clear();

        REQUIRE(list.getLength() == 0);
        REQUIRE(list.isEmpty());
    }
