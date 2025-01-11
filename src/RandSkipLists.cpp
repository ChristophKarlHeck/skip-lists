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

void RandSkipLists::buildSkipLists(void){
    
    // Sort elements and create list 0.
    // Elements are sorted by default in std::set
    SkipListNode* current_node = head;
    for (auto value : elements) {
        
        int level = 0;

        // For each element, flip a fair coin until HEAD shows up
        // Let the number of additional lists the element appears in.
        int nbr_tails = flipCoin();

        // Track max_level
        max_level = std::max(max_level, nbr_tails);

        // Create new node
        SkipListNode* new_node = new SkipListNode(value, nbr_tails);

        // Add pointer from current_node 
        auto vector = current_node->getNext();
        vector[level] = new_node;
        current_node->setNext(vector);
        current_node = new_node;
    }
    
    // From level 1 to max_level - 1
    for(int level = 1; level < max_level; level++){

        // For each level add nullptr to head
        auto head_vector = head->getNext();
        head_vector.push_back(nullptr);
        head->setNext(head_vector);

        current_node = head;
        SkipListNode* next_node = current_node->getNext()[0];

        // Go through list 0 and
        // connect each list by the respective pointers
        while(next_node != nullptr){
            if(next_node->getNext().size() >= level + 1){
                auto current_vector = current_node->getNext();
                current_vector[level] = next_node;
                current_node->setNext(current_vector);
                current_node = next_node;
            }
            next_node = next_node->getNext()[0];
        }
    }
}

RandSkipLists::RandSkipLists(std::set<int> S):
    elements(S),
    head(new SkipListNode(-1, 1)),
    gen(std::random_device{}()),
    dist(0, 1),
    max_level(0)
{
    buildSkipLists();            
}

void RandSkipLists::print(void){

    // Collect all node values from Level 0
    std::vector<int> level0Positions;
    SkipListNode* current = head;
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

        current = head; // Start from the head for each level
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

    SkipListNode* current_node = head;

    //std::cout << "down from level: "<< max_level << std::endl;
    for (int level = max_level -1; level >= 0; level--) {
        if(current_node->getNext()[level] == nullptr || current_node->getNext()[level]->getValue() > x){
            //std::cout << "down from level: "<< level << std::endl;
            continue;
        }
        else{
            //std::cout << "next element in level: " << level << std::endl;
            if (current_node->getNext()[level] != nullptr && current_node->getNext()[level]->getValue() == x){
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
    SkipListNode* current_node = head;

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
            if (current_node->getNext()[level] != nullptr && current_node->getNext()[level]->getValue() == previous_element_of_x){
                auto previous_node_of_x = current_node->getNext()[level];
                // Make sure tpo get all pointers from the previous element to x
                while (level >= 0){
                    if(previous_node_of_x->getNext()[level] != nullptr && previous_node_of_x->getNext()[level]->getValue() == x){
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

std::vector<std::pair<SkipListNode*, int>> RandSkipLists::getInsertPointers(SkipListNode* new_node){
    // Start in highest list.
    // If next element in current list is > x. go one list down
    // Otherwise go to the next element
    // Stop if element was found or if stuck in list 0.

    std::vector<std::pair<SkipListNode*, int>> insertPointers;
    SkipListNode* current_node = head;

    //std::cout << "down from level: "<< max_level << std::endl;
    for (int level = new_node->getNext().size()-1; level >= 0; level--) {
        // Go level down if current_value < x && (next_value == nullptr || next_value > x)
        if(  current_node->getValue() < new_node->getValue() && 
            (current_node->getNext()[level] == nullptr || current_node->getNext()[level]->getValue() > new_node->getValue())){
            if (new_node->getNext().size() > level){
                insertPointers.push_back(std::make_pair(current_node,level));
            }
            continue;
        }
        // Go to next element if next_value < new_node_value
        else if (current_node->getNext()[level] != nullptr && current_node->getNext()[level]->getValue() < new_node->getValue()){
                current_node = current_node->getNext()[level];
                level++;
        }
        else {
            // level 0 pointer from predessor x to successor of x
            insertPointers.push_back(std::make_pair(current_node,level));
            break;
        }
    }

    return insertPointers;
}



bool RandSkipLists::insert(int x){
    
    // O (log n)
    SkipListNode* insert_node = find(x);
        // Check if x is already in list
        
    if (insert_node != nullptr){
        // Node does exist
        return false;
    }

    int nbr_tails = flipCoin();

    std::cout << "New size:" << nbr_tails << std::endl;

    SkipListNode* new_node = new SkipListNode(x,nbr_tails);

    // When size of head needs to be increased. Increase and add pointer to new_node
    if(nbr_tails > max_level){
        while (head->getNext().size() < nbr_tails)
        {   
           auto vector =  head->getNext();
           vector.push_back(new_node);
           head->setNext(vector);
        }
        max_level = nbr_tails;
    }

    // O(log n)
    auto insert_pointers = getInsertPointers(new_node);

    // O(c)
    for (const auto& pair : insert_pointers) {
        auto new_vector = new_node->getNext();
        auto ins_vector = pair.first->getNext();
        new_vector[pair.second] = pair.first->getNext()[pair.second];
        ins_vector[pair.second] = new_node;
        new_node->setNext(new_vector);
        pair.first->setNext(ins_vector);
    }

    // Maintain elements set
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

    // Fit number of levels if del element had greatest vector size 
    auto head_vector = head->getNext();
    head_vector.erase(std::remove_if(head_vector.begin(), head_vector.end(),
                    [](SkipListNode* node) { return node == nullptr; }),
                    head_vector.end());

    head->setNext(head_vector);
    max_level = head_vector.size();

    // Maintain basic set
    elements.erase(x); // O (log n)

    delete delNode;

    return true;

}