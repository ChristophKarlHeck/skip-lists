#include <vector>
#include <algorithm> // For std::max_element
#include <iomanip> // For std::setw

#include "RandSkipLists.h"

int RandSkipLists::flipCoin(void){

    int nbr_tails = 0;
    while (true)
    {   
        nbr_tails++; // each node is at least in level 0. Therefore before flipCoin
        // Directly return the random boolean
        if(dist(gen)) return nbr_tails;
    }
    return -1; 
}

void RandSkipLists::BuildSkipLists(void){

    // Sort elements and create list 0
    // For each element, flip a fair coin until HEAD shows up.
    // Let the number of additional lists the element appears in.

    for (auto value : elements) {
        
        int nbr_tails = flipCoin();
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

SkipListNode* RandSkipLists::find(int x){
    // Start in highest list.
    // If next element in current list is > x. go one list down
    // Otherwise go to the next element
    // Stop if element was found or if stuck in list 0.

    SkipListNode* current_node = &head;

    //std::cout << "down from level: "<< max_level << std::endl;
    for (int level = max_level -1; level >= 0; level--) {
        if(current_node->getNext()[level] == nullptr || current_node->getNext()[level]->getValue() > x){
            //std::cout << "down from level: "<< level << std::endl;
            continue;
        }
        else{
            //std::cout << "next element in level: " << level << std::endl;
            if (current_node->getNext()[level]->getValue() == x){
                //std::cout <<  "Found:" << current_node->getNext()[level] << std::endl;
                return current_node->getNext()[level];
            }
            current_node = current_node->getNext()[level];
            level++;
        }
    }

    return nullptr;
}

std::vector<std::pair<SkipListNode*, int>> RandSkipLists::getPointersToX(int x){
    // Find previous element of x and on the way to it store pointers to x

    std::vector<std::pair<SkipListNode*, int>> pointersToX;
    SkipListNode* current_node = &head;

    auto it = elements.find(x); // O(log n)
    int previous_element_of_x = -1; // Default to -1, representing the head

    // Check if x is not the smallest element
    if (it != elements.begin()){
        --it; // Decrement safely
        previous_element_of_x = *it; // Set to the predecessor of x
    }

    // Go through each level from the max level
    for (int level = max_level -1; level >= 0; level--) {
        if(current_node->getNext()[level] == nullptr || current_node->getNext()[level]->getValue() > previous_element_of_x){
            if(current_node->getNext()[level] != nullptr && current_node->getNext()[level]->getValue() == x){
                // Store pointer to x
                pointersToX.push_back(std::make_pair(current_node,level));
            }
            // Go one level down
            continue;
        }
        else{

            // If the next node matches the predecessor of x 
            if (current_node->getNext()[level]->getValue() == previous_element_of_x){
                auto previous_node_of_x = current_node->getNext()[level];
                // Make sure tpo get all pointers from the previous element to x
                while (level >= 0){
                    if(previous_node_of_x->getNext()[level]->getValue() == x){
                        pointersToX.push_back(std::make_pair(previous_node_of_x,level));
                    }
                    level--;
                }

                break; // Exit the loop once all pointers are added
            }

            // Move to the next node on the same level
            current_node = current_node->getNext()[level];
            level++;
        }
    }

    return pointersToX;
}



bool RandSkipLists::insert(int x){
    
    SkipListNode* insert_node = find(x); // O (log n)
        // Check if x is already in list
        
    if (insert_node != nullptr){
        // Node does exist
        return false;
    }

    int nbr_tails = flipCoin();
    max_level = std::max(max_level, nbr_tails);

    auto upper_bound = elements.upper_bound(x);
    auto lower_bound = std::prev(upper_bound);


    SkipListNode* successor_node = find(*upper_bound);
    SkipListNode* predecessor_node = find(*lower_bound);
    SkipListNode new_node = SkipListNode(x,nbr_tails);

    auto vector_1 = predecessor_node->getNext();
    vector_1[0] = &new_node;
    predecessor_node->setNext(vector_1);
    auto vector = new_node.getNext();
    vector[0] = successor_node;
    new_node.setNext(vector);

    elements.insert(x);

    return true;

}

bool RandSkipLists::del(int x){

    auto delNode = find(x); // O(log n)

    // Check if x is in skip list
    if (delNode == nullptr) { // O(log n)
        return false;
    }

    auto pointersToX = getPointersToX(x); // O(log n)

    // O(c); c = # number of pointers to x
    // Redirect pointers
    for(int i = 0; i < pointersToX.size(); i++){
       auto vector = pointersToX[i].first->getNext();
       vector[pointersToX[i].second] = delNode->getNext()[pointersToX[i].second];
       pointersToX[i].first->setNext(vector);
    }

    elements.erase(x); // O (log n)

    return true;

}

// bool RandSkipLists::del(int x){

//     SkipListNode* del_node = find(x); // O (log n)

//     if (del_node == nullptr){
//         // Node does not exist
//         return false;
//     }

//     auto next_vector = del_node->getNext();
    
//     // find Predecessors and redirect pointers
//     for(int level = del_node->getNext().size() - 1; level >= 0; level--){
//         SkipListNode* current_node = &head;

//         current_node = getPredecessorOfRespectiveLevel(current_node,x,level);

//         //  Redirect pointer on respective level           
//         auto next_vector = current_node->getNext();
//         next_vector[level] = del_node->getNext()[level];
//         current_node->setNext(next_vector);       
//     }

//     elements.erase(x);

//     return true;
// }