#include <iostream>
#include <vector>
#include "WarpMarker.h"
#include <string>
#include <sstream>


// inserts warp marker into new spot in vector
// if warp marker is inserted in between two warps,
// change tempo of warps involved
std::vector<WarpMarker> insert_warp_marker(WarpMarker new_warp_marker, std::vector<WarpMarker> complete_structure) {
    for (int i = 0; i < complete_structure.size(); i++) {
        if (complete_structure.at(i).beat_time > new_warp_marker.beat_time) {
            complete_structure.insert(complete_structure.begin() + i, new_warp_marker);
            return complete_structure;
        }
    }
    complete_structure.push_back(new_warp_marker);
    return complete_structure;
}

int main() {
    std::vector<WarpMarker> complete_structure;
    std::vector<std::string> user_input;
    double end_tempo;
    // GET INPUT
    std::string input;
    std::string T;

    while (true) {
        getline(std::cin, input);
        if (input.empty())
            break;
        // X is an object of stringstream that references the S string
        std::stringstream X(input);
        // Use while loop to check the getline() function condition
        while (getline(X, T, ' '))
            user_input.push_back(T);
        if (user_input.at(0) == "marker") {
            WarpMarker new_marker{};
            new_marker.beat_time = std::stod(user_input.at(1));
            new_marker.sample_time = std::stod(user_input.at(2));
            complete_structure = insert_warp_marker(new_marker, complete_structure);
        }
        else if (user_input.at(0) == "end_tempo") {
            end_tempo = std::stod(user_input.at(1));
        }
        else if (user_input.at(0) == "b2s") {
            double final_conversion = WarpMarker::calculate_conversion(std::stod(user_input.at(1)), complete_structure, end_tempo, true);
            std::cout << final_conversion << std::endl;;
        }
        else if (user_input.at(0) == "s2b") {
            double final_conversion = WarpMarker::calculate_conversion(std::stod(user_input.at(1)), complete_structure, end_tempo, false);
            std::cout << final_conversion << std::endl;
        }
        user_input.clear();
        input.clear();
        T.clear();
    }
    return 0;
}
