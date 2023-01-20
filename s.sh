#!/bin/bash

mkdir -p build

cd src

gcc AVL_Order_Statistic_Tree.c -c
gcc Input_Handling.c -c
gcc Messages_Printing.c -c

gcc -g -std=c17 -O3 -Wall -Wextra -pedantic -Wshadow -Wformat=2 -Wfloat-equal -Wconversion -Wlogical-op -Wshift-overflow=2 -Wduplicated-cond -Wcast-qual -Wcast-align -fsanitize=address -fsanitize=undefined -fno-sanitize-recover -fstack-protector 'main.c' -o 'main' Input_Handling.o Messages_Printing.o AVL_Order_Statistic_Tree.o -lm

mv *.o ../build
mv main ../build

cd ..