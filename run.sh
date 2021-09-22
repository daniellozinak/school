#!/bin/bash
echo "Compiling and executing $1";
g++ $1 -o main.out; ./main.out; rm main.out;
