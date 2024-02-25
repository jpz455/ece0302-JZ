#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "array_list.hpp"

//force class expansion
template class ArrayList<int>;

/*TEST_CASE( "Test", "[ArrayList]" ) {

  ArrayList<int> list;

}

TEST_CASE("Testing invalid bounds and inserts", "[ArrayList]") {
    ArrayList<int> invalidList;
        invalidList.insert(0, M_PI);
        invalidList.insert(1, 2*M_PI);
        invalidList.insert(2, 3*M_PI);

        REQUIRE(invalidList.getEntry(5) == 0); 

      
        REQUIRE(invalidList.insert(5, 5*M_PI) == false);
}

TEST_CASE("Test empty List", "[ArrayList]") {
    ArrayList<int> emptyList;
      
      REQUIRE(emptyList.getLength() == 0);
      REQUIRE(emptyList.isEmpty());
      

}

TEST_CASE("Test setting entry", "[ArrayList]") {
    ArrayList<double> setList;
        setList.insert(0, 37);
        setList.insert(1, 88);
        setList.insert(2, 1223);

        setList.setEntry(1, 12);
        REQUIRE(setList.getEntry(1) == 12);
      
        setList.setEntry(2, 5*M_PI);
        REQUIRE(setList.getEntry(2) == 5*M_PI);

}
    
TEST_CASE("Test insert and getting entry", "[ArrayList]") {
        ArrayList<int> insertList;
        insertList.insert(0, 345);
        insertList.insert(1, 123.32);
        insertList.insert(2, 759);

        REQUIRE_FALSE(insertList.getLength() == 9);
        REQUIRE_FALSE(insertList.getEntry(0) == 10);
        REQUIRE_FALSE(insertList.getEntry(1) == 20);
        REQUIRE_FALSE(insertList.getEntry(2) == 30);
        
        REQUIRE(insertList.getEntry(2)==759);
        REQUIRE(insertList.getEntry(1)==123);
}

TEST_CASE("Test remove", "[ArrayList]") {
   ArrayList<double> removeList;
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
}

TEST_CASE("Test clear", "[ArrayList]") {
    ArrayList<int> clearedList;
        clearedList.insert(0, pow(2,6));
        clearedList.insert(1, pow(2,5));
        clearedList.insert(2, pow(2,4));

        clearedList.clear();

        REQUIRE(clearedList.isEmpty());
        REQUIRE(clearedList.getLength() == 0);
}*/

TEST_CASE("",""){

    int n = 126;
    int m = 35;

    REQUIRE(gcd(n,m)==7);
}

