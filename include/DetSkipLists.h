#ifndef DET_SKIP_LISTS_H
#define DET_SKIP_LISTS_H

#include <iostream>
#include <set>
#include <vector>

#include "SkipListNode.h"

class DetSkipLists{
    public:
        DetSkipLists(std::set<int> S);

        void print(void);
        bool find(int x);
        void insert(int x);

    private:
        std::set<int> elements;
        SkipListNode head;
        std::vector<SkipListNode> nodes;
        int numberOfLists;

        int CalculateNumberOfLists(int n);
        void BuildSkipLists(void);
};

#endif // DET_SKIP_LISTS_H