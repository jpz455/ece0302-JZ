#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include <iostream>
#include "catch.hpp"
#include "XMLParser.hpp"

using namespace std;

// TODO Implement tests of your Stack class and XMLParser class here

TEST_CASE( "Test Bag add", "[ADT Bag]" )
{
	   INFO("Hint: testing Bag add()");
		// Create a Bag to hold ints
		Bag<int> intBag;
		int testSize = 2;
		int bagSize;
		bool success;
		for (int i=0; i<testSize; i++) {
			success = intBag.add(i);
			REQUIRE(success);
			bagSize = intBag.size();
			success = (bagSize == (i+1));
			REQUIRE(success);
		}
}

TEST_CASE( "Test Stack push and size", "[ADT Stack]" )
{
	   INFO("Hint: testing Stack push()");
		// Create a Stack to hold ints
		Stack<int> intStack;
		int testSize = 3;
		int stackSize;
		bool success;
		for (int i=0; i<testSize; i++) {
			success = intStack.push(i);
			REQUIRE(success);
			stackSize = intStack.size();
			success = (stackSize == (i+1));
			REQUIRE(success);
		}
}

TEST_CASE( "Test XMLParser tokenizeInputString", "[XMLParser]" )
{
	   INFO("Hint: tokenize single element test of XMLParse");
		// Create an instance of XMLParse
		XMLParser myXMLParser;
		string testString = "<test>stuff</test>";
		bool success;
		success = myXMLParser.tokenizeInputString(testString);
		REQUIRE(success);
}


TEST_CASE( "Test Stack handout-0", "[XMLParser]" )
{
		// Create a Stack to hold ints
		Stack<int> intStack;
		int testSize = 10;
		int stackSize;
		bool success = false;
		for (int i=0; i<testSize; i++) {
			intStack.push(i);
			stackSize = intStack.size();
			success = (stackSize == (i+1));
			REQUIRE(success);
		}
		for (int i = testSize-1; i>=0; i--) {
			REQUIRE(intStack.isEmpty() == false);
            int elem = intStack.peek();
			REQUIRE(elem == i);
            REQUIRE(intStack.isEmpty() == false);
			intStack.pop();
		}
        REQUIRE(intStack.isEmpty() == true);
}

TEST_CASE( "Test Stack handout-1", "[XMLParser]" )
{
	   Stack<char> charStack;
       std::string s("Hello world");
       int i = 1;
       for (auto c:s) {
           charStack.push(c);
           REQUIRE(charStack.size() == i);
           i++;
       }
       for (i = 0; i < 5; i++) {
           REQUIRE(charStack.isEmpty() == false);
           char c = charStack.peek();
           REQUIRE(c == s[s.length()-1-i]);
           REQUIRE(charStack.isEmpty() == false);
           charStack.pop();
       }
       REQUIRE(charStack.size() == 6);
       charStack.clear();
       REQUIRE(charStack.isEmpty() == true);      
}

// You can assume that the beginning and the end of CONTENT will not be filled with whitespace
TEST_CASE( "Test XMLParser tokenizeInputString Handout-0", "[XMLParser]" )
{
	   INFO("Hint: tokenize single element test of XMLParse");
		// Create an instance of XMLParse
		XMLParser myXMLParser;
		string testString = "<test>stuff</test>";
		bool success;
		success = myXMLParser.tokenizeInputString(testString);
		REQUIRE(success);
		std::vector<TokenStruct> result = {TokenStruct{StringTokenType::START_TAG, std::string("test")},
											TokenStruct{StringTokenType::CONTENT, std::string("stuff")},
											TokenStruct{StringTokenType::END_TAG, std::string("test")}};
		std::vector<TokenStruct> output = myXMLParser.returnTokenizedInput();
		REQUIRE(result.size() == output.size());
		for (int i = 0; i < result.size(); i++) {
			REQUIRE(result[i].tokenType == output[i].tokenType);
			REQUIRE(result[i].tokenString.compare(output[i].tokenString) == 0);
		}
}


