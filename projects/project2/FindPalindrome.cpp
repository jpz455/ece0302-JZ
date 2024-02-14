#include <string>
#include <vector>
#include <iostream>
#include <locale> 
#include "FindPalindrome.hpp"

using namespace std;

//------------------- HELPER FUNCTIONS -----------------------------------------

// non-class helper functions go here, should be declared as "static" so that
// their scope is limited

// helper function to convert string to lower case
static void convertToLowerCase(string & value)
{
	locale loc;
	for (unsigned int i=0; i<value.size(); i++) {
		value[i] = tolower(value[i],loc);
	}
}

// Funciton that double check the given string isnt already within the palindrome
static bool doubleCheckDup(vector<string> sVec, string inputS)
{
    //convert the possible copy string to lowercase to compare to the vector of strings
    string lowerInputS = inputS;
    convertToLowerCase(lowerInputS);

    for (string i : sVec) {
        //converting the vector of strings to all lowercase
        string sVecLower = i;
        convertToLowerCase(sVecLower);
        
        //compare the two lowercase strings to return false if there is a match
        if (sVecLower == lowerInputS) {
            return false;
        }
    }
    return true;
}

//function converts the vector that holds multiple vectors of strings into one string
static string VtoS(vector<string> vstr)
{
	vector<string> temp = vstr;
    string combined = ""; //this will hold the final string of combined strings
    for (int i = 0; i < temp.size(); i++)
		convertToLowerCase(temp[i]); //uniforming the parameter to all lowercase
	for (int i = 0; i < temp.size(); i++)
		combined += temp[i]; //appending the return string
	return combined;	
}


//------------------- PRIVATE CLASS METHODS ------------------------------------

// private recursive function. Must use this signature!
void FindPalindrome::recursiveFindPalindromes(vector<string> candidateStringVector,
                                              vector<string> currentStringVector)
{
    if(cutTest2(candidateStringVector,currentStringVector))
    //BASE: current string is empty so only need to check if canidate is a palindrome
        if (currentStringVector.empty()) {
        //form a single string from vector of strings in order to test 
        string candidateStr = VtoS(candidateStringVector);
        if (isPalindrome(candidateStr)) {
            palindromes.push_back(candidateStringVector); //adds to overall vector of palindromes if tests are passed
            //increment the number of total palindromes
            palindromeCount++;
            return;
        }
        
    }

    //RECURRING CASE: when current isnt empty program will recurrently call the function to see what words will be added to overall palindrome list
    for (size_t i = 0; i < currentStringVector.size();++i) {
       //populating candidate string vector with the possible palindrome words in current string vector
        candidateStringVector.push_back(currentStringVector[i]);
        
        //create a new vector to recur without the word that was just added above
        vector<string> nextCurrent(currentStringVector.begin(), currentStringVector.begin() + i);
        nextCurrent.insert(nextCurrent.end(), currentStringVector.begin() + i + 1, currentStringVector.end());
        
        //goes through the function again with the added word through index i and the vector without the word at index i
        recursiveFindPalindromes(candidateStringVector, nextCurrent);

        //clear word afterwards
        candidateStringVector.pop_back();
    }
}
  

// private function to determine if a string is a palindrome (given, you
// may change this if you want)
bool FindPalindrome::isPalindrome(string currentString) const
{
	locale loc;
	// make sure that the string is lower case...
	convertToLowerCase(currentString);
	// see if the characters are symmetric...
	int stringLength = currentString.size();
	if(stringLength ==1){
		return false;
	}
	for (int i=0; i<stringLength/2; i++) {
		if (currentString[i] != currentString[stringLength - i - 1]) {
			return false;
		}
		
	}
	return true;
}

//------------------- PUBLIC CLASS METHODS -------------------------------------

FindPalindrome::FindPalindrome(){}

FindPalindrome::~FindPalindrome()
{
    clear();
}

int FindPalindrome::number() const
{
	return palindromes.size();
}

void FindPalindrome::clear(){
    wordInput.clear();
    palindromes.clear();
    
}

//tests the behaviors outlined in property 1 of palindromes
bool FindPalindrome::cutTest1(const vector<string> & stringVector)
{
	string strVec = VtoS(stringVector);

    int charFreq[256] = {0}; // Initializes all elements to 256 (relating to ASCII characters 0 - 255)

    for (char i : strVec) {
        charFreq[i]++;
    }

    int odd = 0;

    for (int count : charFreq) {
        if (count % 2 != 0) { //not divisable by 2 would indicate and odd amount
            odd++;
        }
    }

    if (odd > 1 || (strVec.size() % 2 == 0 && charFreq[strVec.size() / 2] % 2 != 0)) { //returns when there are multiple characters with odd frequencies
           return false;                                                                //when the string overall length is even and character frequency isnt even
    }                                                                                   

    return true;
}

//tests the behaviors of palindromes outlined in property 2
bool FindPalindrome::cutTest2(const vector<string> & stringVector1, const vector<string> & stringVector2)
{
	string stringV1 = VtoS(stringVector1);
	string stringV2 = VtoS(stringVector2);

	if (stringV1.size() > stringV2.size()) {
        //string 1 is bigger than string 2 so string 1 should contain all the elements in string 2
		for (int i = 0; i < stringV2.size(); i++){
			if (stringV1.find(stringV2[i]) < 0 || stringV1.find(stringV2[i]) > stringV1.size())
				return false;
		}
	}
	else{
        //string 2 is bigger than string 1 so string 2 should contain all the elements of string 1
		for (unsigned int i = 0; i < stringV1.size(); i++){
			if (stringV2.find(stringV1[i]) < 0 || stringV2.find(stringV1[i]) > stringV2.size())
				return false;
		}
	}
	return true;
}

bool FindPalindrome::add(const string & value)
{
    //checks for invalid characters
	for (int i = 0; i < value.size(); i++){
		if (!((value[i] >= 65 && value[i] <= 90) || (value[i] >= 97 && value[i] <= 122)))
			return false;
	}
	//check to see if the word already exists
	if (doubleCheckDup(wordInput, value) == false)
		return false;
    else{
		wordInput.push_back(value);	//add to string vector
		//test property 1 to see if recursive function needs to be called
		if (cutTest1(wordInput))
		{
			palindromes.clear();

			vector<string> candidate;
			recursiveFindPalindromes(candidate, wordInput); //would call the base case in the recursive function
		}
    }
	return true;
}

bool FindPalindrome::add(const vector<string> & stringVector)
{
	string temp1,temp2,temp3; 
    for(int i=0;i<stringVector.size();i++){
		temp1 = stringVector[i]; 
		convertToLowerCase(temp1); 
		for(int j=0;j<temp1.length();j++){
				if(!isalpha(temp1[j])){
					return false;
				}
		}
		for(int j=0;j<wordInput.size();j++){
			temp2 = wordInput[j];
			convertToLowerCase(temp2);
			if(temp1.compare(temp2) == 0){
				return false;
			}
		}
		for(int j=0;j<stringVector.size();j++){
			if(i == j){
				j++;
            }
			if(j == stringVector.size()){
				break;
			}

			temp2 = stringVector[j];
			convertToLowerCase(temp2);
			if(temp1.compare(temp2) == 0){
				return false;
			}
		}
	}
	for(int i=0;i<stringVector.size();i++){
		wordInput.push_back(stringVector[i]); 
	}
	if(cutTest1(wordInput) == true){
		palindromes.clear();
		recursiveFindPalindromes(vector<string>(),wordInput); 
	}
	return true; 
}

vector< vector<string> > FindPalindrome::toVector() const
{
	return palindromes;
}