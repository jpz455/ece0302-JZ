#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "linked_list.hpp"

template class LinkedList<int>;

TEST_CASE("Test empty List", "[LinkedList]") {
    LinkedList<int> emptyList;

        REQUIRE(emptyList.getLength() == 0);
        REQUIRE(emptyList.isEmpty());
}

TEST_CASE("Test insert and getting entry", "[LinkedList]") {
    LinkedList<int> insertEntryList;
        insertEntryList.insert(0, 999);
        insertEntryList.insert(1, 998);
        insertEntryList.insert(2, 997);

        REQUIRE(insertEntryList.getLength() == 3);
        REQUIRE(insertEntryList.getEntry(0) == 999);
        REQUIRE(insertEntryList.getEntry(1) == 998);
        REQUIRE(insertEntryList.getEntry(2) == 997);
}

TEST_CASE("Test removing", "[LinkedList]") {
    LinkedList<double> removeList;
        removeList.insert(0, 1*M_PI);
        removeList.insert(1, 2*M_PI);
        removeList.insert(2, 3*M_PI);

        REQUIRE(removeList.remove(1) == true);
        REQUIRE(removeList.getLength() == 2);
        REQUIRE(removeList.getEntry(0) == 1*M_PI);
        REQUIRE(removeList.getEntry(1) == 3*M_PI);

        REQUIRE(removeList.remove(0) == true);
        REQUIRE(removeList.remove(0) == true);
        REQUIRE(removeList.isEmpty());

        REQUIRE_FALSE(removeList.remove(0) == true);
}

    TEST_CASE("Test clearing", "[LinkedList]") {
    LinkedList<double> clearedList;
        clearedList.insert(0, pow(2,.5));
        clearedList.insert(1, pow(3,.5));
        clearedList.insert(2, pow(4,.5));

        clearedList.clear();

        REQUIRE(clearedList.getLength() == 0);
        REQUIRE(clearedList.isEmpty());
        
    }

    TEST_CASE("Test set entry", "[LinkedList]") {
    LinkedList<int> setList;
        setList.insert(0, 43);
        setList.insert(1, 98);
        setList.insert(2, 37);

        setList.setEntry(1, 999);
        REQUIRE(setList.getEntry(1) == 999);

    }

    TEST_CASE("Test invalid bounds", "[LinkedList]") {
    LinkedList<int> invalidList;
        invalidList.insert(0, .1);
        invalidList.insert(1, .2);
        invalidList.insert(2, .3);

        REQUIRE(invalidList.getEntry(5) == 0); 
    }

    TEST_CASE("Test empty ", "[LinkedList]") {
    LinkedList<int> emptyList;
        emptyList.insert(0, 100);
        emptyList.insert(1, 200);
        emptyList.insert(2, 300);

        REQUIRE(emptyList.getLength() == 3);
        REQUIRE_FALSE(emptyList.isEmpty());

        emptyList.clear();

        REQUIRE(emptyList.getLength() == 0);
        REQUIRE(emptyList.isEmpty());
    }
TEST_CASE("",""){
    LinkedList<int> examList;
    examList.insert(0,20);
    examList.insert(1,45);
    examList.insert(2,500);
    examList.insert(1,60);
    examList.insert(2,30);
    examList.insert(3,100);
    examList.remove(2);

    int answer[5]={20,60,100,45,500};
    for(int i=0;i<5;i++)
    REQUIRE(examList.getEntry(i)==answer[i]);
}