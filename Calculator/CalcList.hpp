#ifndef CALCLIST_H
#define CALCLIST_H

#include "CalcListInterface.hpp"
#include <sstream>
#include <iomanip>

//Node Class for the linked List
class CalcListNode {
    friend class CalcList; // Grants access to private members of CalcListNode to CalcList.
private:
    FUNCTIONS function; // Stores the arithmetic operation.
    double operand; //stores the new value
    double result; //stores the result after the calculation
    CalcListNode* next; //stores the pointer to the next node

// Constructor for the CalcListNode.
    CalcListNode(FUNCTIONS func, double operand, double result, CalcListNode* next = nullptr) 
        : function(func), operand(operand), result(result), next(next) {}
};

// CalcList class inherits from CalcListInterface.
class CalcList : public CalcListInterface {
private:
    CalcListNode* head; // Pointer to the beginning of the list.
    double currentTotal; //keeping track of the current total 

public:
    
    CalcList();
    ~CalcList();


    double total() const override; // Returns the current total.

    void newOperation(const FUNCTIONS func, const double operand) override; // Performs a new arithmetic operation and adds the node at the front of the linked list

    void removeLastOperation() override; //remove the head node of the linked list

    std::string toString(unsigned short precision) const override; //output the linked list

    char getOperationChar(FUNCTIONS func) const; // Helper function to return character representation of the operation.
};

#endif /* CALCLIST_H */
