#!/usr/bin/env bash

lcov --directory . --capture --initial --output-file zero_coverage.info #Capture all files as zero
lcov --directory . --capture --output-file imp_coverage.info #Capture implemented coverage
lcov --add-tracefile zero_coverage.info --add-tracefile imp_coverage.info --output-file all_coverage.info #Merge the files to get all coverage
lcov --remove all_coverage.info 'main/main.cpp' 'tests/*' '/usr/*' --output-file act_coverage.info #Remove main functions coverage, test functions coverage, and external functions coverage
lcov --list act_coverage.info #List our coverage
mkdir webReport
cd webReport
genhtml ../act_coverage.info #Generate an HTML report
cd ..
