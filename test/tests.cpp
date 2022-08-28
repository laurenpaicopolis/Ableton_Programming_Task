#define CATCH_CONFIG_MAIN

#include "catch2/catch.hpp"
#include "../parse_input.h"
#include <vector>

TEST_CASE("Given test case") {
    std::vector<std::string> input_lines =  {"marker 0.0 0.0",
                                             "marker 4.0 2.0",
                                             "end_tempo 2.25",
                                             "b2s 2.0",
                                             "s2b 6.0"};
    std::vector<std::string> expected_output_lines = {"1.000000",
                                                      "13.000000"};
    REQUIRE(parse_input(input_lines) == expected_output_lines);
}

TEST_CASE("Decimal usage") {
    // Decimals
    std::vector<std::string> input_lines_1 = {"marker 0.0 0.0",
                                              "marker 4.0 2.0",
                                              "end_tempo 2.25",
                                              "b2s 2.0",
                                              "s2b 6.0"};
    std::vector<std::string> output_lines_1 = parse_input(input_lines_1);
    // No decimals
    std::vector<std::string> input_lines_2 = {"marker 0 0",
                                              "marker 4 2",
                                              "end_tempo 2.25",
                                              "b2s 2",
                                              "s2b 6"};
    std::vector<std::string> output_lines_2 = parse_input(input_lines_2);
    // Random mix
    std::vector<std::string> input_lines_3 = {"marker 0.0 0",
                                              "marker 4 2.0",
                                              "end_tempo 2.25",
                                              "b2s 2",
                                              "s2b 6.0"};
    std::vector<std::string> output_lines_3 = parse_input(input_lines_3);

    std::vector<std::string> expected_output_lines = {"1.000000",
                                                      "13.000000"};
    REQUIRE(output_lines_1 == expected_output_lines);
    REQUIRE(output_lines_2 == expected_output_lines);
    REQUIRE(output_lines_3 == expected_output_lines);
}

TEST_CASE("1 WM, shrinking b2s, Converting values before WM") {
    std::vector<std::string> input_lines = {"marker 0 2",
                                            "end_tempo 2",
                                            "b2s -1",
                                            "s2b 1"};
    std::vector<std::string> expected_output_lines = {"1.500000",
                                                      "-2.000000"};
    REQUIRE(parse_input(input_lines) == expected_output_lines);
}

TEST_CASE("1 WM, shrinking b2s, Converting values on WM") {
    std::vector<std::string> input_lines = {"marker 0 2",
                                            "end_tempo 2",
                                            "b2s 0",
                                            "s2b 2"};
    std::vector<std::string> expected_output_lines = {"2.000000",
                                                      "0.000000"};
    REQUIRE(parse_input(input_lines) == expected_output_lines);
}

TEST_CASE("1 WM, shrinking b2s, Converting values after WM") {
    std::vector<std::string> input_lines = {"marker 0 2",
                                             "end_tempo 2",
                                             "b2s 3",
                                             "s2b 6"};
    std::vector<std::string> expected_output_lines = {"3.500000",
                                                      "8.000000"};
    REQUIRE(parse_input(input_lines) == expected_output_lines);
}

TEST_CASE("2 WM, shrinking b2s, Converting values before first WM") {
    std::vector<std::string> input_lines = {"marker -2 1",  // tempo between = 3
                                             "marker 1 2",
                                             "end_tempo 2",
                                             "b2s -5",
                                             "s2b 0"};
    std::vector<std::string> expected_output_lines = {"0.000000",
                                                      "-5.000000"};
    REQUIRE(parse_input(input_lines) == expected_output_lines);
}

TEST_CASE("2 WM, shrinking b2s, Converting values on first WM") {
    std::vector<std::string> input_lines = {"marker -2 1",  // tempo between = 3
                                            "marker 1 2",
                                            "end_tempo 2",
                                            "b2s -2",
                                            "s2b 1"};
    std::vector<std::string> expected_output_lines = {"1.000000",
                                                      "-2.000000"};
    REQUIRE(parse_input(input_lines) == expected_output_lines);
}

TEST_CASE("2 WM, shrinking b2s, Converting values between WMs") {
    std::vector<std::string> input_lines = {"marker -2 1",  // tempo between = 3
                                            "marker 1 2",
                                            "end_tempo 2",
                                            "b2s 0",
                                            "s2b 1.5"};
    std::vector<std::string> expected_output_lines = {"1.666667",
                                                      "-0.500000"};
    REQUIRE(parse_input(input_lines) == expected_output_lines);
}

