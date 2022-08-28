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
double WarpMarker::calculate_tempo_between_markers(WarpMarker *start_marker, WarpMarker *end_marker) {
    return (end_marker->beat_time - start_marker->beat_time)/(end_marker->sample_time - start_marker->sample_time);
}

/**
 * Gets the tempo at the given location
 * @param time user defined time
 * @param time_type True = beat time, False = sample time
 * @param warp_marker_list list of warp markers
 * @param end_tempo tempo after the last warp marker in case `time` comes after all warp markers
 * @return the tempo at the given time
 */
double WarpMarker::tempo_at(double time, bool time_type, std::vector<WarpMarker> &warp_marker_list, double end_tempo) {
    // Should not happen for valid command inputs
    if (warp_marker_list.empty()) {
        return 0.0;
    } // Now warp_marker_list length is >= 1

    // Get the warp markers around time
    WarpMarker *start_marker, *end_marker;
    std::tie(start_marker, end_marker) = locate_warp_markers(time,
                                                             time_type,
                                                             warp_marker_list);
    if (start_marker == nullptr) {
        // Have to get the tempo between first and second warp markers
        if (warp_marker_list.size() == 1)
            // Can't get tempo with 1 marker so use end_tempo
            return end_tempo;

        start_marker = &warp_marker_list.at(0);
        end_marker = &warp_marker_list.at(1);
        return calculate_tempo_between_markers(start_marker, end_marker);
    } else if (end_marker == nullptr) {
        return end_tempo;
    } else {
        return (end_marker->beat_time - start_marker->beat_time) / (end_marker->sample_time - start_marker->sample_time);
    }
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
    WarpMarker *start_marker, *end_marker;
    std::tie(start_marker, end_marker) = locate_warp_markers(beats,
                                                             true,
                                                             warp_marker_list);

    double tempo = tempo_at(beats, true, warp_marker_list, end_tempo);

    // Beats comes before all markers
    if (start_marker == nullptr)
        return end_marker->sample_time - (end_marker->beat_time - beats) * (1/tempo);

    return (beats - start_marker->beat_time) * (1/tempo) + start_marker->sample_time;
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
    // Locate and return the 2 warp markers the sample time is located between
    WarpMarker *start_marker, *end_marker;
    std::tie(start_marker, end_marker) = locate_warp_markers(seconds,
                                                             false,
                                                             warp_marker_list);

    double tempo = tempo_at(seconds, false, warp_marker_list, end_tempo);

    // Seconds comes before all markers
    if (start_marker == nullptr)
        return end_marker-> beat_time - (end_marker->sample_time - seconds) * (tempo);

    return (seconds - start_marker->sample_time) * tempo + start_marker->beat_time;
}

/**
 * Find the warp markers before and after the time to convert, or `nullptr` if there is not one.
 * If the time is on a warp marker, that warp marker is the "before" marker.
 *
 * @param time_to_convert time to convert (either beats or seconds)
 * @param time_type True = beat time, False = sample time
 * @param warp_marker_list list of warp markers
 * @return pointers to the two `WarpMarker`s that the time is between, or
 *         `nullptr` if `time_to_convert` is before/after all warp markers
 */
std::tuple<WarpMarker*, WarpMarker*> WarpMarker::locate_warp_markers(double time_to_convert,
                                                                     bool time_type,
                                                                     std::vector<WarpMarker> &warp_marker_list) {
    static WarpMarker *start_marker = nullptr;
    static WarpMarker *end_marker = nullptr;

    // No warp markers are given, start and end should be nullptr
    // Should never happen on valid input commands
    if (warp_marker_list.empty()) {
        return std::make_tuple(start_marker, end_marker);
    }

    // Time comes before first warp marker
    if ((time_type && warp_marker_list.front().beat_time > time_to_convert)
            || (!time_type && warp_marker_list.front().sample_time > time_to_convert)){
        // Start is nullptr, set end
        end_marker = &warp_marker_list.front();
        return std::make_tuple(start_marker, end_marker);
    }
    // Time comes after last warp marker
    else if ((time_type && warp_marker_list.back().beat_time <= time_to_convert)
            || (!time_type && warp_marker_list.back().sample_time <= time_to_convert)) {
        // Set start, end is nullptr
        start_marker = &warp_marker_list.back();
        return std::make_tuple(start_marker, end_marker);
    }

    // Iterates through warp marker list to find two warp markers time to convert is between
    for (int i = 0; i < warp_marker_list.size(); i++) {
        if (time_type) {  // b2s
            // Finds start and end warp marker surrounding seconds on timeline
            if (warp_marker_list.at(i).beat_time > time_to_convert) {
                start_marker = &warp_marker_list.at(i - 1);
                end_marker = &warp_marker_list.at(i);
                return std::make_tuple(start_marker, end_marker);
            }
        } else {  // s2b
            // Finds start and end warp marker surrounding seconds on timeline
            if (warp_marker_list.at(i).sample_time > time_to_convert) {
                start_marker = &warp_marker_list.at(i - 1);
                end_marker = &warp_marker_list.at(i);
                return std::make_tuple(start_marker, end_marker);
            }
        }
    }
    // Should never reach here
}