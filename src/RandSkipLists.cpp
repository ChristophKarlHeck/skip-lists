#include <vector>
#include <algorithm> // For std::max_element
#include <iomanip> // For std::setw

#include "RandSkipLists.h"

int RandSkipList::flipCoin(void){

    int nbr_tails = 0;
    while (true)
    {   
        nbr_tails++; // each node is at least in level 0. Therefore before flipCoin
        // Directly return the random boolean
        if(m_dist(m_gen)) return nbr_tails;
    }
    return -1; 
}

std::tuple<int,int> RandSkipList::construct(void){

    int number_of_steps = 0; // runtime analysis
    
    // Sort elements and create list 0.
    // Elements are sorted by default in std::set
    SkipListNode* current_node = m_head;
    for (auto value : m_elements) {
        number_of_steps++;

        int level = 0;

        // For each element, flip a fair coin until HEAD shows up
        // Let the number of additional lists the element appears in.
        int nbr_tails = flipCoin();

        // Track max_level
        m_max_level = std::max(m_max_level, nbr_tails);

        // Create new node
        SkipListNode* new_node = new SkipListNode(value, nbr_tails);

        // Add pointer from current_node 
        auto vector = current_node->getNext();
        vector[level] = new_node;
        current_node->setNext(vector);
        current_node = new_node;
    }
    
    // From level 1 to max_level
    for(int level = 1; level < m_max_level; level++){
        number_of_steps++;

        // For each level add nullptr to head
        auto head_vector = m_head->getNext();
        head_vector.push_back(nullptr);
        m_head->setNext(head_vector);

        current_node = m_head;
        SkipListNode* next_node = current_node->getNext()[0];

        // Go through list 0 and
        // connect each list by the respective pointers
        while(next_node != nullptr){
            number_of_steps++;
            if(next_node->getNext().size() >= level + 1){
                auto current_vector = current_node->getNext();
                current_vector[level] = next_node;
                current_node->setNext(current_vector);
                current_node = next_node;
            }
            next_node = next_node->getNext()[0];
        }
    }

    return std::make_tuple(number_of_steps, m_max_level);
}

RandSkipList::RandSkipList(std::set<int> S):
    m_elements(S),
    m_head(new SkipListNode(-1, 1)),
    m_gen(std::random_device{}()),
    m_dist(0, 1),
    m_max_level(0)
{ }

