#include <vector>
#include <string>
#include "WarpMarker.h"

#ifndef ABLETON_PROGRAMMING_TASK_PARSE_INPUT_H
#define ABLETON_PROGRAMMING_TASK_PARSE_INPUT_H

std::vector<WarpMarker> insert_warp_marker(WarpMarker new_warp_marker, std::vector<WarpMarker> warp_marker_list);
std::vector<std::string> parse_input(std::vector<std::string> &commands);

#endif //ABLETON_PROGRAMMING_TASK_PARSE_INPUT_H
