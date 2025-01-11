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
        SkipListNode* find(int x);
        bool insert(int x);
        bool del(int x);

    private:
        std::set<int> m_elements;
        SkipListNode* m_head;
        int m_max_level;

        int calculateNumberOfLists(int n);
        void buildSkipLists(void);
        void deleteSkipLists(void);
};

#endif // DET_SKIP_LISTS_H