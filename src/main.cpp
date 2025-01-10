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

    // Create the random set

    for(int i = 0; i < 10; i++){
        int lower_bound = 1;
        int upper_bound = 20;
        std::set<int> S = createRandomSet(n, lower_bound, upper_bound);

        RandSkipLists RandSkipLists(S);
        RandSkipLists.find(5);
        RandSkipLists.print();
        RandSkipLists.del(5);
        RandSkipLists.print();
        RandSkipLists.insert(5);
        RandSkipLists.print();
        std::cout << "New:\n" << std::endl;
    }
    
    
    // RandSipLists.insert(5);
    

    //RandSipLists.findPredecessors(5);

    return 0;
}