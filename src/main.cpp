#include <chrono>
#include <set>

#include "DetSkipLists.h"
#include "RandSkipLists.h"
#include "utils.h"

int main(int argc, char *argv[])
{
    // Ensure the user provides the required argument
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <number_of_elements>" << std::endl;
        return 1;
    }

    // Convert the command-line argument to an integer
    int n = std::atoi(argv[1]);
    if (n <= 0) {
        std::cerr << "Error: The number of elements must be a positive integer." << std::endl;
        return 1;
    }
  

    // for(int i = 0; i < 100000; i++){
    //     std::set<int> S = createRandomSet(n, lower_bound, upper_bound);
    //     RandSkipLists RandSkipLists(S);
    //     RandSkipLists.print();
    //     RandSkipLists.del(5);
    //     RandSkipLists.print();
    //     if(RandSkipLists.find(5)!=nullptr){
    //         throw std::runtime_error("Value 5 not found in the skip list.");
    //     }
    //     RandSkipLists.insert(5);
    //     RandSkipLists.print();
    //     if(RandSkipLists.find(5)==nullptr){
    //         throw std::runtime_error("Value 5 not found in the skip list.");
    //     }
    // }

    for(int i = 0; i < 100000; i++){
        std::set<int> S = Utils::createRandomSet(n);
        rand_element =  
        DetSkipLists DetSkipLists(S);
        DetSkipLists.del(5);
        DetSkipLists.insert(5);
    }

    // benchmark("RandSkipList Find", RandSkipLists, [&](auto& list) {
    //     for (int i = 0; i < n; ++i) list.find(i);
    // }, n);


    return 0;
}