#include <vector>
#include <algorithm> // For std::max_element

#include "RandSkipLists.h"

bool RandSkipLists::flipCoin(void){
    return dist(gen); // Directly return the random boolean
}

void RandSkipLists::BuildSkipLists(void){

    // Sort elements and create list 0
    // For each element, flip a fair coin until HEAD shows up.
    // Let the number of additional lists the element appears in.

    int max_level = 0;
    for (auto value : elements) {
        int nbr_tails = 0;
        while (true)
        {
            if(flipCoin()) break;
            nbr_tails++;
        }
        
        max_level = std::max(max_level, nbr_tails);
        nodes.push_back(SkipListNode(value, nbr_tails));
    }

    // Set head next vector with proper height
    std::vector<SkipListNode*> head_vector(max_level, nullptr);
    head.setNext(head_vector);

    for(int level = max_level; level >= 0; level--){
        SkipListNode current_node = head;

        // Do it level by levl

    }


    // Connect each list by the respective 

}

RandSkipLists::RandSkipLists(std::set<int> S):
    elements(S),
    head(SkipListNode(-1, 0)),
    nodes(),
    gen(std::random_device{}()),
    dist(0, 1)
{
    BuildSkipLists();            
}