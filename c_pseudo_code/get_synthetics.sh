#!/bin/sh


echo ""
echo "How long does it take to generate 50,000 sets of synthetics in C++?"


echo ""
echo "Using -O1 optimization:"
g++ -O1 get_synthetics.cpp
./a.out


echo ""
echo "Using -O2 optimization:"
g++ -O2 get_synthetics.cpp
./a.out


echo ""
echo "Using -O3 optimization:"
g++ -O3 get_synthetics.cpp
./a.out


echo ""
