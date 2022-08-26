//
// Created by Lauren Paicopolis on 8/22/22.
//

#include "WarpMarker.h"

/**
 * Calculates tempo between two warp markers:
 * tempo = End marker beat time - Start marker beat time / End marker beat time - Start marker beat time
 *
 * @param start_and_end_markers list of two warp markers surrounding the value to be converted
 * @return the tempo between the two warp markers
 */
double WarpMarker::calculate_tempo_between_markers(WarpMarker **start_and_end_markers) {
    return (start_and_end_markers[1]->beat_time - start_and_end_markers[0]->beat_time)/(start_and_end_markers[1]->sample_time - start_and_end_markers[0]->sample_time);
}

/**
 * Converts beats to seconds within beat/sample warp timeline
 *
 * @param beats user defined beats
 * @param warp_marker_list list of warp markers
 * @param end_tempo user defined end tempo
 * @return conversion of beats to seconds
 */
double WarpMarker::b2s(double beats, std::vector<WarpMarker> &warp_marker_list, double end_tempo) {
    // Locate what two warp markers the beat time is located between and return them
    static WarpMarker **start_and_end_markers = locate_warp_marker(beats, true,warp_marker_list);

    // Only one warp marker in timeline, so just
    // use end_tempo to convert
    if (start_and_end_markers[0] == nullptr)
        return beats * (1/end_tempo);

    // Beat is after last warp marker and there are
    // multiple warp markers in timeline, so use end tempo
    // and last warp marker to convert
    if (start_and_end_markers[1] == nullptr)
        return start_and_end_markers[0]->sample_time + (beats - start_and_end_markers[0]->beat_time) * (1/end_tempo);

    // Calculate tempo between two warp markers beat is in between
    double tempo = calculate_tempo_between_markers(start_and_end_markers);

    // Calculate beat to seconds
    return (beats - start_and_end_markers[0]->beat_time) * (1/tempo) + start_and_end_markers[0]->sample_time;
}

/**
 * Converts seconds to beats within beat/sample warp timeline
 *
 * @param seconds user defined seconds
 * @param warp_marker_list list of warp markers
 * @param end_tempo user defined end tempo
 * @return conversion of seconds to beats
 */
double WarpMarker::s2b(double seconds, std::vector<WarpMarker> &warp_marker_list, double end_tempo) {
    // Locate what two warp markers the sample time is located between and return them
    static WarpMarker **start_and_end_markers = locate_warp_marker(seconds, false,warp_marker_list);

    // Only one warp marker in timeline, so just
    // use end_tempo to convert
    if (start_and_end_markers[0] == nullptr)
        return seconds * end_tempo;

    // Beat is after last warp marker and there are
    // multiple warp markers in timeline, so use end tempo
    // and last warp marker to convert
    if (start_and_end_markers[1] == nullptr)
        return start_and_end_markers[0]->beat_time + (seconds - start_and_end_markers[0]->sample_time) * end_tempo;

    // Calculate tempo between two warp markers seconds is in between
    double tempo = calculate_tempo_between_markers(start_and_end_markers);

    // Calculate seconds to beats
    return (seconds - start_and_end_markers[0]->sample_time) * (tempo) + start_and_end_markers[0]->beat_time;
}

/**
 * Find what warp markers the time to convert is between
 *
 * @param time_to_convert user defined time to convert
 * @param time_type either True for beat time to convert or False for sample time to convert
 * @param warp_marker_list list of warp markers
 * @return list of two warp markers the time is between
 */
WarpMarker** WarpMarker::locate_warp_marker(double time_to_convert, bool time_type, std::vector<WarpMarker> &warp_marker_list) {
    WarpMarker end_warp_marker {};
    WarpMarker start_warp_marker {};
    static WarpMarker *start_and_end_markers[2] = {&start_warp_marker, &end_warp_marker};

    // If there is only one warp marker, assign null
    // This signals to only use end tempo for conversion
    if (warp_marker_list.size() == 1) {
        start_and_end_markers[0] = nullptr;
        return start_and_end_markers;
    }

    // Iterates through warp marker list to find two warp markers time to convert is between
    for (int i = 0; i < warp_marker_list.size(); i++) {

        // True: Use beat time to find where beat is within timeline
        if (time_type) {
            // Finds start and end warp marker surrounding seconds on timeline
            if (warp_marker_list.at(i).beat_time >= time_to_convert) {
                start_and_end_markers[1] = &warp_marker_list.at(i); // End warp marker
                start_and_end_markers[0] = &warp_marker_list.at(i - 1); // Start warp marker
                return start_and_end_markers;
            }
        }

        // False: Use sample time to find where seconds are within timeline
        else {
            // Finds start and end warp marker surrounding seconds on timeline
            if (warp_marker_list.at(i).sample_time >= time_to_convert) {
                start_and_end_markers[1] = &warp_marker_list.at(i); // End warp marker
                start_and_end_markers[0] = &warp_marker_list.at(i - 1); // Start warp marker
                return start_and_end_markers;
            }
        }
    }

    // If time to convert is after all warp markers, assign last warp marker and null
    // This signals to use last warp marker and end tempo for conversion
    start_and_end_markers[0] = &warp_marker_list.at(warp_marker_list.size() - 1);
    start_and_end_markers[1] = nullptr;
    return start_and_end_markers;
}