TEST_CASE("2 WM, shrinking b2s, Converting values on second WM") {
    std::vector<std::string> input_lines = {"marker -2 1",  // tempo between = 3
                                            "marker 1 2",
                                            "end_tempo 2",
                                            "b2s 1",
                                            "s2b 2"};
    std::vector<std::string> expected_output_lines = {"2.000000",
                                                      "1.000000"};
    REQUIRE(parse_input(input_lines) == expected_output_lines);
}

TEST_CASE("2 WM, shrinking b2s, Converting values after last WM") {
    std::vector<std::string> input_lines = {"marker -2 1",  // tempo between = 3
                                            "marker 1 2",
                                            "end_tempo 2",
                                            "b2s 0",
                                            "s2b 1.5"};
    std::vector<std::string> expected_output_lines = {"2.500000",
                                                      "3.000000"};
    REQUIRE(parse_input(input_lines) == expected_output_lines);
}

TEST_CASE("1 WM, stretching b2s, Converting values before WM") {
    std::vector<std::string> input_lines = {"marker 0 2",
                                            "end_tempo 0.5",
                                            "b2s -1",
                                            "s2b 1"};
    std::vector<std::string> expected_output_lines = {"0.000000",
                                                      "-0.500000"};
    REQUIRE(parse_input(input_lines) == expected_output_lines);
}

TEST_CASE("1 WM, stretching b2s, Converting values on WM") {
    std::vector<std::string> input_lines = {"marker 0 2",
                                            "end_tempo 0.5",
                                            "b2s 0",
                                            "s2b 2"};
    std::vector<std::string> expected_output_lines = {"2.000000",
                                                      "0.000000"};
    REQUIRE(parse_input(input_lines) == expected_output_lines);
}

TEST_CASE("1 WM, stretching b2s, Converting values after WM") {
    std::vector<std::string> input_lines = {"marker 0 2",
                                            "end_tempo 0.5",
                                            "b2s 3",
                                            "s2b 6"};
    std::vector<std::string> expected_output_lines = {"8.000000",
                                                      "2.000000"};
    REQUIRE(parse_input(input_lines) == expected_output_lines);
}

TEST_CASE("2 WM, stretching b2s, Converting values before first WM") {
    std::vector<std::string> input_lines = {"marker -2 4",  // tempo between = 0.25
                                            "marker -1 8",
                                            "end_tempo 0.5",
                                            "b2s -3",
                                            "s2b 2"};
    std::vector<std::string> expected_output_lines = {"0.000000",
                                                      "-2.500000"};
    REQUIRE(parse_input(input_lines) == expected_output_lines);
}

TEST_CASE("2 WM, stretching b2s, Converting values on first WM") {
    std::vector<std::string> input_lines = {"marker -2 4",  // tempo between = 0.25
                                            "marker -1 8",
                                            "end_tempo 0.5",
                                            "b2s -2",
                                            "s2b 4"};
    std::vector<std::string> expected_output_lines = {"4.000000",
                                                      "-2.000000"};
    REQUIRE(parse_input(input_lines) == expected_output_lines);
}

TEST_CASE("2 WM, stretching b2s, Converting values between WMs") {
    std::vector<std::string> input_lines = {"marker -2 4",  // tempo between = 0.25
                                            "marker -1 8",
                                            "end_tempo 0.5",
                                            "b2s -1.5",
                                            "s2b 5"};
    std::vector<std::string> expected_output_lines = {"6.000000",
                                                      "-1.750000"};
    REQUIRE(parse_input(input_lines) == expected_output_lines);
}

TEST_CASE("2 WM, stretching b2s, Converting values on second WM") {
    std::vector<std::string> input_lines = {"marker -2 4",  // tempo between = 0.25
                                            "marker -1 8",
                                            "end_tempo 0.5",
                                            "b2s -1",
                                            "s2b 8"};
    std::vector<std::string> expected_output_lines = {"8.000000",
                                                      "-1.000000"};
    REQUIRE(parse_input(input_lines) == expected_output_lines);
}

TEST_CASE("2 WM, stretching b2s, Converting values after last WM") {
    std::vector<std::string> input_lines = {"marker -2 4",  // tempo between = 0.25
                                            "marker -1 8",
                                            "end_tempo 0.5",
                                            "b2s -3",
                                            "s2b 2"};
    std::vector<std::string> expected_output_lines = {"12.000000",
                                                      "0.000000"};
    REQUIRE(parse_input(input_lines) == expected_output_lines);
}
