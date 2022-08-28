# Ableton Programming Task

This program is for task #3, converting between beats and seconds using Warp Markers.
I ran and built the project inside CLion, and the testing suite used is Catch2.


[//]: # (This program recommends that the start of the beat track maps to 0 seconds on the )

[//]: # (sample track. For example, if the beat track starts with a pickup phrase of 2 beats,)

[//]: # (there should be a Warp Marker from -2.0 to 0.0. If the beat track has no pickup phrase,)

[//]: # (then there should be a Warp Marker from 0.0 to 0.0. Therefore, there always should be a)

[//]: # (Warp Marker from a non-positive beat time to 0.0 seconds in sample time. This prevents)

[//]: # (any output of `b2s` or `s2b` from being negative.)