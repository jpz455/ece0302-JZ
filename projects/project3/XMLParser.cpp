// Project 3 -- XML Parsing Project

/** XML parsing class implementation.
    @file XMLParser.cpp */

#include <string>
#include <assert.h>
#include "XMLParser.hpp"

// TODO: Implement the constructor here
XMLParser::XMLParser()
{
	elementNameBag = new Bag<std::string>();
    parseStack = new Stack<std::string>();
}  // end default constructor

// TODO: Implement the destructor here
XMLParser::~XMLParser()
{   
    delete elementNameBag;
    delete parseStack;
	clear();
}  // end destructor
//*********HELPER FUNCTIONS TO HELP SECTION OFF CODE***********************//

//validate characters

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

bool XMLParser::valTag(char c) {
    return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z') ||
           (c >= '0' && c <= '9') ||
           c == '_' || c == '-' || c == '.';
}

//takes care of content tokens
bool XMLParser::tokeCont(const std::string &inputString, int &index, std::string &temp){
    // Read content until '<' or end of string
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

//cannot tell the difference between start or end tokens until the index is updated accordingly
bool XMLParser::tokeStartEnd(const std::string &inputString, int &index, std::string &temp){
       index++; // Move past '<'
    // Read tag name
    while (inputString[index] != '>' && inputString[index] != '/' && !std::isspace(inputString[index])) {
       if(!valTag(inputString[index]))
       return false;
       
        temp.push_back(inputString[index]);
        index++;
    }
    // Validate tag name
    if (!isValid(temp)) {
        return false; // Invalid tag name
    }
    
    bool isEmptyTag = false;
    while (index < inputString.length() && inputString[index] != '>') {
        if (inputString[index] == '/') {
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
    // Move past '>'
    
    return true;

};

//takes care of end tokens
bool XMLParser::tokeEnd(const std::string &inputString, int &index, std::string &temp){
    index += 2; // Move past '</'
    // Read until '>'
    
    
    while (inputString[index] != '>') {

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
    index += 2; // Move past '<?'
    // Read until '?>'
    while (inputString[index] != '\?' && inputString[index + 1] != '>') {
        temp.push_back(inputString[index]);
        index++;
    }
    // Skip past '?>'
    index += 2;
    // Create token for declaration
    TokenStruct tempT = TokenStruct{StringTokenType::DECLARATION, temp};
    tokenizedInputVector.push_back(tempT);
    temp.clear();
    return true;
};

// TODO: Implement the tokenizeInputString method
bool XMLParser::tokenizeInputString(const std::string &inputString) {
   parseStack->clear();

    clear();

    std::string temp;
    int index = 0;

     if(inputString.empty() || (inputString.length() == 1 && inputString[0] == ' '))
        return false;


   
    while (index < inputString.length()) {
       //*****START OF A MARKUP********//
       
        if (inputString[index] == '<') {
            int index2 = index + 1;
            // Check for nested brackets
            while (index2 < inputString.length() && inputString[index2] != '>') {
                if (inputString[index2] == '<') {
                    clear();
                    return false;
                }
                index2++;
            }

           //********DECLARATION TOKEN************//
            if (inputString[index + 1] == '\?') {
                // Tokenize declaration
                if (!tokeDec(inputString, index, temp)) {
                    return false;
                }
            } 
            //************END TOKEN***************//
            else if (inputString[index + 1] == '/') {
                // Tokenize end tag
                if (!tokeEnd(inputString, index, temp)) {
                    return false;
                }
            } 
            //this will pass to function that can increment index accordingly to determine the last character /> or >
            else {
                // Tokenize start or empty tag
                if (!tokeStartEnd(inputString, index, temp)) {
                    return false;
                }
            }
            index = index2 + 1;
        } 

        //********CONTENT TOKEN************// 
        else if (!std::isspace(inputString[index])) {
            // Tokenize content
            if (!tokeCont(inputString, index, temp)) {
                return false;
            }
        }
        else if(tokenizedInputVector.empty() && inputString[index]== '\n')
        return false;

        else {
            index++;
           
        }
    
    }

    tokeSuccess=true;
    return true;
}

// TODO: Implement the parseTokenizedInput method here
bool XMLParser::parseTokenizedInput() {
    if (tokeSuccess) {
        std::string firstStartElement = ""; // Store the name of the first encountered start tag
        std::string lastEndElement = "";    // Store the name of the last encountered end tag
    if(tokenizedInputVector[0].tokenType == EMPTY_TAG){
        return false;
    }
        for (int i = 0; i < tokenizedInputVector.size(); ++i) {
            // Handle XML declaration (skip it)
            if (tokenizedInputVector[i].tokenType == DECLARATION) {
                continue;
            }

            // Check if it's a start tag
            if (tokenizedInputVector[i].tokenType == START_TAG) {
                // Store the name of the first encountered start tag
                if (firstStartElement.empty()) {
                    firstStartElement = tokenizedInputVector[i].tokenString;
                }
                parseStack->push(tokenizedInputVector[i].tokenString);
            }
            // Check if it's an end tag
            else if (tokenizedInputVector[i].tokenType == END_TAG) {
                // Store the name of the last encountered end tag
                lastEndElement = tokenizedInputVector[i].tokenString;
                // If the parse stack is empty, the document is invalid
                if (parseStack->isEmpty()) {
                    return false;
                }
                // Compare the end tag with the top of the parse stack
                string topOfStack = parseStack->peek();
                if (tokenizedInputVector[i].tokenString != topOfStack) {
                    return false;
                }
                // Pop the tag from the stack
                parseStack->pop();
            }
        }

        // If the first start tag does not match the last end tag, the document is invalid
        if (firstStartElement != lastEndElement) {
            return false;
        }

        // If the parse stack is not empty, the document is invalid
        if (!parseStack->isEmpty()) {
            return false;
        }

        // If all checks passed, return true
        parseSuccess=true;
        return true;
    }

    // If tokenization was not successful, return false
    return false;
}

// TODO: Implement the clear method here
void XMLParser::clear()
{
    tokenizedInputVector.clear();
    
    
   
}

vector<TokenStruct> XMLParser::returnTokenizedInput() const
{
	return tokenizedInputVector;
}

// TODO: Implement the containsElementName method
bool XMLParser::containsElementName(const std::string &inputString) const
{
if(parseSuccess&&tokeSuccess){
	    for (const auto &token : tokenizedInputVector) {
        if (token.tokenType == START_TAG || token.tokenType == END_TAG || token.tokenType == EMPTY_TAG) {
            size_t pos = token.tokenString.find(inputString);
            if (pos != std::string::npos) {
                return true;
            }
        }
    }
    return false;
}

}

// TODO: Implement the frequencyElementName method
int XMLParser::frequencyElementName(const std::string &inputString) const
{   
    if(parseSuccess&&tokeSuccess)
	return elementNameBag->getFrequencyOf(inputString);
}