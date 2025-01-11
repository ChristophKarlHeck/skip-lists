#include <cmath> // For std::log
#include <iostream>
#include <iomanip> // For std::setw
#include <algorithm> // For std::lower_bound

#include "DetSkipLists.h"

int DetSkipLists::calculateNumberOfLists(int n){
    
    // log2(n) <= i
    double log2 = std::log2(n);
    // Round floating-point number up to the nearest integer.
    int i = static_cast<int>(std::ceil(log2));

    return i;

}

void DetSkipLists::buildSkipLists(void) {

    // Create nodes for all elements in the set
    std::vector<SkipListNode*> helper_list;
    int position = 1; // Start with 1 otherwise modulo operation fails
    for (auto value : m_elements) {
        int nbr_lists_element_appears_in = 0;
        // Figure out in how many SkipLists the element appears in
        for (int i = 0; i < m_max_level; i++){
            int step = pow(2,i);
            if(position % step == 0){
                nbr_lists_element_appears_in ++;
            }
        }
        SkipListNode* new_node = new SkipListNode(value, nbr_lists_element_appears_in);

        // Needed to remember the 2^ith element
        helper_list.push_back(new_node); 

        position++;
    }

    // Connect nodes with pointers on each respective level
    SkipListNode* current = m_head;
    for(int i = 0; i < helper_list.size(); i++){
        for(int level = 0; level < current->getNext().size(); level++){
            int step = pow(2,level);
             if (i + step -1 < helper_list.size()) {
                auto next_vector = current->getNext();
                next_vector[level] = helper_list[i + step - 1];
                current->setNext(next_vector);
             }
        }
        current = helper_list[i];
    }
}

DetSkipLists::DetSkipLists(std::set<int> S):
    m_elements(S),
    m_head(new SkipListNode(-1, calculateNumberOfLists(S.size()) + 1)),
    m_max_level(calculateNumberOfLists(S.size() + 1))
{
    std::cout << "NumberOfLists: "<< m_max_level << std::endl;
    buildSkipLists();            
}

void DetSkipLists::print(void){

    // Collect all node values from Level 0
    std::vector<int> level_0_Positions;
    SkipListNode* current = m_head;
    while (current) {
        current = current->getNext()[0];
        if (current) {
            level_0_Positions.push_back(current->getValue());
        }
    }

    // Calculate the total number of columns (2 per node (value))
    size_t total_columns = level_0_Positions.size() * 2;

    // Print each level
    std::cout << "Level " << m_max_level << ": " << std::endl;
    for (int level = m_max_level - 1; level >= 0; --level) {
        std::cout << "Level " << level << ": ";

        current = m_head; // Start from the head for each level
        size_t column_index = 0;

        while (column_index < total_columns) {
            // In every second column insert value
            if (column_index % 2 == 0) {
                // Column for a value
                SkipListNode* nextNode = current ? current->getNext()[level] : nullptr;

                if (nextNode && nextNode->getValue() == level_0_Positions[column_index / 2]) {
                    std::cout << std::setw(4) << nextNode->getValue();
                    current = nextNode; // Move to the next node
                } else {
                    std::cout << std::setw(4) << " "; // Empty space for alignment
                }
            } 
            
            ++column_index;
        }

        // Add nullptr at the end of each level
        std::cout << std::endl;
    }
}

SkipListNode* DetSkipLists::find(int x){
    // Start in highest list.
    // If next element in current list is > x. go one list down
    // Otherwise go to the next element
    // Stop if element was found or if stuck in list 0.

    SkipListNode* current_node = m_head;
    for (int level = m_max_level; level >= 0; level--) {
        if(current_node->getNext()[level] == nullptr || current_node->getNext()[level]->getValue() > x){
            std::cout << "down from level: "<< level << std::endl;
            continue;
        }
        else{
            std::cout << "next element in level: " << level << std::endl;
            if (current_node->getNext()[level] != nullptr && current_node->getNext()[level]->getValue() == x){
                return current_node->getNext()[level];
            }
            current_node = current_node->getNext()[level];
            level++;
        }
    }

    return nullptr;
}

void DetSkipLists::deleteSkipLists(void){

    int level = 0;
    SkipListNode* current = m_head;
    SkipListNode* next = current->getNext()[level];
     // delete all nodes by level 0
    while(next!=nullptr){
        delete current;
        current = next;
        next = next->getNext()[level];
    }
}

bool DetSkipLists::insert(int x){
    
    if(m_elements.find(x) != m_elements.end()){
        // Check if x is already in list
        return false;
    }

    // maintain elements for quick checks
    m_elements.insert(x);

    // delete entire SkipLists
    deleteSkipLists();

    // calculate the new number of lists needed
    m_max_level = calculateNumberOfLists(m_elements.size() + 1);

    m_head = new SkipListNode(-1, m_max_level);

    // I have to call buildSkip Lists, since when we need a new level, we need a new list, we need to rebuild entire list   
    buildSkipLists();

    return true;
}

bool DetSkipLists::del(int x){

    if(m_elements.find(x) == m_elements.end()){
        // Check if x is not in list
        return false;
    }

    // maintain elements for quick checks
    m_elements.erase(x);

    // delete entire SkipLists
    deleteSkipLists();

    m_max_level = calculateNumberOfLists(m_elements.size() + 1);

    m_head = new SkipListNode(-1, m_max_level);

    buildSkipLists();

    return true;

}





