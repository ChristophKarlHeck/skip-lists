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

DetSkipLists::DetSkipLists(std::set<int> S):
    elements(S),
    head(SkipListNode(-1, CalculateNumberOfLists(S.size()) + 1)),
    nodes(),
    numberOfLists(CalculateNumberOfLists(S.size() + 1))
{
    BuildSkipLists();            
}

void DetSkipLists::print(void) {
    // Collect all node values from Level 0
    std::vector<int> level0Positions;
    SkipListNode* current = &head;
    while (current) {
        current = current->getNext()[0];
        if (current) {
            level0Positions.push_back(current->getValue());
        }
    }

    // Calculate the total number of columns (2 per node: value + arrow)
    size_t totalColumns = level0Positions.size() * 2;

    // Print each level
    for (int level = numberOfLists; level >= 0; --level) {
        std::cout << "Level " << level << ": ";

        current = &head; // Start from the head for each level
        size_t columnIndex = 0;

        while (columnIndex < totalColumns) {
            // Determine if this column should contain a value or an arrow
            if (columnIndex % 2 == 0) {
                // Column for a value
                SkipListNode* nextNode = current ? current->getNext()[level] : nullptr;

                if (nextNode && nextNode->getValue() == level0Positions[columnIndex / 2]) {
                    std::cout << std::setw(4) << nextNode->getValue();
                    current = nextNode; // Move to the next node
                } else {
                    std::cout << std::setw(4) << " "; // Empty space for alignment
                }
            } 
            
            ++columnIndex;
        }

        // Add nullptr at the end of each level
        std::cout << std::endl;
    }
}

bool DetSkipLists::find(int x){
    // Start in highest list.
    // If next element in current list is > x. go one list down
    // Otherwise go to the next element
    // Stop if element was found or if stuck in list 0.

    SkipListNode* current_node = &head;
    for (int level = numberOfLists; level >= 0; level--) {
        if(current_node->getNext()[level] == nullptr || current_node->getNext()[level]->getValue() > x){
            std::cout << "down from level: "<< level << std::endl;
            continue;
        }
        else{
            std::cout << "next element in level: " << level << std::endl;
            if (current_node->getNext()[level]->getValue() == x){
                return true;
            }
            current_node = current_node->getNext()[level];
            level++;
        }
    }

    return false;
}

bool DetSkipLists::insert(int x){
    
    if(elements.find(x) != elements.end()){
        // Check if x is already in list
        return false;
    }

    // maintain elements for quick checks
    elements.insert(x);
    
    // Insert node in vector
    // Find the position where x should be inserted to keep vector sorted
    auto it = std::lower_bound(nodes.begin(), nodes.end(), x);
    // Insert x at the found position
    nodes.insert(it, SkipListNode(x, numberOfLists));
    // convert iterator to index
    int position = std::distance(nodes.begin(), it);

    // Rearrange the entire SkipLists DT
    int level = 0;
    SkipListNode* previous_node = &head;
    SkipListNode* current_node = previous_node->getNext()[level];
    SkipListNode* next_node = current_node->getNext()[level];

    // Get the new node and its environment nodes
    while(current_node->getValue() != x){
        previous_node = current_node;
        current_node = next_node;
        next_node = next_node->getNext()[level];
    }

    // move all next_vectors to the left
    while(next_node == nullptr){
        current_node->setNext(next_node->getNext());
        current_node = next_node;
        next_node = next_node->getNext()[level];
    }

    // get number of lists last element should be integrated
    int nbr_levels = 0;
    for(int i=0; i < numberOfLists; i++){
        int result = pow(2,i); // 2^level
        if(result % position == 0){
            nbr_levels++;
        }
    }
    std::vector<SkipListNode*> new_vector(nbr_levels, nullptr);
    // build vector for last element 
    current_node->setNext(new_vector);

    // repoint head



    return true;

}