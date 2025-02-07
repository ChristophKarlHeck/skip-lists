#include <iostream>
#include <set>
#include <fstream>  // For file operations
#include <cstdlib>  // For std::atoi
#include <string>
#include <tuple>  // For std::tuple

#include "DetSkipList.h"
#include "RandSkipLists.h"
#include "utils.h"

int main(int argc, char *argv[]) {
    // Ensure the user provides at least two arguments
    if (argc < 3 || argc > 4) {
        std::cerr << "Usage: " << argv[0] << " <number_of_elements> <number_of_rounds> [write_to_file:true/false]" << std::endl;
        return 1;
    }

    // Convert command-line arguments to integers and check for positive values
    int n = std::atoi(argv[1]);
    if (n <= 0) {
        std::cerr << "Error: The number of elements must be a positive integer." << std::endl;
        return 1;
    }

    int number_of_rounds = std::atoi(argv[2]);
    if (number_of_rounds <= 0) {
        std::cerr << "Error: The number of trials must be a positive integer." << std::endl;
        return 1;
    }

    // Determine if output should be written to a file
    bool write_to_file = (argc == 4 && std::string(argv[3]) == "true");

    std::ofstream configFile, detCsvFile, randCsvFile;

    if (write_to_file) {
        // Open the configuration file for storing n and log(n)
        configFile.open("config.csv");
        if (!configFile.is_open()) {
            std::cerr << "Error: Could not open config.csv for writing." << std::endl;
            return 1;
        }

        // Write n and log(n) only once
        configFile << "Log2N,N,Nlog2N,n²\n";
        configFile << std::log2(n) << "," << n << "," << n * std::log2(n) << "," << n*n << "\n";
        configFile.close();


        detCsvFile.open("det_analysis.csv");
        if (!detCsvFile.is_open()) {
            std::cerr << "Error: Could not open det_analysis.csv for writing." << std::endl;
            return 1;
        }
        detCsvFile << "Round,RunningTimeConstruction,RunningTimeFinding,RunningTimeDeleting,RunningTimeInserting,MaxHeight\n"; // CSV Header
    }
    std::cout << "DETERMINISTIC SKIPLIST" <<std::endl;
    for(int i = 0; i < number_of_rounds; i++){
        std::set<int> S = Utils::createRandomSet(n);
        int rand_element=Utils::getRandomElementInSet(S);
        // int rand_element;
        // if(i%2==0){
        //     rand_element=Utils::getRandomElementInSet(S);
        // } else{
        //     rand_element=Utils::getRandomElementNotInSet(S,n);
        // } 
        DetSkipList detSkipList(S);        
        auto [number_of_construction_steps, max_height] = detSkipList.construct();     // Construct the deterministic SkipList
        detSkipList.print();
        std::cout << "TASK: Find(" << rand_element << ")" <<std::endl;
        auto [number_of_finding_steps, node] = detSkipList.find(rand_element);     // Find
        detSkipList.print();
        std::cout << "TASK: Delete(" << rand_element << ")" <<std::endl;
        int number_of_deleting_steps = detSkipList.del(rand_element);              // Delete
        detSkipList.print();
        std::cout << "TASK: Insert(" << rand_element << ")" <<std::endl;
        int number_of_inserting_steps = detSkipList.insert(rand_element);          // Insert
        detSkipList.print();

        if (write_to_file) {
            detCsvFile << (i + 1) << ","
                    << number_of_construction_steps << ","
                    << number_of_finding_steps << ","
                    << number_of_deleting_steps << ","
                    << number_of_inserting_steps << ","
                    << max_height << "\n";
        }
    }

    if (write_to_file) {
        detCsvFile.close();
        std::cout << "Results saved to det_analysis.csv" << std::endl;

        randCsvFile.open("rand_analysis.csv");
        if (!randCsvFile.is_open()) {
            std::cerr << "Error: Could not open rand_analysis.csv for writing." << std::endl;
            return 1;
        }
        randCsvFile << "Round,RunningTimeConstruction,RunningTimeFinding,RunningTimeDeleting,RunningTimeInserting,MaxHeight\n"; // CSV Header
    }
    std::cout << "\nRANDOMIZED SKIPLIST" <<std::endl;
    for(int i = 0; i < number_of_rounds; i++){
        std::set<int> S = Utils::createRandomSet(n);
        int rand_element=Utils::getRandomElementInSet(S);
        // int rand_element;
        // if(i%2==0){
        //     rand_element=Utils::getRandomElementInSet(S);
        // } else{
        //     rand_element=Utils::getRandomElementNotInSet(S,n);
        // } 
        RandSkipList randSkipList(S);        
        auto [number_of_construction_steps, max_height] = randSkipList.construct();     // Construct the deterministic SkipList
        randSkipList.print();
        std::cout << "TASK: Find(" << rand_element << ")" <<std::endl;
        auto [number_of_finding_steps, node] = randSkipList.find(rand_element);     // Find
        randSkipList.print();
        std::cout << "TASK: Delete(" << rand_element << ")" <<std::endl;
        int number_of_deleting_steps = randSkipList.del(rand_element);              // Delete
        randSkipList.print();
        std::cout << "TASK: Insert(" << rand_element << ")" <<std::endl;
        int number_of_inserting_steps = randSkipList.insert(rand_element);          // Insert
        randSkipList.print();

        if (write_to_file) {
            randCsvFile << (i + 1) << ","
                    << number_of_construction_steps << ","
                    << number_of_finding_steps << ","
                    << number_of_deleting_steps << ","
                    << number_of_inserting_steps << ","
                    << max_height << "\n";
        }
    }

    if (write_to_file) {
        randCsvFile.close();
        std::cout << "Results saved to rand_analysis.csv" << std::endl;
    }

    return 0;
}