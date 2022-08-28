#include "parse_input.h"
#include <vector>
#include <iostream>

/**
 * Collects all of user input and prints program output
 */
int main() {
    std::string input;
    std::vector<std::string> input_lines;

    while (true) {
        getline(std::cin, input);
        // Ends program if input is empty string
        if (input.empty())
            break;

        input_lines.push_back(input);
        input.clear();
    }

    std::vector<std::string> output_lines = parse_input(input_lines);
    for (std::string &s : output_lines) {
        std::cout << s << std::endl;
    }
    return 0;
}