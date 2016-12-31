#!/usr/bin/env bash

mkdir hardware-tests-build
cd hardware-tests-build

cmake -DGEN_TESTS=ON -DGEN_COVERAGE=ON ..
make

./tests/main_tests_hardware/2017-Vision-main-tests-hardware

lcov --directory . --capture --initial --output-file coverage.info #Capture all files as zero
lcov --remove coverage.info 'main/main.cpp' 'tests/*' '/usr/*' --output-file act_coverage.info #Remove main functions coverage, test functions coverage, and external functions coverage
lcov --list act_coverage.info #List our coverage
mkdir webReport
cd webReport
genhtml ../act_coverage.info #Generate an HTML report
cd ..
