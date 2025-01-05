#include <set>

#include "DetSkipLists.h"
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
    int lower_bound = 1;
    int upper_bound = 100;
    std::set<int> S = createRandomSet(n, lower_bound, upper_bound);

    DetSkipLists detSkipLists(S);
    detSkipLists.print();
    bool result = detSkipLists.insert(5);
    detSkipLists.print();
    detSkipLists.insert(56);
    detSkipLists.print();
    detSkipLists.insert(6);
    detSkipLists.insert(7);
    // std::cout << "Inserted: "<< result << std::endl;
    detSkipLists.print();
    detSkipLists.del(7);
    detSkipLists.print();
    detSkipLists.del(56);
    detSkipLists.print();
    detSkipLists.del(6);
    detSkipLists.print();

    return 0;
}