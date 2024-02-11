#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"
#include "FindPalindrome.hpp"
using namespace std;

// There should be at least one test per FindPalindrome method

TEST_CASE( "Test adding a non-allowable word", "[FindPalindrome]" )
{
	FindPalindrome b;
	REQUIRE(!b.add("kayak1"));
}

TEST_CASE("test recursion", "[FindPalindrome]"){
	FindPalindrome b;

	REQUIRE(b.add("a"));
	REQUIRE(b.add("AA"));
	REQUIRE(b.add("AaA"));
	REQUIRE(b.number() == 6);

}

TEST_CASE( "Test duplicate words", "[FindPalindrome]" )
{
	FindPalindrome b;
	REQUIRE(b.add("TaCoCaT"));
	REQUIRE(b.number() == 1);
	REQUIRE(!b.add("tAcOcAt"));
	REQUIRE(b.number() == 1);
}

TEST_CASE( "Test an english sentence", "[FindPalindrome]" )
{
	FindPalindrome b;
	vector<string> v;
	v.push_back("Was");
	v.push_back("IT");
	v.push_back("a");
	v.push_back("cat");
	v.push_back("I");
	v.push_back("SAW");
	REQUIRE(b.add(v));
	REQUIRE(b.number() == 2);
}


TEST_CASE( "test properties", "[FindPalindrome]" )
{
	FindPalindrome b;
	vector<string> v(1);
	vector<string> v1(1);
	v[0] = "kayak";
	v1[0] = "kayaking";
	REQUIRE(b.cutTest1(v));
	REQUIRE(b.cutTest2(v, v1));
	v[0] = "car";
	v1[0] = "pizza";
	REQUIRE(!b.cutTest1(v));
	REQUIRE(!b.cutTest2(v, v1));
}

TEST_CASE( "Clear", "[FindPalindrome]" )
{
	FindPalindrome b;
	REQUIRE(b.add("kayak"));
	REQUIRE(b.number() == 1);
	b.clear();
	REQUIRE(b.number() == 0);
	REQUIRE(b.add("flower"));
	REQUIRE(b.number() == 0);
}

