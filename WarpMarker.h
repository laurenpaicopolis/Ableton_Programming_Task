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

        static double calculate_tempo_between_markers(WarpMarker **start_and_end_markers);
        static WarpMarker** locate_warp_marker(double time_to_convert, bool conversion_type, std::vector<WarpMarker> &warp_marker_list);
        static double b2s(double beats, std::vector<WarpMarker> &warp_marker_list, double end_tempo);
        static double s2b(double seconds, std::vector<WarpMarker> &warp_marker_list, double end_tempo);
};


#endif //ABLETON_PROGRAMMING_TASK_WARPMARKER_H
