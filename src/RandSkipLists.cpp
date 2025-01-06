#include <vector>
#include <algorithm> // For std::max_element
#include <iomanip> // For std::setw

#include "RandSkipLists.h"

bool RandSkipLists::flipCoin(void){
    return dist(gen); // Directly return the random boolean
}

void RandSkipLists::BuildSkipLists(void){

    // Sort elements and create list 0
    // For each element, flip a fair coin until HEAD shows up.
    // Let the number of additional lists the element appears in.

    for (auto value : elements) {
        int nbr_tails = 0;
        while (true)
        {   
            nbr_tails++; // each node is at least in level 0. Therefore before flipCoin
            if(flipCoin()) break;
        }
        
        max_level = std::max(max_level, nbr_tails);
        nodes.push_back(SkipListNode(value, nbr_tails));
    }

    // Set head next vector with proper height
    std::vector<SkipListNode*> head_vector(max_level, nullptr);
    head.setNext(head_vector);

    for(int level = max_level-1; level >= 0; level--){
        SkipListNode* previous_node = &head;

        // Do it level by levl
        for(int i = 0; i < nodes.size(); i++){

            if(nodes[i].getNext().size() >= level + 1){
                auto& nextVector = previous_node->getNext();
                nextVector[level] = &nodes[i];
                previous_node->setNext(nextVector);
                previous_node = &nodes[i];
            }

        }

    }


    // Connect each list by the respective 

}

RandSkipLists::RandSkipLists(std::set<int> S):
    elements(S),
    head(SkipListNode(-1, 0)),
    nodes(),
    gen(std::random_device{}()),
    dist(0, 1),
    max_level(0)
{
    BuildSkipLists();            
}

void RandSkipLists::print(void){

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
    std::cout << "Level " << max_level << ": " << std::endl;
    for (int level = max_level - 1; level >= 0; --level) {
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

bool RandSkipLists::find(int x){
    // Start in highest list.
    // If next element in current list is > x. go one list down
    // Otherwise go to the next element
    // Stop if element was found or if stuck in list 0.

    SkipListNode* current_node = &head;
    std::cout << "down from level: "<< max_level << std::endl;
    for (int level = max_level -1; level >= 0; level--) {
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