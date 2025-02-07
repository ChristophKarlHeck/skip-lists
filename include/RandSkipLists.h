#ifndef RAND_SKIP_LISTS_H
#define RAND_SKIP_LISTS_H

#include <iostream>
#include <set>
#include <vector>
#include <random>

#include "SkipListNode.h"

class RandSkipList{
    public:
        RandSkipList(std::set<int> S);

        void print(void);
        std::tuple<int,SkipListNode*> find(int x);
        int insert(int x);
        int del(int x);
        std::tuple<int,int> construct(void);

    private:
        std::set<int> m_elements;
        SkipListNode* m_head;
        std::mt19937 m_gen; // Random number generator
        std::uniform_int_distribution<> m_dist; // Distribution for coin flips
        int m_max_level;

        int flipCoin(void);
        std::tuple<int,std::vector<std::pair<SkipListNode*, int>>> getPointersToX(int x);
        std::tuple<int,std::vector<std::pair<SkipListNode*, int>>> getInsertPointers(SkipListNode* new_node);
        
};

#endif // RAND_SKIP_LISTS_H