#!/bin/bash
set -e
set -x

rm -rf build
mkdir -p build
cd build && cmake .. -DCMAKE_BUILD_TYPE=Releas && cmake --build .

mv cerium/cerium ../cerium
