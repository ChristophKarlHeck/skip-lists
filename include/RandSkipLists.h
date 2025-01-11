#ifndef RAND_SKIP_LISTS_H
#define RAND_SKIP_LISTS_H

#include <iostream>
#include <set>
#include <vector>
#include <random>

#include "SkipListNode.h"

class RandSkipLists{
    public:
        RandSkipLists(std::set<int> S);

        void print(void);
        SkipListNode* find(int x);
        bool insert(int x);
        bool del(int x);

    private:
        std::set<int> m_elements;
        SkipListNode* m_head;
        std::mt19937 m_gen; // Random number generator
        std::uniform_int_distribution<> m_dist; // Distribution for coin flips
        int m_max_level;

        int flipCoin(void);
        void buildSkipLists(void);
        std::vector<std::pair<SkipListNode*, int>> getPointersToX(int x);
        std::vector<std::pair<SkipListNode*, int>> getInsertPointers(SkipListNode* new_node);
        
};

#endif // RAND_SKIP_LISTS_H