// You can assume that the beginning and the end of CONTENT will not be filled with whitespace
TEST_CASE( "Test XMLParser tokenizeInputString Handout-1", "[XMLParser]" )
{
	   INFO("Hint: tokenize multiple elements test of XMLParse");
		// Create an instance of XMLParse
		XMLParser myXMLParser;
		string testString = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><Note src='gmail'>  <From>Tom</From> <To>Alice</To> </Note>";
		bool success;
		success = myXMLParser.tokenizeInputString(testString);
		REQUIRE(success);
		std::vector<TokenStruct> result = { TokenStruct{StringTokenType::DECLARATION, std::string("xml version=\"1.0\" encoding=\"UTF-8\"")},
									TokenStruct{StringTokenType::START_TAG, std::string("Note")},
									TokenStruct{StringTokenType::START_TAG, std::string("From")},
									TokenStruct{StringTokenType::CONTENT, std::string("Tom")},
									TokenStruct{StringTokenType::END_TAG, std::string("From")},
									TokenStruct{StringTokenType::START_TAG, std::string("To")},
									TokenStruct{StringTokenType::CONTENT, std::string("Alice")},
									TokenStruct{StringTokenType::END_TAG, std::string("To")},
									TokenStruct{StringTokenType::END_TAG, std::string("Note")}};
		std::vector<TokenStruct> output = myXMLParser.returnTokenizedInput();
		REQUIRE(result.size() == output.size());
		for (int i = 0; i < result.size(); i++) {
			REQUIRE(result[i].tokenType == output[i].tokenType);
			REQUIRE(result[i].tokenString.compare(output[i].tokenString) == 0);
		}
}

TEST_CASE( "Test XMLParser parseTokenizedInput Handout-0", "[XMLParser]" )
{
	   INFO("Hint: tokenize single element test of XMLParse");
		// Create an instance of XMLParse
		XMLParser myXMLParser;
		string testString = "<test myattr='abcdef'>stuff<this_is_empty_tag/></test>";
		bool success;
		success = myXMLParser.tokenizeInputString(testString);
		REQUIRE(success);
		std::vector<TokenStruct> result = {TokenStruct{StringTokenType::START_TAG, std::string("test")},
											TokenStruct{StringTokenType::CONTENT, std::string("stuff")},
											TokenStruct{StringTokenType::EMPTY_TAG, std::string("this_is_empty_tag")},
											TokenStruct{StringTokenType::END_TAG, std::string("test")}};
		std::vector<TokenStruct> output = myXMLParser.returnTokenizedInput();
		REQUIRE(result.size() == output.size());
		success = myXMLParser.parseTokenizedInput();
		REQUIRE(success);
		output = myXMLParser.returnTokenizedInput();
		REQUIRE(result.size() == output.size());
		for (int i = 0; i < result.size(); i++) {
			REQUIRE(result[i].tokenType == output[i].tokenType);
			REQUIRE(result[i].tokenString.compare(output[i].tokenString) == 0);
		}
}

