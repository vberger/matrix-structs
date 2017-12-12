#!/bin/bash -ex

cmake -GNinja -DBUILD_TESTS=ON -H. -Bbuild -DCMAKE_BUILD_TYPE=Debug
cmake --build build

cd build && GTEST_COLOR=1 ctest --verbose
