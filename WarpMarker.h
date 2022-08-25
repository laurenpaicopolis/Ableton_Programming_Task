//
// Created by Lauren Paicopolis on 8/22/22.
//

#ifndef ABLETON_PROGRAMMING_TASK_WARPMARKER_H
#define ABLETON_PROGRAMMING_TASK_WARPMARKER_H

#include <vector>

class WarpMarker {
    public:
        double sample_time;
        double beat_time;

        static double calculate_conversion(double b2s, std::vector<WarpMarker> &complete_structure, double end_tempo, bool conversion_type);
        static int locate_warp_marker(double time_to_convert, bool conversion_type, std::vector<WarpMarker> &complete_structure);
};


#endif //ABLETON_PROGRAMMING_TASK_WARPMARKER_H
