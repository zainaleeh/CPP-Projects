#include "NotationConverter.hpp"
#include <algorithm>

std::string NotationConverter::postfixToInfix(std::string inStr) {
  std::string element, infix;
  LinkedDeque<std::string> LinkedDeque; // Create a deque to hold the operators
  
  size_t i = 0;
  while (i < inStr.size()) { //Traverse through each character in the input string
    if (std::isspace(inStr[i])) {  //check for spaces in the string
      i++; 
      continue;
    }
    
    else if (isOperator(std::string(1, inStr[i]))) { //check for an operator
      element = std::string(1, inStr[i]);
      if (LinkedDeque.size() < 2) throw std::invalid_argument("Invalid postfix expression");
            
      else{
        std::string operand2 = LinkedDeque.back(); 
        LinkedDeque.removeBack(); // Pop operand2 from the deque
        std::string operand1 = LinkedDeque.back(); 
        LinkedDeque.removeBack(); // Pop operand1 from the deque
      
      // Form the infix string and push it back to the deque
      LinkedDeque.insertBack("(" + operand1 + " " + element + " " + operand2 + ")");
        i++;
      }
        } 
    else {
      // If the token is an operand
      //element = std::string(1, inStr[i]);
      LinkedDeque.insertBack(std::string(1, inStr[i]));
      i++;// Push operand to the deque
        }
    }

  if (LinkedDeque.size() != 1){
        throw std::invalid_argument("Invalid postfix expression");
    }
  infix = LinkedDeque.back();

  return infix; // Return the infix expression
}
  


std::string NotationConverter::postfixToPrefix(std::string inStr) {
  std::string infix = this->postfixToInfix(inStr);
  return this->infixToPrefix(infix);
}


  

std::string NotationConverter::infixToPostfix(std::string inStr) {
  
  std::string element, postfix;
  LinkedDeque<std::string> LinkedDeque; // Create a deque to hold the operators
  
  size_t i = 0;
  while (i < inStr.size()) { //Traverse through each character in the input string
    if (std::isspace(inStr[i])) {  //check for spaces in the string
      i++; 
      continue;
    }
    
    if (isOperator(std::string(1, inStr[i]))) { //check for an operator
      element = std::string(1, inStr[i]); //convert char to string

      // Pop operators from the deque while the precedence is greater or equal and append them to postfix
      while (!LinkedDeque.empty() && precedence(LinkedDeque.back()) >= precedence(element)) {
        
        postfix += LinkedDeque.back() + ' '; //pass the last elem in deque in postfix exp
        LinkedDeque.removeBack(); //remove the last elem from deque
        
      }
      
      LinkedDeque.insertBack(element); // insert string elem in the deque
      i++;
    } 
      
    else if (inStr[i] == '(') {
      LinkedDeque.insertBack("("); //insert a string parenthesis 
      i++;
    } 
    
    else if (inStr[i] == ')') { 
      // Pop operators from the deque and append them to postfix until an open parenthesis is encountered
      while (!LinkedDeque.empty() && LinkedDeque.back() != "(") {
        postfix += LinkedDeque.back() + ' '; //keep updateing postfix with the elem in deque until ( is found
        LinkedDeque.removeBack(); //removing the last elem in deque
      }
      
      if (LinkedDeque.empty()) throw std::invalid_argument("Mismatched parentheses");
            LinkedDeque.removeBack(); // pop the left parenthesis
            i++;
        }
      
    else { // operand
    if(!std::isdigit(inStr[i]) && !std::isalpha(inStr[i]) && !isOperator(std::string(1, inStr[i])) && inStr[i] != ')' && inStr[i] != '(') {
                throw std::invalid_argument("Invalid character in expression");
              }
    // If it's a valid operand
         
    postfix += std::string(1, inStr[i]) + ' '; // converts '' to ""
    i++;
      
    }   
  }
    // Append any remaining operators in the deque to postfix
    while (!LinkedDeque.empty()) {
        if (LinkedDeque.back() == "(") throw std::invalid_argument("Mismatched parentheses");
        postfix += LinkedDeque.back() + ' ';
        LinkedDeque.removeBack();
    }

    return postfix; // return the final postfix string
}





