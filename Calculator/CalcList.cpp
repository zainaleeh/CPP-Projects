#include "CalcList.hpp"
#include <stdexcept>

CalcList::CalcList() : head(nullptr), currentTotal(0.0) {} // Constructor

CalcList::~CalcList() { // Destructor to avoid any memory leaks
    while(head != nullptr) {
        CalcListNode* temp = head;
        head = head->next;
        delete temp;
    }
}

double CalcList::total() const { //function to get the currentTotal
    return currentTotal;
}

void CalcList::newOperation(const FUNCTIONS func, const double operand) { //Add a new node at the front of the linked list
    double newResult = currentTotal;
    switch(func) { 
        case ADDITION: newResult += operand; break;
        case SUBTRACTION: newResult -= operand; break;
        case MULTIPLICATION: newResult *= operand; break;
        case DIVISION: {
          if(operand == 0) { //check for division by 0
            throw std::runtime_error("Division by zero is not allowed.");}
          newResult /= operand;
            break;
    }
    

    }
  // Create a new node with the operation and result, then link it at the front.
    CalcListNode* newNode = new CalcListNode(func, operand, newResult);
    newNode->next = head;
    head = newNode;
    currentTotal = newResult;
}

void CalcList::removeLastOperation() {
    // Check if list is empty
    if(head == nullptr) {
        throw std::runtime_error("Cannot remove from an empty CalcList.");
    }

    // If only one node in the list
    if(head->next == nullptr) {
        delete head;
        head = nullptr;
        currentTotal = 0.0;  // reset the currentTotal
        return;
    }

    // If there's more than one node, update the total to the value of the next operation
    currentTotal = head->next->result;

    // Store the current head temporarily
    CalcListNode* temp = head;

    // Move the head pointer to the next node
    head = head->next;

    // Delete the old head
    delete temp;
}


std::string CalcList::toString(unsigned short precision) const {
    std::stringstream ss;
    
    // Count the number of operations
    int step = 0;
    for(CalcListNode* countNode = head; countNode != nullptr; countNode = countNode->next) {
        step++;
    } 

  //two pointers to transverse over the list and output the string in the right format
    CalcListNode* prev = head;
    CalcListNode* curr = (head) ? head->next : nullptr;  // Starts at the second node, if exists

    while (curr) { //as long as curr pointer doesn't reach null/end of list
        ss << step-- << ": " 
           << std::fixed << std::setprecision(precision) << curr->result
           << getOperationChar(prev->function)
           << prev->operand 
           << "=" << prev->result << "\n";

        prev = curr; //move the pointers forward
        curr = curr->next;
    }

    if(prev) {  // when prev reaches the last node
        ss << step << ": "
           << std::fixed << std::setprecision(precision) << 0.0  // For the initial value, as given in the example
           << getOperationChar(prev->function)
           << prev->operand 
           << "=" << prev->result << "\n";
    }

    return ss.str();
}




// Helper function that returns the character representation of an arithmetic function.
char CalcList::getOperationChar(FUNCTIONS func) const {
    switch(func) {
        case ADDITION: return '+';
        case SUBTRACTION: return '-';
        case MULTIPLICATION: return '*';
        case DIVISION: return '/';
        default: return ' ';
    }
}
