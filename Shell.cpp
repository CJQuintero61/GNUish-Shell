/*
    File: Shell.cpp
    Made By: Christian Quintero
    Last Updated: 09/17/2025

    This file is the implementation file for the Shell class.
    It runs the shell loop and handles user input.
*/

#include "Shell.h"
#include <iostream>
#include <sstream>
using namespace std;

Shell::Shell()
{
    /*
        Shell::Shell

        This is the constructor for the Shell class.
        It initializes the private attributes.
    */

    tokens_count = 0;
    input_string = "";
    input_flag = true;
    
    // initialize the tokens array to empty strings
    for (int i = 0; i < MAX_TOKENS; i++)
    {
        tokens[i] = "";                 
    }

} // end constructor

void Shell::run()
{
    /*
        Shell::run

        This method runs the main shell loop.
        It gets user input, parses it, and executes the command.
    */

    cout << "\n-----Welcome to the GNUish shell!-----\n" << endl;

    // infinite loop to run the shell
    do
    {

        // reset the variables for each loop iteration
        tokens_count = 0;
        input_string = "";
        input_flag = true;
        for (int i = 0; i < MAX_TOKENS; i++)
        { 
            tokens[i] = "";
        }              


        get_input();

        // match the input case
        if (input_string == "exit")
        {
            cout << "-----Exiting the GNUish shell. Goodbye!-----" << endl;
            break;
        }
        else if (input_string == "")
        {
            // for an empty input, restart the loop
            continue;
        }
        else
        {
            input_flag = parse_input();

            if(input_flag == false)
            {
                // if too many tokens were entered, restart the loop
                continue;
            }

            // run the desired command
            //execute_command();
        }

    } while (true);
    
    // after breaking from the loop, this method will return to main
    // where the program will end

} // end run

void Shell::get_input()
{
    /*
        Shell::get_input

        This method gets user input from the keyboard.
    */
    
    string str = "";        

    cout << "Enter a UNIX command $ ";
    getline(cin, str);

    input_string = str;

} // end get_input

bool Shell::parse_input()
{
    /*
        Shell::parse_input

        Returns: bool - a flag indicating if the input was valid or not
            true - input was valid
            false - input was invalid (too many tokens)

        This method parses the input string into tokens.
        It splits the input string by spaces and stores the tokens in the tokens array.
    */

    // use a stringstream to parse the input string
    stringstream ss(input_string);
    string token;

    // get each token from the input string
    while (ss >> token)
    {
        // if we have reached the max number of tokens, break
        if (tokens_count >= MAX_TOKENS)
        {
            cout << "[ERROR]: Maximum number of tokens reached. Maximum tokens allowed: " << MAX_TOKENS << endl;
            return false;  
        }

        // store the token in the tokens array
        tokens[tokens_count] = token;
        tokens_count++;
    }

    return true;   
} // end parse_input