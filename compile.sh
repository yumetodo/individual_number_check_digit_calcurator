#!/bin/sh
em++ -std=c++17 -O2 -s DISABLE_EXCEPTION_CATCHING=0 --bind -o index.js index.cpp