#!/bin/bash

g++ test.cpp -o 20 -std=c++20 && ./20 && rm -rf ./20
g++ test.cpp -o 17 -std=c++17 && ./17 && rm -rf ./17
g++ test.cpp -o 14 -std=c++14 && ./14 && rm -rf ./14
# g++ test.cpp -o 11 -std=c++11 && ./11 && rm -rf ./11
