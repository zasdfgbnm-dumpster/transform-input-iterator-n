#!/bin/bash

nvcc test.cu -o 14 -std=c++14 && ./14 && rm -rf ./14
nvcc test.cu -o 17 -std=c++17 && ./17 && rm -rf ./17
