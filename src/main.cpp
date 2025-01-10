#include <chrono>
#include <set>

#include "DetSkipLists.h"
#include "RandSkipLists.h"
#include "utils.h"

// Benchmark a single function
template <typename SkipListType, typename Func>
void benchmark(const std::string& label, SkipListType& skipList, Func func, int n) {
    auto start = std::chrono::high_resolution_clock::now();
    func(skipList); // Execute the function
    auto end = std::chrono::high_resolution_clock::now();
    double duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << label << " with n = " << n << ": " << duration << " us\n";
}

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

    // Create the random set

    int lower_bound = 1;
    int upper_bound = 1000000;
    std::set<int> S = createRandomSet(n, lower_bound, upper_bound);

    RandSkipLists RandSkipLists(S);
    //RandSkipLists.print();
    RandSkipLists.del(5);
    if(RandSkipLists.find(5)!=nullptr){
        throw std::runtime_error("Value 5 not found in the skip list.");
    }
    RandSkipLists.insert(5);
    //RandSkipLists.print();
    if(RandSkipLists.find(5)==nullptr){
        throw std::runtime_error("Value 5 not found in the skip list.");
    }


    benchmark("RandSkipList Find", RandSkipLists, [&](auto& list) {
        for (int i = 0; i < n; ++i) list.find(i);
    }, n);

    
    // RandSipLists.insert(5);
    

    //RandSipLists.findPredecessors(5);

    return 0;
}