TEST_CASE( "Test XMLParser Final Handout-0", "[XMLParser]" )
{
	   INFO("Hint: TestFile");
		// Create an instance of XMLParse
		XMLParser myXMLParser;
		ifstream myfile ("./TestFile.txt");
		std::string inputString((std::istreambuf_iterator<char>(myfile) ), (std::istreambuf_iterator<char>()) );

		bool success;
		success = myXMLParser.tokenizeInputString(inputString);
		REQUIRE(success);
		success = myXMLParser.parseTokenizedInput();
		REQUIRE(success);
		REQUIRE(myXMLParser.containsElementName("catalog"));
		REQUIRE(myXMLParser.frequencyElementName("catalog") == 1);
		REQUIRE(myXMLParser.containsElementName("product"));
		REQUIRE(myXMLParser.frequencyElementName("product") == 1);
		REQUIRE(myXMLParser.containsElementName("catalog_item"));
		REQUIRE(myXMLParser.frequencyElementName("catalog_item") == 2);
		REQUIRE(myXMLParser.containsElementName("item_number"));
		REQUIRE(myXMLParser.frequencyElementName("item_number") == 2);
		REQUIRE(myXMLParser.containsElementName("size"));
		REQUIRE(myXMLParser.frequencyElementName("size") == 6);
		REQUIRE(myXMLParser.containsElementName("color_swatch"));
		REQUIRE(myXMLParser.frequencyElementName("color_swatch") == 15);
}
TEST_CASE("Test invalid","[XMLParser]"){

	INFO("Hint: Testing various strings, clear in between");

	XMLParser myXMLParser;
	XMLParser my2;
	std::string test = " <someTag>Content</someTag> ";

	XMLParser my3;
	std::string testS2 = "<?xml version =\"1.0\"?><html><head>Content here</head><body>Content here<empty src=\"f\"/></body></html>";
	REQUIRE(my3.tokenizeInputString(testS2));
	
	REQUIRE( my3.parseTokenizedInput());
	REQUIRE(my2.tokenizeInputString(test));
	REQUIRE(my2.parseTokenizedInput());
	
	
	
    REQUIRE( !myXMLParser.tokenizeInputString("<.Invalid/>") );
	REQUIRE( !myXMLParser.tokenizeInputString("</test/>") );
	REQUIRE( !myXMLParser.tokenizeInputString("") );
	 REQUIRE( !myXMLParser.tokenizeInputString(" ") );

	REQUIRE( !myXMLParser.parseTokenizedInput() );
	 REQUIRE( myXMLParser.tokenizeInputString(" <tag /> ") );

	 REQUIRE( !myXMLParser.tokenizeInputString(" \n") );

	 REQUIRE( myXMLParser.tokenizeInputString(" some t?ex/.t ") );
}

TEST_CASE("Tokenize and parse XML string") {
    std::string xmlString = "<?xml?><head>sometext</head><body>sometext</body>";
	std::string xmlString2 = "<empty/><tag>content</tag>";
	std::string xmlString3 = "<tag1 <anothertag>>content</tag1>";

  
    XMLParser myXMLParser;
	
    bool tokenizeSuccess = myXMLParser.tokenizeInputString(xmlString);
    REQUIRE(tokenizeSuccess); 

   
    bool parseSuccess = myXMLParser.parseTokenizedInput();
    REQUIRE_FALSE(parseSuccess); 

	

	bool tokenizeSuccess2 = myXMLParser.tokenizeInputString(xmlString2);
    REQUIRE(tokenizeSuccess2); 

    
    bool parseSuccess2 = myXMLParser.parseTokenizedInput();
    REQUIRE_FALSE(parseSuccess2); 

	bool tokenizeSuccess3 = myXMLParser.tokenizeInputString(xmlString3);
    REQUIRE_FALSE(tokenizeSuccess3); 
	REQUIRE( !myXMLParser.parseTokenizedInput() );
   
    bool parseSuccess3 = myXMLParser.parseTokenizedInput();
    REQUIRE_FALSE(parseSuccess3); 

}

TEST_CASE("nested","[myxmlparser]"){
	std::string test1 = " <someTag>Content</someTag> ";
	std::string test2= "<?xml version =\"1.0\"?><html><head>Content here</ head><body>Content here<empty src=\"f\"/></body></html>";
	std::string test3= "</tag>reversed<tag>";
	std::string test4 = "<tag>";
	std::string test5 = "<tag1 <anothertag>>content</tag1>";

	XMLParser myXMLParser;

	REQUIRE_FALSE(myXMLParser.parseTokenizedInput());

	
	REQUIRE(myXMLParser.tokenizeInputString(test1));
	REQUIRE(myXMLParser.parseTokenizedInput());

	REQUIRE(!myXMLParser.tokenizeInputString(test2));
	REQUIRE(!myXMLParser.parseTokenizedInput());


	REQUIRE(myXMLParser.tokenizeInputString(test3));
	REQUIRE(!myXMLParser.parseTokenizedInput());


	REQUIRE(myXMLParser.tokenizeInputString(test4));
	REQUIRE(!myXMLParser.parseTokenizedInput());


	REQUIRE(!myXMLParser.tokenizeInputString(test5));
	REQUIRE(!myXMLParser.parseTokenizedInput());
	
}

