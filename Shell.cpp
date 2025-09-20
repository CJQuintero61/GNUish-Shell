/*
    File: Shell.cpp
    Made By: Christian Quintero
    Last Updated: 09/20/2025

    This file is the implementation file for the Shell class.
    It runs the shell loop and handles user input.
*/

#include "Shell.h"
#include <iostream>
#include <sstream>
#include <unistd.h>    
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
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

        // get user input
        get_input();
        
        // parse the input into tokens
        // the input_flag marks if the input is valid or not
        // if too many tokens were entered, it will be false
        input_flag = parse_input();

        if(input_flag == false)
        {
            // if too many tokens were entered, restart the loop
            continue;
        }

        // early validations
        if(tokens[0] == "exit")
        {
            // if the user entered "exit", break the loop and end the program
            cout << "\n-----Exiting the GNUish shell. Goodbye!-----\n" << endl;
            break; 
        }
        else if(tokens[0] == "")
        {
            // if the user entered nothing, restart the loop
            continue; 
        }

        // run the desired command
        execute_command();
    

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

    cout << "\nEnter a UNIX command $ ";
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
            cout << "[ERROR]::Maximum number of tokens reached. Maximum tokens allowed: " << MAX_TOKENS << endl;
            return false;  
        }

        // store the token in the tokens array
        tokens[tokens_count] = token;
        tokens_count++;
    }

    return true;   
} // end parse_input

void Shell::execute_command()
{
    /*
        Shell::execute_command

        This method executes the command based on the tokens.
    */

    // create the command path
    string command_path = "/bin/";

    // add the first token (the command) to the command path
    if(tokens[0] != "")
    {
        // e.g. /bin/ls
        command_path += tokens[0]; 
    }
    else
    {
        return;
    }

    // create an array of char* to hold the arguments for execv
    char* args[MAX_TOKENS + 1]; // +1 for the NULL terminator

    for(int i = 0; i < tokens_count; i++)
    {
        // convert the strings in the tokens array to c-strings
        // then cast them to char* and store in args array
        args[i] = (char*)tokens[i].c_str();
    }

    // last argument must be NULL
    args[tokens_count] = NULL; 

    // create a child process
    int pid = fork();

    if(pid < 0)
    {
        cout << "[ERROR]::Fork failed!" << endl;
        return;
    }
    else if(pid == 0)
    {
        // in child process

        // convert the command path to a c-string
        // and pass the args array to execv
        // to execute the command
        execv(command_path.c_str(), args); 

        // if execv returns, it must have failed
        perror("Unknown command");
        exit(EXIT_FAILURE); // exit the child process
    }
    else
    {
        // in parent process

        // wait for the child process to finish
        int status;
        wait(&status); 
    }
    
} // end execute_command

void Shell::print_tokens()
{
    /*
        Shell::print_tokens

        This method prints the tokens stored in the tokens array.
    */

    for (int i = 0; i < tokens_count; i++)
    {
        cout << tokens[i] << endl;
    }

} // end print_tokens