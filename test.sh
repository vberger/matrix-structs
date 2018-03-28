#!/bin/bash -ex

cmake -GNinja -H. -Bbuild \
    -DBUILD_TESTS=ON \
    -DCMAKE_BUILD_TYPE=Debug \
    -DBUILD_SHARED_LIBS=1
cmake --build build
cmake --build build --target install

cd build && GTEST_COLOR=1 ctest --verbose