TEST_CASE("frequency test", "[myxmlparser]") {
    std::string test1 = "<test>stuff</test>";
	std::string test2 = " <someTag>Content</someTag> ";
    XMLParser myXML;

	REQUIRE(myXML.tokenizeInputString(test2));
	REQUIRE(myXML.parseTokenizedInput());

    myXML.clear();

    
    myXML.tokenizeInputString(test1);
    myXML.parseTokenizedInput();

    
    REQUIRE(myXML.frequencyElementName("test") == 1);
}

TEST_CASE("test frequency and contains", "[XMLParser]") {
    XMLParser myXMLParser;
    std::string test = "<begin info=\"value\">stuff</begin>";

    REQUIRE(myXMLParser.tokenizeInputString(test));
    REQUIRE(myXMLParser.parseTokenizedInput());

    REQUIRE(myXMLParser.containsElementName("begin"));
    REQUIRE(myXMLParser.frequencyElementName("begin") == 1);
   
}

TEST_CASE("Test multiple elements", "[XMLParser]") {
    XMLParser myXMLParser;
    std::string test = "<stuff1>info1<stuff2></stuff2>info2</stuff1>";

    REQUIRE(myXMLParser.tokenizeInputString(test));
    REQUIRE(myXMLParser.parseTokenizedInput());

    REQUIRE(myXMLParser.containsElementName("stuff1"));
    REQUIRE(myXMLParser.containsElementName("stuff2"));
}



TEST_CASE("Test whitespace", "[XMLParser]") {
    XMLParser myXMLParser;
    std::string test = "<element>  blah blah blah  </element>";

    REQUIRE(myXMLParser.tokenizeInputString(test));
    REQUIRE(myXMLParser.parseTokenizedInput());

    REQUIRE(myXMLParser.containsElementName("element"));
}

TEST_CASE("Test empty", "[XMLParser]") {
    XMLParser myXMLParser;
    std::string test = "";

    REQUIRE_FALSE(myXMLParser.tokenizeInputString(test));
    REQUIRE_FALSE(myXMLParser.parseTokenizedInput());
}

TEST_CASE("Test really long string", "[XMLParser]") {
    XMLParser myXMLParser;
    std::string test = "<parent>";

    for (int i = 0; i < 10000; ++i) {
        test += "stuff ";
    }

    test += "</parent>";

    REQUIRE(myXMLParser.tokenizeInputString(test));
    REQUIRE(myXMLParser.parseTokenizedInput());
    REQUIRE(myXMLParser.containsElementName("parent"));
}

TEST_CASE("Test non alphabet characters", "[XMLParser]") {
    XMLParser myXMLParser;
    std::string test = "<st-uff_1>.&@#</st-uff_1>";

    REQUIRE(myXMLParser.tokenizeInputString(test));
    REQUIRE(myXMLParser.parseTokenizedInput());

    REQUIRE(myXMLParser.containsElementName("st-uff_1"));
}

TEST_CASE("test return tokenized input","[XMLParser]"){
	XMLParser myXMLParser;

	std::string test = "<start>content</start>";

	myXMLParser.tokenizeInputString(test);
	myXMLParser.parseTokenizedInput();

	vector<TokenStruct> returnInput = myXMLParser.returnTokenizedInput();

	std::vector<TokenStruct> result = {TokenStruct{StringTokenType::START_TAG, std::string("start")},
											TokenStruct{StringTokenType::CONTENT, std::string("content")},
											TokenStruct{StringTokenType::END_TAG, std::string("start")}};
	
	REQUIRE(result.size() == returnInput.size());
	REQUIRE(returnInput[0].tokenString.compare(result[0].tokenString) == 0);
	REQUIRE(returnInput[1].tokenString.compare(result[1].tokenString) == 0);
	REQUIRE(returnInput[2].tokenString.compare(result[2].tokenString) == 0);
}