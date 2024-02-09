#include <string>
#include <vector>
#include <iostream>
#include <locale> 
#include "FindPalindrome.hpp"
#include <numeric>
#include <algorithm>

using namespace std;

//------------------- HELPER FUNCTIONS -----------------------------------------

// non-class helper functions go here, should be declared as "static" so that
// their scope is limited

// helper function to convert string to lower case
static void str2lower(string & value)
{
	locale loc;
	for (int i=0; i<value.size(); i++) {
		value[i] = tolower(value[i],loc);
	}
}

// helper function to convert WORD_LIST (vector<string>) to a long string
static string wordlist2str(std::vector<std::string> list)
{
	string listStr = "";
	for(string s : list)
		listStr += s;
	return listStr;
}

// helper function to get the frequency of char c in string str
static int getCharFreq(string str, char c)
{
	int count = 0;
	for(char x : str)
		count += x == c ? 1 : 0;
	return count;
}

// helper function to determine of string str contains char c
static bool contains(string str, char c)
{
	return str.find(c) != string::npos;
}

//------------------- PRIVATE CLASS METHODS ------------------------------------

// private recursive function. Must use this signature!
void FindPalindrome::recursiveFindPalindromes(std::vector<std::string> candidateStringVector, 
                                              std::vector<std::string> currentStringVector)
{
    // Base case: If currentStringVector is empty, check if candidateStringVector forms a palindrome
    if (currentStringVector.empty()) {
        // Concatenate words in candidateStringVector to form a single string
        std::string candidateStr = wordlist2str(candidateStringVector);
        // Check if the concatenated string is a palindrome
        if (isPalindrome(candidateStr)) {
            // If it's a palindrome, add candidateStringVector to the list of palindrome sentences
            palindromes.push_back(candidateStringVector);
        }
        return;
    }

    // Recursive case: Try adding each word from currentStringVector to candidateStringVector
    for (size_t i = 0; i < currentStringVector.size(); ++i) {
        // Create copies of candidateStringVector and currentStringVector
        std::vector<std::string> nextCandidate = candidateStringVector;
        std::vector<std::string> nextCurrent = currentStringVector;
        // Add the word at index i from currentStringVector to nextCandidate
        nextCandidate.push_back(currentStringVector[i]);
        // Remove the word at index i from nextCurrent
        nextCurrent.erase(nextCurrent.begin() + i);
        // Recur with the updated vectors
        recursiveFindPalindromes(nextCandidate, nextCurrent);
    }
}


// private function to determine if a string is a palindrome (given, you
// may change this if you want)

// string passed as immediate value, no need to preserve case
bool FindPalindrome::isPalindrome(string currentString) const
{
	locale loc;
	// make sure that the string is lower case...
	str2lower(currentString);
	// see if the characters are symmetric...
	int stringLength = currentString.size();
	for(int i=1; i<stringLength/2; i++){
		if( currentString[i - 1] != currentString[stringLength - i] )
			return false;
	}
	return true;
}

bool FindPalindrome::preCheck()
{
	return cutTest1(inputWordList);
}

//------------------- PUBLIC CLASS METHODS -------------------------------------

FindPalindrome::FindPalindrome(){
}

FindPalindrome::~FindPalindrome()
{
	clear();
}

int FindPalindrome::number() const
{
	return palindromes.size();			
}

void FindPalindrome::clear()
{
	inputWordList.clear();
	palindromes.clear();		
}

bool FindPalindrome::cutTest1(const std::vector<std::string> & stringVector)
{

    std::string concatenated;
    for (const std::string& word : stringVector) {
        concatenated += word;
    }

    int oddCount = 0;
    
    for (char c : concatenated) {
        if (std::isalpha(c)) {
            int freq = std::count(concatenated.begin(), concatenated.end(), c);
            if (freq % 2 != 0) {
                oddCount++;
            }
        }
    }

    
    return oddCount <= 1;
}

bool FindPalindrome::cutTest2(const std::vector<std::string> & stringVector1,
                              const std::vector<std::string> & stringVector2)
{
   
    int charCount1[26] = {0}; 
    for (const std::string& word : stringVector1) {
        for (char c : word) {
            if (std::islower(c)) {
                charCount1[c - 'a']++; 
            }
            else if (std::isupper(c)) {
                charCount1[std::tolower(c) - 'a']++; 
            }
        }
    }

   
    for (const std::string& word : stringVector2) {
        for (char c : word) {
            if (std::islower(c)) {
                if (charCount1[c - 'a'] == 0) {
                    return false; 
                }
                charCount1[c - 'a']--; 
            }
            else if (std::isupper(c)) {
                if (charCount1[std::tolower(c) - 'a'] == 0) {
                    return false; 
                }
                charCount1[std::tolower(c) - 'a']--; 
            }
        }
    }

    return true; 
}

bool FindPalindrome::add(const string & value) {
   
    for (char c : value) {
        if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))) {
            return false;
        }
    }

    
    inputWordList.push_back(value);

    
    palindromes.clear();

   
    if (preCheck()) {
        std::vector<std::string> candidate;
        recursiveFindPalindromes(candidate, inputWordList);
    }

    return true;
}

bool FindPalindrome::add(const std::vector<std::string> & stringVector) {

    for (const std::string& word : stringVector) {
        for (char c : word) {
            if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))) {
                return false;
            }
        }
    }

    
    inputWordList.insert(inputWordList.end(), stringVector.begin(), stringVector.end());

    // Clear the palindromes list
    palindromes.clear();

    // Check if the inputWordList passes quick checks
    if (preCheck()) {
        std::vector<std::string> candidate;
        recursiveFindPalindromes(candidate, inputWordList);
    }

    return true;
}

std::vector<std::vector<std::string>> FindPalindrome::toVector() const
{
	return palindromes;
}