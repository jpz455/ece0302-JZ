#include <string>
using std::string;
#include <stack>
#include <iostream>
#include <vector>
#include <cctype> // for isalpha

#include "algebraic_expressions.hpp"

bool isoperator(char ch) {
  return ((ch == '+') || (ch == '-') || (ch == '/') || (ch == '*'));
}

int endPost(string s, int last) {
  int first = 0;

  if ((first > last)) {
    return -1;
  }

  char ch = s[last];
  if (isalpha(ch)) {
    return last;
  } else {
    if (isoperator(ch)) {
      int lastEnd = endPost(s, last - 1);
      if (lastEnd > -1) {
        return endPost(s, lastEnd - 1);
      } else {
        return -1;
      }
    } else {
      return -1;
    }
  }
}

bool isPost(string s) {
  int firstChar = endPost(s, s.size() - 1);

  return (firstChar == 0);
}

void convert(const std::string &postfix, std::string &prefix) {
    
    std::stack<std::vector<std::string>> stack;
    //precondition
    if(isPost(postfix)){
    //iterate through every character of the postfix
    for (char i : postfix) {
      //if it isnt an operator than it must be an operand
      if (!isoperator(i)) { 
        //push it on top of the stack by converting it to a single string element i
        stack.push(std::vector<std::string>{std::string(1, i)});
      } 
      //operands need to pop the top two elements in order to perform the calculation
      else if (isoperator(i)) {  
        //need to hold onto the operator but pop it from the stack to get the two operands
        std::vector<std::string> operate;
        operate.push_back(std::string(1, i));
        //this assigns the most recent operand value to the second operand
        std::vector<std::string> op2 = stack.top();
        //this removes the top entry
        stack.pop();
        //assigns the second (but now it is the most recent entry to the first operand)
        std::vector<std::string> op1 = stack.top();
        //this removes it from the top
        stack.pop();
        
        //populating the operator with each operand after the operator
        operate.insert(operate.end(), op1.begin(), op1.end());
        operate.insert(operate.end(), op2.begin(), op2.end());
        //pushes it back onto the stack but in reverse order as the post fix notation
        stack.push(operate);
        }
    }
    //loops through the stack to assign back to the prefix notation
    std::vector<std::string> final = stack.top();
    for (const std::string &str : final) {
      prefix += str;
    }
}
}
