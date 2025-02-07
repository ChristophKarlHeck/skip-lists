#ifndef DET_SKIP_LISTS_H
#define DET_SKIP_LISTS_H

#include <iostream>
#include <set>
#include <vector>
#include <tuple>

#include "SkipListNode.h"

class DetSkipList{
    public:
        DetSkipList(std::set<int> S);

        void print(void);
        std::tuple<int,SkipListNode*> find(int x);
        int insert(int x);
        int del(int x);
        std::tuple<int,int> construct(void);

    private:
        std::set<int> m_elements;
        SkipListNode* m_head;
        int m_max_level;

        int calculateNumberOfLists(int n);
        int deleteSkipList(void);
};

#endif // DET_SKIP_LISTS_H