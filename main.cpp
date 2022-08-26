#include <iostream>
#include <vector>
#include "WarpMarker.h"
#include <string>
#include <sstream>

/**
 * Locates where new warp marker should be inserted within existing warp marker list
 * @param new_warp_marker warp marker to be added
 * @param warp_marker_list complete list of warp markers
 * @return warp_marker_list
 */
std::vector<WarpMarker> insert_warp_marker(WarpMarker new_warp_marker, std::vector<WarpMarker> warp_marker_list) {

    // For timeline with multiple pre-existing warp markers
    for (int i = 0; i < warp_marker_list.size(); i++) {
        // Locates first warp marker with larger beat time than the new warp marker
        // and inserts new warp marker into timeline behind further warp marker
        if (warp_marker_list.at(i).beat_time > new_warp_marker.beat_time) {
            warp_marker_list.insert(warp_marker_list.begin() + i, new_warp_marker);
            return warp_marker_list;
        }
    }
    // For timeline w/ no warp markers, add first warp marker created
    warp_marker_list.push_back(new_warp_marker);
    return warp_marker_list;
}

/**
 * Starts program and collects user input:
 * marker <beat time> <sample time>
 * end_tempo <value>
 * s2b <sample time>
 * b2s <beat time>
 */
int main() {
    std::vector<WarpMarker> warp_marker_list;
    std::vector<std::string> user_input;
    double end_tempo;
    std::string input;
    std::string token;

    while (true) {
        getline(std::cin, input);
        // Ends program if input is empty string
        if (input.empty())
            break;

        std::stringstream X(input);
        // Tokenize input on space
        while (getline(X, token, ' '))
            user_input.push_back(token);

        // "marker" - create new warp marker and insert into beat/sample timelines
        if (user_input.at(0) == "marker") {
            WarpMarker new_marker{};
            new_marker.beat_time = std::stod(user_input.at(1));
            new_marker.sample_time = std::stod(user_input.at(2));
            warp_marker_list = insert_warp_marker(new_marker, warp_marker_list);
        }

        // "end_tempo" - assigns user defined end_tempo
        else if (user_input.at(0) == "end_tempo") {
            end_tempo = std::stod(user_input.at(1));
        }

        // "b2s" - converts user defined beats to seconds and print
        else if (user_input.at(0) == "b2s") {
            double final_conversion = WarpMarker::b2s(std::stod(user_input.at(1)), warp_marker_list, end_tempo);
            std::cout << final_conversion << std::endl;;
        }

        // "s2b" - converts user defined seconds to beats and print
        else if (user_input.at(0) == "s2b") {
            double final_conversion = WarpMarker::s2b(std::stod(user_input.at(1)), warp_marker_list, end_tempo);
            std::cout << final_conversion << std::endl;
        }
        user_input.clear();
        input.clear();
        token.clear();
    }
    return 0;
}
