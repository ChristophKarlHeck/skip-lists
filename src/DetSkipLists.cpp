#include <cmath> // For std::log
#include <iostream>
#include <iomanip> // For std::setw
#include <algorithm> // For std::lower_bound

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
    std::cout << "NumberOfLists: "<< numberOfLists << std::endl;
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
    std::cout << "Level " << numberOfLists << ": " << std::endl;
    for (int level = numberOfLists - 1; level >= 0; --level) {
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

    // calculate the new number of lists needed
    numberOfLists = CalculateNumberOfLists(elements.size() + 1);

    nodes.clear();

    // I have to call buildSkip Lists, since when we need a new level, we need a new list, we need to rebuild entire list   
    BuildSkipLists();


    // Find the position where x should be inserted to keep vector sorted
    // auto it = std::lower_bound(
    //     nodes.begin(), 
    //     nodes.end(), 
    //     x,
    //     [](const SkipListNode& node, int value) {
    //         return node.getValue() < value; // Custom comparison
    //     });

    // // Convert iterator to index
    // int position = std::distance(nodes.begin(), it);
    // // Extend vector by 1 Node
    // nodes.push_back(SkipListNode(0, numberOfLists));

    // // Move values to the right
    // int iterator = nodes.size();
    // while(iterator > position){
    //     nodes[iterator].setValue(nodes[iterator-1].getValue());
    //     iterator--;
    // }
    // // Insert new value
    // nodes[position].setValue(x);

    //Make connection wiith last element. But what happens, when we need a new list?
    // Then everything has to be rebuilt;

        // Connect last node with SkipList

    // Move all values to the right
    // int level = 0;
    // for (size_t i = nodes.size(); i >= 0; i--) {

    //     if (i + 1 < nodes.size()) {
                
    //         int value = nodes[i].getValue();
    //         nodes[i+1].setValue(value);
                
    //     }
    // }

    // Rearrange the entire SkipLists DT
    // int level = 0;
    // SkipListNode* previous_node = &head;
    // SkipListNode* current_node = previous_node->getNext()[level];
    // SkipListNode* next_node = current_node->getNext()[level];

    // // Get the new node and its environment nodes
    // while(current_node->getValue() != x){
    //     previous_node = current_node;
    //     current_node = next_node;
    //     next_node = next_node->getNext()[level];
    // }

    // move all next_vectors to the left
    // while(next_node != nullptr){
    //     current_node->setNext(next_node->getNext());
    //     current_node = next_node;
    //     next_node = next_node->getNext()[level];
    // }


    //std::vector<SkipListNode*> new_vector(nbr_levels, nullptr);
    // build vector for last element 
    //current_node->setNext(new_vector);

    // repoint head

    return true;
}

bool DetSkipLists::del(int x){

    if(elements.find(x) == elements.end()){
        // Check if x is not in list
        return false;
    }

    // maintain elements for quick checks
    elements.erase(x);

    numberOfLists = CalculateNumberOfLists(elements.size() + 1);

    nodes.clear();

    BuildSkipLists();

}





