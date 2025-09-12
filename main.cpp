/*
    File: main.cpp
    Made By: Christian Quintero
    Last Updated: 09/12/2025

    This file is part of project 1 for Operating Systems (COSC-3346-001)

    This program implementes a simple shell that accepts user input and 
    runs some basic UNIX commands.
*/

#include <iostream>
using namespace std;


int main()
{
    // initialize variables
    string keyboard_input = "";

    // simple welcome message to know the program is running
    cout << "Welcome to the GNUish shell!" << endl << endl;


    // main loop for the shell
    // uses an infinite loop that can be exited with the "exit" command
    do
    {
        cout << "Enter a UNIX command: ";
        getline(cin, keyboard_input);

        // check for exit command
        if(keyboard_input == "exit")
        {
            cout << endl << "Exiting the GNUish shell. Goodbye!" << endl;
            break;
        }

        // simple code 
        cout << "You entered: " << keyboard_input << endl << endl;




        // uses an infinite loop that can be exited with the "exit" command
    }   while (true);
    
    

    return 0;
} // end main