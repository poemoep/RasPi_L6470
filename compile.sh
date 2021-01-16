#!/bin/bash
clear
gcc -o test L6470.c main.c -z muldefs -I /usr/local/include/ -L /usr/local/lib/ -l wiringPi -lm

