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
using namespace std;


int main()
{
    // initialize variables
    string input_string = "";           // the keyboard input string
    const int MAX_TOKENS = 10;       // max number of tokens
    int tokens_count = 0;               // current number of tokens
    string tokens[MAX_TOKENS];       // array to hold the tokens

    // simple welcome message to know the program is running
    cout << "\n-----Welcome to the GNUish shell!-----\n" << endl;

    // main loop for the shell
    // uses an infinite loop that can be exited with the "exit" command
    do
    {
        // clear the variables
        input_string = "";          
        tokens_count = 0;

        // clear the tokens array
        for (int i = 0; i < MAX_TOKENS; i++)
        {
            tokens[i] = "";                 
        }

        // get user input
        cout << "Enter a UNIX command $ ";
        getline(cin, input_string);

        // check for exit command
        if(input_string == "exit")
        {
            cout << endl << "-----Exiting the GNUish shell. Goodbye!-----" << endl;
            break;
        }
        else if (input_string.empty())
        {
            // continue the do-while loop if no input was given
            continue;
        }
 
        // convert input string to c-string
        char* input_cstring = new char[input_string.length() + 1];  // +1 for null terminator

        // copy the string to the c-string pointer
        strcpy(input_cstring, input_string.c_str());

        // tokenize the input string
        char* cstring_token = strtok(input_cstring, " \t\n");       // tokenize by space, tab, or newline

        while (cstring_token != nullptr && tokens_count < MAX_TOKENS)
        {
            tokens[tokens_count] = string(cstring_token);               // convert c-string token to string and store in array
            tokens_count++;                                             // increment token count
            cstring_token = strtok(nullptr, " \t\n");                   // get the next token
        }

        // check if there are too many tokens
        if (cstring_token != nullptr)
        {
            cout << "[ERROR]::Too many tokens entered. Maximum tokens allowed: " << MAX_TOKENS << endl;
            delete [] input_cstring;            // free the allocated memory
            input_cstring = nullptr;            // avoid dangling pointer
            continue;                           // restart the loop
        }

        delete [] input_cstring;            // free the allocated memory
        input_cstring = nullptr;            // avoid dangling pointer

        // print the tokens 
        for(int i = 0; i < tokens_count; i++)
        {
            cout << tokens[i] << endl;
        }

    }   while (true);
    
    

    return 0;
} // end main