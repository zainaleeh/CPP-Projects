#ifndef NOTATIONCONVERTER_H
#define NOTATIONCONVERTER_H

#include "NotationConverterInterface.hpp"
#include "LinkedDeque.hpp" 

class NotationConverter : public NotationConverterInterface {
public:
  std::string postfixToInfix(std::string inStr) override;
  std::string postfixToPrefix(std::string inStr) override;
  std::string infixToPostfix(std::string inStr) override;
  std::string infixToPrefix(std::string inStr) override;
  std::string prefixToInfix(std::string inStr) override;
  std::string prefixToPostfix(std::string inStr) override;
  int precedence(const std::string& op);
  bool isOperator(const std::string& token);

};

#endif
