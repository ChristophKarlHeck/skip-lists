#include "SkipListNode.h"

// Initializes the vector with levels elements, each set to nullptr
SkipListNode::SkipListNode(int value, int level) : value(value), next(level, nullptr) {}

// Getter for value
int SkipListNode::getValue(void) const {
    return value;
}

// Setter for value
void SkipListNode::setValue(int newValue) {
    value = newValue;
}

// Getter for next vector
std::vector<SkipListNode*>& SkipListNode::getNext(void) {
    return next;
}

// Setter for next vector
void SkipListNode::setNext(const std::vector<SkipListNode*>& newNext) {
    next = newNext;
}