void RandSkipList::print(void){

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

std::tuple<int,SkipListNode*> RandSkipList::find(int x){
    // Start in highest list.
    // If next element in current list is > x. go one list down
    // Otherwise go to the next element
    // Stop if element was found or if stuck in list 0.

    int number_of_steps = 0; // runtime analysis

    SkipListNode* current_node = m_head;

    //std::cout << "down from level: "<< m_max_level << std::endl;
    for (int level = m_max_level -1; level >= 0; level--) {
        number_of_steps++;
        if(current_node->getNext()[level] == nullptr || current_node->getNext()[level]->getValue() > x){
            //std::cout << "down from level: "<< level << std::endl;
            if(level==0){
                std::cout << "NOT FOUND" << std::endl;
                break;
            }
            continue;
        }
        else{
            //std::cout << "next element in level: " << level << std::endl;
            if (current_node->getNext()[level] != nullptr && current_node->getNext()[level]->getValue() == x){
                //std::cout <<  "Found:" << current_node->getNext()[level] << std::endl;
                return std::make_tuple(number_of_steps,current_node->getNext()[level]);
            }
            current_node = current_node->getNext()[level];
            level++;
        }
    }

    return std::make_tuple(number_of_steps,nullptr);
}

std::tuple<int,std::vector<std::pair<SkipListNode*, int>>> RandSkipList::getPointersToX(int x){
    // Find previous element of x and on the way to it store pointers to x

    int number_of_steps = 0; // runtime analysis

    std::vector<std::pair<SkipListNode*, int>> pointersToX;
    SkipListNode* current_node = m_head;

    auto it = m_elements.find(x); // O(log n)
    int previous_element_of_x = -1; // Default to -1, representing the head

    // Check if x is not the smallest element
    if (it != m_elements.begin()){
        --it; // Decrement safely
        previous_element_of_x = *it; // Set to the predecessor of x
    }

    // Go through each level from the max level
    for (int level = m_max_level -1; level >= 0; level--) {
        number_of_steps++;
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
                    number_of_steps++;
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

    return std::make_tuple(number_of_steps,pointersToX);
}

std::tuple<int,std::vector<std::pair<SkipListNode*, int>>> RandSkipList::getInsertPointers(SkipListNode* new_node){
    // Start in highest list.
    // If next element in current list is > x. go one list down
    // Otherwise go to the next element
    // Stop if element was found or if stuck in list 0.

    int number_of_steps = 0; // runtime analysis

    std::vector<std::pair<SkipListNode*, int>> insertPointers;
    SkipListNode* current_node = m_head;

    //std::cout << "down from level: "<< max_level << std::endl;
    for (int level = m_max_level-1; level >= 0; level--) {
        number_of_steps++;
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

    return std::make_tuple(number_of_steps,insertPointers);
}



int RandSkipList::insert(int x){

    int number_of_steps = 0; // runtime analysis
    
    // O (log n)
    auto [number_of_finding_steps, insert_node] = find(x);
    number_of_steps += number_of_finding_steps;
        
    // Check if x is already in list   
    if (insert_node != nullptr){
        // Node does exist
        return false;
    }

    int nbr_tails = flipCoin();

    std::cout << "New size:" << nbr_tails << std::endl;

    SkipListNode* new_node = new SkipListNode(x,nbr_tails);

    // When size of head needs to be increased. Increase and add pointer to new_node
    if(nbr_tails > m_max_level){
        while (m_head->getNext().size() < nbr_tails)
        {  
           number_of_steps++;
           auto vector = m_head->getNext();
           vector.push_back(new_node);
           m_head->setNext(vector);
        }
        m_max_level = nbr_tails;
    }

    // O(log n)
    auto [number_steps_get_pointers, insert_pointers] = getInsertPointers(new_node);
    number_of_steps += number_steps_get_pointers;

    // O(c)
    for (const auto& pair : insert_pointers) {
        number_of_steps++;
        auto new_vector = new_node->getNext();
        auto ins_vector = pair.first->getNext();
        new_vector[pair.second] = pair.first->getNext()[pair.second];
        ins_vector[pair.second] = new_node;
        new_node->setNext(new_vector);
        pair.first->setNext(ins_vector);
    }

    // Maintain elements set
    m_elements.insert(x);
    number_of_steps += std::log2(m_elements.size());

    return number_of_steps;

}

int RandSkipList::del(int x){

    int number_of_steps = 0; // runtime analysis

    auto [number_of_finding_steps, del_node] = find(x); // O(log n)
    number_of_steps += number_of_finding_steps; 

    // Check if x is in skip list
    if (del_node == nullptr) { // O(log n)
        return false;
    }

    auto [number_steps_get_pointers, pointers_to_x]= getPointersToX(x); // O(log n)
    number_of_steps += number_steps_get_pointers; 

    // O(c); c = # number of pointers to x
    // Redirect pointers
    for(int i = 0; i < pointers_to_x.size(); i++){
       number_of_steps++;
       auto vector = pointers_to_x[i].first->getNext();
       vector[pointers_to_x[i].second] = del_node->getNext()[pointers_to_x[i].second];
       pointers_to_x[i].first->setNext(vector);
    }

    // Fit number of levels if del element had greatest vector size 
    auto head_vector = m_head->getNext();
    head_vector.erase(std::remove_if(head_vector.begin(), head_vector.end(),
                    [](SkipListNode* node) { return node == nullptr; }),
                    head_vector.end());

    m_head->setNext(head_vector);
    m_max_level = head_vector.size();

    // Maintain basic set
    m_elements.erase(x); // O (log n)
    number_of_steps += std::log2(m_elements.size());

    delete del_node;

    return number_of_steps;

}