#ifndef SKIPLISTNODE_H
#define SKIPLISTNODE_H
#include <vector>

// Class representing a single node in the skip list
class SkipListNode {
public:
    // Constructor
    SkipListNode(int value, int level);

    // Getter for value
    int getValue(void) const;

    // Setter for value
    void setValue(int newValue);

    // Getter for next vector
    std::vector<SkipListNode*>& getNext(void);

    // Setter for next vector
    void setNext(const std::vector<SkipListNode*>& newNext);

private:
    int value;                          // Value stored in the node
    std::vector<SkipListNode*> next;    // Vector of pointers to the next nodes at each level
};

#endif // SKIPLISTNODE_H