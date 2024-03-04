// Project 3 -- XML Parsing Project

/** XML parsing class implementation.
    @file XMLParser.cpp */

#include <string>
#include <assert.h>
#include "XMLParser.hpp"

// TODO: Implement the constructor here
XMLParser::XMLParser()
{
	//allocate space for element name bag and parse stack
    elementNameBag = new Bag<std::string>();
    parseStack = new Stack<std::string>();
}  // end default constructor

// TODO: Implement the destructor here
XMLParser::~XMLParser()
{   
     clear();
	delete elementNameBag;
	elementNameBag = nullptr;
	delete parseStack;
	parseStack = nullptr;
}  // end destructor

//*********HELPER FUNCTIONS TO HELP SECTION OFF CODE***********************//


//validate characters within a string
bool XMLParser::isValid(const std::string &tagName) const {
        // Check if the tag name is empty or begins with invalid characters
        if (tagName.empty() || tagName[0] == '-' || tagName[0] == '.' || std::isdigit(tagName[0])) {
            return false;
            
        }

        // Check if the tag name contains any invalid characters
        for (char c : tagName) {
            if (!(std::isalnum(c) || c == '_' || c == '-' || c == '.')) {
                // Check for invalid characters
                if (c == ' ' || c == '!' || c == '"' || c == '#' || c == '$' || c == '%' ||
                    c == '&' || c == '\'' || c == '(' || c == ')' || c == '*' || c == '+' ||
                    c == ',' || c == '/' || c == ';' || c == '<' || c == '=' || c == '>' ||
                    c == '?' || c == '@' || c == '[' || c == '\\' || c == ']' || c == '^' ||
                    c == '`' || c == '{' || c == '|' || c == '}' || c == '~') {
                    
                    return false;
                }
            }
        }
    return true;
}

//helper function to help determine if the tag is valid
bool XMLParser::valTag(char c) {
    return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z') ||
           (c >= '0' && c <= '9') ||
           c == '_' || c == '-' || c == '.';
}

//pass potential content tokens to this function to further test to determine if they can be added to the input vector
bool XMLParser::tokeCont(const std::string &inputString, int &index, std::string &temp){
    // Read content until < or end of string
   
    while (index < inputString.length() && inputString[index] != '<') {
        temp.push_back(inputString[index]);
        index++;
    }

    // Create token for content
    TokenStruct tempT = TokenStruct{StringTokenType::CONTENT, temp};
    tokenizedInputVector.push_back(tempT);
    temp.clear();
    return true;
};

//cannot tell the difference between start or empty tokens until the index is updated accordingly
bool XMLParser::tokeStartEmp(const std::string &inputString, int &index, std::string &temp){
       index++; // Move past <
    // Read tag name
    while (inputString[index] != '>' && inputString[index] != '/' && !std::isspace(inputString[index])) {
       if(!valTag(inputString[index])){
       tokeSuccess=false;
       return false;}
       
        temp.push_back(inputString[index]);
        index++;
    }
    // Validate tag name
    if (!isValid(temp)) {
        tokeSuccess=false;
        return false; // Invalid tag name
    }
    
    bool isEmptyTag = false;//bool variable to indicate whether empty token validity has been met
    while (index < inputString.length() && inputString[index] != '>') {
        if (inputString[index] == '/') { //if there is a backslash anywhere within the string it is empty not a start token
            isEmptyTag = true;
            break;
        }
        index++;
    }

    // Create token for start or empty tag
    if (isEmptyTag) {
        // Empty tag
        TokenStruct tempT = TokenStruct{StringTokenType::EMPTY_TAG, temp};
        tokenizedInputVector.push_back(tempT);
    } else {
        // Start tag
        TokenStruct tempT = TokenStruct{StringTokenType::START_TAG, temp};
        tokenizedInputVector.push_back(tempT);
    }
    elementNameBag->add(temp); // Add tag name to element bag
    temp.clear();  
    return true;

};

//takes care of end tokens
bool XMLParser::tokeEnd(const std::string &inputString, int &index, std::string &temp){
    index += 2; // Move past </
    // Read until >
    
    
    while (inputString[index] != '>') {//read in tag name and validate at the same time

        if(!valTag(inputString[index]))

        return false;
        
        temp.push_back(inputString[index]);
        index++;
    }

    // Create token for end tag
    TokenStruct tempT = TokenStruct{StringTokenType::END_TAG, temp};
    tokenizedInputVector.push_back(tempT);
    temp.clear();
    return true;
};

//takes care of declaration tokens
bool XMLParser::tokeDec(const std::string &inputString, int &index, std::string & temp){
    index += 2; // Move past <?
    // Read until ?>
    while (inputString[index] != '\?' && inputString[index + 1] != '>') {
        temp.push_back(inputString[index]);
        index++;
    }
    // Skip past ?>
    index += 2;
    // Create token for declaration
    TokenStruct tempT = TokenStruct{StringTokenType::DECLARATION, temp};
    tokenizedInputVector.push_back(tempT);
    temp.clear();
    return true;
};

