#/bin/bash

g++ -std=c++17 -O2 -Wall $1.cpp -o main

./main < in.txt > out.txt

cat out.txt