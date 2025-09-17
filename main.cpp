/*
    File: main.cpp
    Made By: Christian Quintero
    Last Updated: 09/17/2025

    This file is part of project 1 for Operating Systems (COSC-3346-001)

    This program implementes a simple shell that accepts user input and 
    runs some basic UNIX commands.
*/
#include <iostream>
#include <cstring>
#include "Shell.h"
using namespace std;

int main()
{
    // create a shell object and run the shell loop
    Shell shell = Shell();
    shell.run();
    return 0;
} // end main