/*
    File: Shell.h
    Made By: Christian Quintero
    Last Updated: 09/17/2025

    This file is the specification file for the Shell class.
    It defines the methods and attributes of the Shell class.
*/

#ifndef SHELL_H
#define SHELL_H

#include <iostream>
#include <string>
using namespace std;

class Shell
{
    /*
        Shell 

        This class specifies the methods and attributes of the Shell class.
    */
    private:
        static const int MAX_TOKENS = 10;                       // max number of tokens
        static const int MAX_HISTORY = 10;                      // max number of commands in history
        int tokens_count;                                       // current number of tokens
        bool input_flag;                                        // flag to indicate if input is valid
        string tokens[MAX_TOKENS];                              // array to hold the tokens
        string input_string;                                    // the keyboard input string
        string command_history[MAX_HISTORY];                    // array to hold command history


    
    public:
        Shell();                                         // constructor
        void run();                                      // runs the shell loop
        void get_input();                                // gets user input
        bool parse_input();                              // parses the input string into tokens and strores them in the tokens array
        void execute_command();                          // executes the command based on the tokens
        void history();                                  // prints the last 10 commands entered
        void add_to_history(const string& command);      // adds command to history queue
        void run_nth_command();                          // runs the nth command from history
        void print_tokens();                             // prints the tokens 

};

#endif // SHELL_H