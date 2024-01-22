#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include <iostream>
#include "bitset.hpp"

TEST_CASE( "Test bitset default construction", "[bitset]" ) {

    Bitset b;  
    REQUIRE(b.size() == 8);
    REQUIRE(b.good());
}

TEST_CASE("Test bitset construction given invalid parameter size", "[bitset]"){
    Bitset b(-1);
    REQUIRE_FALSE(b.good());
}

TEST_CASE("Test bitset size construction","[bitset]"){
    Bitset b(890);
    REQUIRE(b.size()==890);
    REQUIRE(b.good());
}

TEST_CASE( "Test bitset construction with asString", "[bitset]" ) {
    Bitset b;
    REQUIRE(b.asString().compare("00000000") == 0);
}

TEST_CASE("Test bitset asString with variable 0 and 1","[bitset]"){
    Bitset b("0101001101011100");
    REQUIRE(b.test(1));
    REQUIRE(b.test(3));
    REQUIRE(b.test(6));
    REQUIRE(b.test(7));
    REQUIRE(b.test(9));
    REQUIRE_FALSE(b.test(0));
    REQUIRE_FALSE(b.test(2));
    REQUIRE_FALSE(b.test(4));
    REQUIRE_FALSE(b.test(5));
    REQUIRE(b.good());
    REQUIRE(b.size()==16);
}

TEST_CASE( "Test bitset construction size", "[bitset]" ) {
    Bitset b(64);
    std::string s(64, '0');
    REQUIRE(b.size() == 64);
    REQUIRE(b.good());
}

TEST_CASE("Test bitset string construction, set, toggle, and test","[bitset]"){
    Bitset b("001100110101");
    REQUIRE(b.size()==12);
    b.set(0);
    b.toggle(2);
    REQUIRE(b.test(0));
    REQUIRE_FALSE(b.test(2));

}

TEST_CASE( "Test bitset construction string", "[bitset]" ) {
    std::string s("00101110000011000001101000001");
    Bitset b(s);
    REQUIRE(b.size() == s.size());
    REQUIRE(b.good());
    REQUIRE(b.asString().compare(s) == 0);
}

TEST_CASE( "Test bitset construction invalid string", "[bitset]" ) {
    std::string s("00101110000011002001101000001");
    Bitset b(s);
    REQUIRE_FALSE(b.good());
}

TEST_CASE( "Test set", "[bitset]" ) {
    std::string s("00010001");
    Bitset b;
    b.set(3);
    b.set(7);
    REQUIRE(b.size() == 8);
    REQUIRE(b.good());
    REQUIRE(b.asString().compare(s) == 0);
}

TEST_CASE( "Test set with size init", "[bitset]" ) {
    std::string s("00010");
    Bitset b(5);
    b.set(3);
    REQUIRE(b.size() == 5);
    REQUIRE(b.good());
    REQUIRE(b.asString().compare(s) == 0);
}

TEST_CASE( "Test combined", "[bitset]" ) {
    std::string s((1<<15) + 3, '0');
    Bitset b(s);
    REQUIRE(b.size() == s.size());
    REQUIRE(b.good());
    REQUIRE(b.asString().compare(s) == 0);

    for (int i = 1; i < (1<<10); i++) {
        b.set(i);
        b.reset(i + (1<<10));
        b.toggle(i + (1<<11));
        REQUIRE(b.good());
        REQUIRE(b.test(i));
        REQUIRE_FALSE(b.test(i + (1<<10)));
        REQUIRE(((b.test(i + (1<<11)) == true && s.at(i + (1<<11)) == '0') || (b.test(i + (1<<11)) == false && s.at(i + (1<<11)) == '1')));
    }
}

