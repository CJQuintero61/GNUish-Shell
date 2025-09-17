/*
    File: main.cpp
    Made By: Christian Quintero
    Last Updated: 09/16/2025

    This file is part of project 1 for Operating Systems (COSC-3346-001)

    This program implementes a simple shell that accepts user input and 
    runs some basic UNIX commands.
*/

#include <iostream>
using namespace std;


int main()
{
    // initialize variables
    string input_string = "";           // the keyboard input string
    const int tokens_length = 10;       // max number of tokens
    string tokens[tokens_length];       // array to hold the tokens

    // simple welcome message to know the program is running
    cout << "\n-----Welcome to the GNUish shell!-----\n" << endl;


    // main loop for the shell
    // uses an infinite loop that can be exited with the "exit" command
    do
    {
        cout << "Enter a UNIX command $ ";
        getline(cin, input_string);

        // check for exit command
        if(input_string == "exit")
        {
            cout << endl << "Exiting the GNUish shell. Goodbye!" << endl;
            break;
        }

        // simple code 
        cout << "You entered: " << input_string << endl << endl;




        // uses an infinite loop that can be exited with the "exit" command
    }   while (true);
    
    

    return 0;
} // end main