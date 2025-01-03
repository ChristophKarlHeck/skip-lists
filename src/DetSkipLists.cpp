#include "DetSkipLists.h"

DetSkipLists::DetSkipLists(std::set<int> S){
    std::cout << "Elements of S: ";
    for (const int& elem : S) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
            
}