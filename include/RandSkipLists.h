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
        std::set<int> elements;
        SkipListNode head;
        std::vector<SkipListNode> nodes; // need to be removed
        std::mt19937 gen; // Random number generator
        std::uniform_int_distribution<> dist; // Distribution for coin flips
        int max_level;

        int flipCoin(void);
        void BuildSkipLists(void);
        std::vector<SkipListNode*> findPointersToX(int x);
        SkipListNode* getPredecessorOfRespectiveLevel(SkipListNode* node, int value, int level);
        
};

#endif // RAND_SKIP_LISTS_H