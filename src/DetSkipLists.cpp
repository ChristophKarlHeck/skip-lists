#include <cmath> // For std::log
#include <iostream>
#include <iomanip> // For std::setw

#include "DetSkipLists.h"

int DetSkipLists::CalculateNumberOfLists(int n){
    
    // log2(n) <= i
    double log2 = std::log2(n);
    // Round floating-point number up to the nearest integer.
    int i = static_cast<int>(std::ceil(log2));

    return i;

}

void DetSkipLists::BuildSkipLists(void) {

    // Create nodes for all elements in the set
    for (auto value : elements) {

        nodes.push_back(SkipListNode(value, numberOfLists));
    }

    // Build SkipLists
    for (int level = 0; level < numberOfLists; level++) {

        int step = pow(2,level); // 2^level

        // Make links to elements from head
        auto& nextVector = head.getNext();
        nextVector[level] = &nodes[step-1];
        head.setNext(nextVector);

        // Start at first next element from head in respective level and add links for each node
        for (size_t i = step-1; i < nodes.size(); i += step) {

            if (i + step < nodes.size()) {

                // Get the next vector of the current node
                auto& nextVector = nodes[i].getNext();
                
                // Update the next pointer for the current level
                nextVector[level] = &nodes[i + step];
                
                // Set the updated next vector back to the node
                nodes[i].setNext(nextVector);
            }
        }
    }

}

void DetSkipLists::print() {
    for (int level = numberOfLists; level >= 0; --level) {
        std::cout << "Level " << level << ": -> ";

        SkipListNode* current = &head; // Start from the head for each level
        while (current) {
            // Move to the next node at the current level
            current = current->getNext()[level];

            if (!current) {
                if (numberOfLists!= level){
                    std::cout << " -> " << nullptr;
                }
                else{
                    std::cout << nullptr;
                }
                break;
            }
            // Print the node's value and pointer
            std::cout << current->getValue();

            // Print an arrow if there is another node
            if (current->getNext()[level]) {
                std::cout << " -> ";
            }
        }

        std::cout << std::endl;
    }
}


DetSkipLists::DetSkipLists(std::set<int> S):
    elements(S),
    head(SkipListNode(-1, CalculateNumberOfLists(S.size()) + 1)),
    nodes(),
    numberOfLists(CalculateNumberOfLists(S.size() + 1))
{
    BuildSkipLists();            
}