// TODO: Implement the tokenizeInputString method
bool XMLParser::tokenizeInputString(const std::string &inputString) {
    //clear before starting another tokenization
    clear();

    //temp and index will keep track of various strings and indexes throughout the tokenization
    std::string temp;
    int index = 0;

     if(inputString.empty() || (inputString.length() == 1 && inputString[0] == ' ')){//if the input string is empty or is just a space it is not valid
        tokeSuccess=false;
        return false;
     }


    //loop through the entire inputString
    while (index < inputString.length()) {
       
       //*****START OF A MARKUP********//
       
        if (inputString[index] == '<') {//<indicates the start of some sort of token we don't know which yet
            int index2 = index + 1;
            // Check for nested brackets
            while (index2 < inputString.length() && inputString[index2] != '>') {
                if (inputString[index2] == '<') {
                    clear();
                    tokeSuccess=false;
                    return false;
                }
                index2++;
            }

           //********DECLARATION TOKEN************//
            if (inputString[index + 1] == '\?') {   
                // Tokenize declaration
                if (!tokeDec(inputString, index, temp)) {
                    tokeSuccess=false;  
                    return false;
                }
            } 
            //************END TOKEN***************//
            else if (inputString[index + 1] == '/') {
                // Tokenize end tag
                if (!tokeEnd(inputString, index, temp)) {
                    tokeSuccess=false;
                    return false;
                }
            } 
           //*********START OR EMPTY TOKEN************//
            else {
                // Tokenize start or empty token
                if (!tokeStartEmp(inputString, index, temp)) {
                    tokeSuccess=false;
                    return false;
                }
            }
            index = index2 + 1;
        } 

        //********CONTENT TOKEN************// 
        else if (!std::isspace(inputString[index])) {
            // Tokenize content
            if (!tokeCont(inputString, index, temp)) {
               tokeSuccess=false;
                return false;
            }
        }
        else if(tokenizedInputVector.empty() && inputString[index]== '\n'){
        tokeSuccess=false;
        return false;
        }

        else {
            index++;
        }
    }
    tokeSuccess=true;
    return true;
}

// TODO: Implement the parseTokenizedInput method here
bool XMLParser::parseTokenizedInput() {
   //only parse if tokenization was successful
    if (tokeSuccess) {
        std::string firstStartElement = ""; // Store the name of first start tag
        std::string lastEndElement = "";    // Store the name of the last end tag
   
   //cannot start with an empty tag
    if(tokenizedInputVector[0].tokenType == EMPTY_TAG){
        return false;
    }
    //loop through the entire input vector
        for (int i = 0; i < tokenizedInputVector.size(); ++i) {
            //jump over the declaration if there is one
            if (tokenizedInputVector[i].tokenType == DECLARATION) {
                continue;
            }

            ///***CHECK START********//
            if (tokenizedInputVector[i].tokenType == START_TAG) {
                //update to hold the name of the first start tag
                if (firstStartElement.empty()) {
                    firstStartElement = tokenizedInputVector[i].tokenString;
                }
                //push the start onto the stack
                parseStack->push(tokenizedInputVector[i].tokenString);
            }
            //*********CHECK END***********//
            else if (tokenizedInputVector[i].tokenType == END_TAG) {
                //update the name of the last end tag
                lastEndElement = tokenizedInputVector[i].tokenString;
                //cannot just hold an empty tag
                if (parseStack->isEmpty()) {
                    return false;
                }
                //compare end tag string to the top of the stack
                string topOfStack = parseStack->peek();
                if (tokenizedInputVector[i].tokenString != topOfStack) {
                    return false;
                }
                //pop tag from stack
                parseStack->pop();
            }
        }

        //if the first start tag element does not match the last end element then the parse is invalud
        if (firstStartElement != lastEndElement) {
            return false;
        }

        // cannot have an empty parse
        if (!parseStack->isEmpty()) {
            return false;
        }
        parseSuccess=true;
        return true;
    }
    return false;
}

// TODO: Implement the clear method here
void XMLParser::clear()
{
    elementNameBag->clear();
    parseStack->clear();
    tokenizedInputVector.clear();
}

vector<TokenStruct> XMLParser::returnTokenizedInput() const
{
	return tokenizedInputVector;
}

// TODO: Implement the containsElementName method
bool XMLParser::containsElementName(const std::string &inputString) const
{
    //throw a logic error if tokenization and parse was not successful
    if (!tokeSuccess || !parseSuccess) {
        throw std::logic_error("Input has not been both tokenized and parsed");
    }

    for (size_t i = 0; i < tokenizedInputVector.size(); ++i) {//loop through entire input vector
        const TokenStruct &token = tokenizedInputVector[i];//hold onto the given token at index i
        if ((token.tokenType == START_TAG || token.tokenType == END_TAG || token.tokenType == EMPTY_TAG) &&
            token.tokenString.find(inputString) != std::string::npos) {
            return true;
        }
    }
return false;
}


// TODO: Implement the frequencyElementName method
int XMLParser::frequencyElementName(const std::string &inputString) const
{   
   //cannot find frequency if tokenization and parse was not successful
    if (!tokeSuccess || !parseSuccess) {
        throw std::logic_error("Input has not been both tokenized and parsed");
    }
	return elementNameBag->getFrequencyOf(inputString);
}