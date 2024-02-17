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

TEST_CASE("Test default constructor","[FindPalindrome]"){
	FindPalindrome pal;

	REQUIRE(pal.number()==0);
	REQUIRE(pal.toVector() == vector<vector<string>>());
}

TEST_CASE (" test adding single letters","[FindPalindrome]"){
	FindPalindrome b;

	REQUIRE(b.add("e"));
	REQUIRE(b.number()==0);
	REQUIRE(b.add("c"));
	REQUIRE(b.number()==0);
}

TEST_CASE("Test add vector of strings method", "[FindPalindrome]"){
	FindPalindrome b;
	vector<string> test(3);
	
	test[0]="aman"/**/"aplan"/**/"acanal"/**/"panama";
	test[1] = "able"/**/"was"/**/"i"/**/"ere"/**/"i"/**/"saw"/**/"elba";
	test[2] = "madam"/**/"in"/**/"eden"/**/"im"/**/"adam";
	
	REQUIRE(b.add(test[0]));
	REQUIRE(b.add(test[1]));
	REQUIRE(b.add(test[2]));
	REQUIRE(b.number()==1);
}

TEST_CASE("test recursion", "[FindPalindrome]"){
	FindPalindrome b;

	REQUIRE(b.add("a"));
	REQUIRE(b.add("AA"));
	REQUIRE(b.add("AaA"));
	REQUIRE(b.number() == 6);

   	b.clear();
	
	REQUIRE(b.number()==0);
 	REQUIRE(b.add("a"));
    REQUIRE(b.add("aa"));
    REQUIRE(b.add("aaa"));
    REQUIRE(b.add("aaaa"));

    REQUIRE(b.number() == 24); //= to 4!
}

TEST_CASE( "Test duplicate words", "[FindPalindrome]" )
{
	FindPalindrome pal;
	
	REQUIRE(pal.add("TaCoCaT"));
	REQUIRE(pal.number() == 1);
	
	REQUIRE_FALSE(pal.add("tacocat"));
	REQUIRE(pal.number() == 1);
}

TEST_CASE( "Test an english sentence with add string method", "[FindPalindrome]" )
{
	FindPalindrome b;
	vector<string> sentence;
	
	sentence.push_back("never");
	sentence.push_back("even");
	sentence.push_back("or");
	sentence.push_back("odd");
	
	REQUIRE(b.add(sentence));
	REQUIRE(b.number() == 1);
	
}


TEST_CASE( "test add vector with duplicate words and invalid characters", "[FindPalindrome]" )
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

	REQUIRE(pal.add("noon"));
	REQUIRE(pal.number() == 1);
}


TEST_CASE("cutTest2 method test", "[FindPalindrome]") {
    FindPalindrome b;

    vector<string> longpets = {"raining", "cats", "and", "dogs"};
    vector<string> shortpets = {"cat", "dog"};

    REQUIRE(b.cutTest2(longpets, shortpets) == true);

    vector<string> abrevmonth = {"jan", "feb","mar","apr"};
    vector<string> month = {"january", "february", "march", "april"};

    REQUIRE(b.cutTest2(abrevmonth, month) == true);

    vector<string> colors = {"red", "blue"};
    vector<string> colorsRepeat = {"red", "blue"};

    REQUIRE(b.cutTest2(colors, colorsRepeat) == true);
	REQUIRE(b.add(colors));
	REQUIRE_FALSE(b.add(colorsRepeat));

    vector<string> spring = {"flower", "petal"};
    vector<string> summer = {"tree", "park"};

    REQUIRE(b.cutTest2(spring, summer) == false);
}

TEST_CASE( "cutTest 1 method test", "[FindPalindrome]" )
{
	FindPalindrome pal;
	std::vector <std::string> testCutOne;
	
	testCutOne.push_back("AAAA");
	testCutOne.push_back("bbbb");

	REQUIRE(pal.cutTest1(testCutOne));

	testCutOne.push_back("kkk");
	testCutOne.push_back("p");
	REQUIRE_FALSE(pal.cutTest1(testCutOne));

	testCutOne.clear();

	testCutOne.push_back("aa");
	testCutOne.push_back("bb");
	testCutOne.push_back("c");
	testCutOne.push_back("d");

	REQUIRE_FALSE(pal.cutTest1(testCutOne));
	
}

TEST_CASE("Test to vector method","[FindPalindrome]"){
		
		vector<vector<string>> temp = 
		{{"mr","owl","ate","my","metal","worm"}};

		FindPalindrome pal; 
		
		REQUIRE(pal.add("mr"));
		REQUIRE(pal.add("owl"));
		REQUIRE(pal.add("ate"));
		REQUIRE(pal.add("my"));
		REQUIRE(pal.add("metal"));
		REQUIRE(pal.add("worm"));

		REQUIRE(pal.toVector() == temp);
}