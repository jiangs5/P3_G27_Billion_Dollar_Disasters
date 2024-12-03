#include "Trie.h"
#include "Map.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

int main() { 
    
    //County input validation
    string countyName;
    bool validInput = false;

    while (!validInput) {
        std::cout << "Please enter county name: ";
        std::getline(std::cin, countyName);

        validInput = true;

        //Check if the string is empty
        if (countyName.empty()) {
            std::cout << "Error: Input cannot be empty.\n";
            validInput = false;
        }

        // Check if the string contains only letters and spaces
        for (char c : countyName) {
            if (!std::isalpha(c) && !std::isspace(c)) {
                std::cout << "Error: county name should only contain letters and spaces.\n";
                validInput = false;
                break;
            }
        }

        std::cout << "County name is valid: " << countyName << std::endl;
    }

    //Using Map data structure
    

    //Using Trie data structure
    
    return 0; 
}