std::string NotationConverter::infixToPrefix(std::string inStr) {
/*reverse the string first, apply the precedence and associavity 
rules (a little different than infix to prefix), add and remove
from the back of the deque, and then reverse the prefix again
  */

    std::string element, prefix;
    LinkedDeque<std::string> LinkedDeque; // Create a deque to hold the operators

    // Reverse the input infix string since we are converting to prefix
    std::reverse(inStr.begin(), inStr.end());

    size_t i = 0;
    while (i < inStr.size()) { // Traverse through each character in the input string

        if (std::isspace(inStr[i])) {  // Check for spaces in the string
            i++;
            continue;
        }

        if (isOperator(std::string(1, inStr[i]))) { // Check for an operator
            element = std::string(1, inStr[i]); // Convert char to string

            // Pop operators from the deque while the precedence is greater or equal and append them to prefix
            while (!LinkedDeque.empty() && precedence(LinkedDeque.back()) > precedence(element)) {
                prefix += LinkedDeque.back() + ' '; // Prepend the operators from deque to prefix
                LinkedDeque.removeBack(); // Remove the front element from deque
            }

            LinkedDeque.insertBack(element); // Insert string element in the deque
            i++;
        } else if (inStr[i] == ')') {
            LinkedDeque.insertBack(")"); // Mirror the infix, ')' will be encountered first
            i++;
        } else if (inStr[i] == '(') {
            // Pop operators from the deque and prepend them to prefix until a closing parenthesis is encountered
            while (!LinkedDeque.empty() && LinkedDeque.back() != ")") {
                prefix += LinkedDeque.back() + ' ';// Prepend the operators from deque to prefix
                LinkedDeque.removeBack(); // Remove the front element from deque
            }

            if (LinkedDeque.empty()) throw std::invalid_argument("Mismatched parentheses");
            LinkedDeque.removeBack(); // Remove the mirrored closing parenthesis
            i++;
        } else {
    // if the character is not an operand, operator, or parenthesis, throw an exception
              if(!std::isdigit(inStr[i]) && !std::isalpha(inStr[i]) && !isOperator(std::string(1, inStr[i])) && inStr[i] != ')' && inStr[i] != '(') {
                throw std::invalid_argument("Invalid character in expression");
              }
    // If it's a valid operand
          prefix += std::string(1, inStr[i]) + ' '; // Prepend operands to prefix string
          i++;
}
    }

    // Prepend any remaining operators in the deque to prefix
    while (!LinkedDeque.empty()) {
        if (LinkedDeque.back() == ")" || LinkedDeque.back() == "(")
            throw std::invalid_argument("Mismatched parentheses");
        prefix += LinkedDeque.back() + ' ';
        LinkedDeque.removeBack();
    }

    // Reverse the prefix string to get the final correct prefix expression
    std::reverse(prefix.begin(), prefix.end());
    return prefix; // Return the final prefix string
}


std::string NotationConverter::prefixToInfix(std::string inStr) {
    std::string element, infix;
    LinkedDeque<std::string> LinkedDeque; // Create a stack to hold the operands
    
    // Start reading the prefix string from right to left
    for(int i = inStr.size() - 1; i >= 0; i--) {
        
        // Skip spaces
        if(std::isspace(inStr[i]))
            continue;
        
        // Check if the current symbol is an operator
        if(isOperator(std::string(1, inStr[i]))) {
            if(LinkedDeque.size() < 2) // There must be at least two operands on the stack for a valid prefix expression
                throw std::invalid_argument("Invalid prefix expression");

            std::string operand1 = LinkedDeque.back(); 
            LinkedDeque.removeBack(); // Pop operand1 from the stack
            std::string operand2 = LinkedDeque.back(); 
            LinkedDeque.removeBack(); // Pop operand2 from the stack

            // Concatenate the popped operands and the operator, surround with parentheses, and push back to stack
            LinkedDeque.insertBack("(" + operand1 + " " + inStr[i] + " " + operand2 + ")");
        } 
        else { // The symbol is an operand
            LinkedDeque.insertBack(std::string(1, inStr[i])); // Push operand to the stack
        }
    }
    
    if(LinkedDeque.size() != 1) // There must be only one element left in the stack, the infix expression
        throw std::invalid_argument("Invalid prefix expression");
    
    infix = LinkedDeque.back(); // The final element in the stack is the infix expression
    return infix;
}


std::string NotationConverter::prefixToPostfix(std::string inStr) {
  std::string infix = this->prefixToInfix(inStr);
  return this->infixToPostfix(infix);
  

}

int NotationConverter::precedence(const std::string& op) {
    if (op == "+" || op == "-") return 1;
    if (op == "*" || op == "/") return 2;
    return 0;
    
}

bool NotationConverter::isOperator(const std::string& token) {
    return token == "+" || token == "-" || token == "*" || token == "/";
}