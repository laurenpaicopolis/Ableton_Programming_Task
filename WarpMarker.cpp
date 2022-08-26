//
// Created by Lauren Paicopolis on 8/22/22.
//

#include "WarpMarker.h"

// True is b2s
// False is s2b

double WarpMarker::calculate_conversion(double value_to_convert, std::vector<WarpMarker> &complete_structure, double end_tempo, bool conversion_type) {
    double final_conversion;
    int index = locate_warp_marker(value_to_convert, conversion_type, complete_structure);
    // Use end_time
    if (index == -1) {
        if (complete_structure.size() < 2) {
            // i d k
            if (conversion_type)
                // b2s
                final_conversion = value_to_convert * (1/end_tempo);
            else
                // s2b
                final_conversion = value_to_convert * end_tempo;
        }
        else {
            // If end_tempo and there is more than one warp marker is used and need to do either s2b or b2s
            WarpMarker last_warp_marker = complete_structure.back();
            if (conversion_type)
                // b2s
                final_conversion = last_warp_marker.sample_time + (value_to_convert - last_warp_marker.beat_time) * (1/end_tempo);
            else
                // s2b
                final_conversion = last_warp_marker.beat_time + (value_to_convert - last_warp_marker.sample_time) * end_tempo;
        }
    }
    else {
        WarpMarker end_warp_marker = complete_structure.at(index);
        WarpMarker start_warp_marker = complete_structure.at(index - 1);
        double between_beat_time = end_warp_marker.beat_time - start_warp_marker.beat_time;
        double between_sample_time = end_warp_marker.sample_time - start_warp_marker.sample_time;
        // b2s
        if (conversion_type) {
            double number_to_convert = value_to_convert - start_warp_marker.beat_time;
            final_conversion = number_to_convert * (between_sample_time/between_beat_time) + start_warp_marker.sample_time;
        }
        // s2b
        else {
            double number_to_convert = value_to_convert - start_warp_marker.sample_time;
            final_conversion = number_to_convert * (between_beat_time/between_sample_time) + start_warp_marker.beat_time;
        }
    }
    return final_conversion;
};


int WarpMarker::locate_warp_marker(double time_to_convert, bool time_type, std::vector<WarpMarker> &complete_structure) {

    if (complete_structure.size() == 1) {
        return -1;
    }
    for (int i = 0; i < complete_structure.size(); i++) {
        if (time_type) {
            if (complete_structure.at(i).beat_time >= time_to_convert) {
                return i;
            }
        }
        if (!time_type) {
            if (complete_structure.at(i).sample_time >= time_to_convert) {
                return i;
            }
        }
    }
 return -1;
}