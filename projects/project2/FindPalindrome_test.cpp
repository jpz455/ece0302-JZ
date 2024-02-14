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

TEST_CASE (" test adding single letters","[FindPalindrome]"){
	FindPalindrome b;

	REQUIRE(b.add("e"));
	REQUIRE(b.number()==0);
	REQUIRE(b.add("c"));
	REQUIRE(b.number()==0);
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
	FindPalindrome pal;
	REQUIRE(pal.add("TaCoCaT"));
	REQUIRE(pal.number() == 1);
	REQUIRE_FALSE(pal.add("tacocat"));
	REQUIRE(pal.number() == 1);
}

TEST_CASE( "Test an english sentence and add a vector of strings method", "[FindPalindrome]" )
{
	FindPalindrome pal;
	vector<string> sentence;
	sentence.push_back("murder");
	sentence.push_back("for");
	sentence.push_back("a");
	sentence.push_back("jar");
	sentence.push_back("of");
	sentence.push_back("red");
	sentence.push_back("rum");
	REQUIRE(pal.add(sentence));
	REQUIRE(pal.number() == 2);
}


TEST_CASE( "test add vector", "[FindPalindrome]" )
{
	FindPalindrome pal;
	vector<string> test(2);
	vector<string> test2(2);
	
	test.push_back("LEVEL!");
	test.push_back("le0el");

	test2[0] = "leVel";
	test2[1] = "LEVEL";
	
	REQUIRE_FALSE(pal.add(test));
	REQUIRE_FALSE(pal.add(test2));
	
}

TEST_CASE( "test clear method", "[FindPalindrome]" )
{
	FindPalindrome pal;
	REQUIRE(pal.add("noon"));
	REQUIRE(pal.number() == 1);
	pal.clear();
	REQUIRE(pal.number() == 0);
}


