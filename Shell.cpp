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
#include <limits.h>    // for PATH_MAX
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

    // initialize the command history array to empty strings
    for (int i = 0; i < MAX_HISTORY; i++)
    {
        command_history[i] = "";
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
        getcwd(cwd, PATH_MAX);                         // get the current working directory

        // reset the tokens array to empty strings
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
            // if too many tokens were entered
            // add to history then restart the loop
            add_to_history(input_string);
            continue;
        }

        // match the first token case
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
        else if(tokens[0] == "history" || tokens[0] == "hist")
        {
            // add the history command to the history
            add_to_history(input_string); 

            // print the command history
            // then reset the loop
            history();
            continue; 
        }
        else if(tokens[0] == "r")
        {
            // changes the tokens to the nth command from history
            run_nth_command(); 
            continue;
        }

        // add to history
        add_to_history(input_string);

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

    // get the current working directory
    // returns null on failure, cwd contains a pointer to the buffer on success
    if (getcwd(cwd, PATH_MAX) != NULL)
    {
        cout << "\n" << cwd <<" $ ";
    }     
    else
    {   
        // default prompt if getcwd fails
        cout << "\nEnter a UNIX command $ ";
    }

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
        // wait for the child process to finish
        int status;
        wait(&status); 
    }
    
} // end execute_command

void Shell::history()
{
    /*
        Shell::history

        This method prints the last 10 commands entered with the most recent command last.
        This means the queue prints from last to first
    */

    // count the current number of commands in history
    int command_count = 0;
    for (int i = 0; i < MAX_HISTORY; i++)
    {
        if (command_history[i] != "")
        {
            command_count++;
        }
    }

    cout << "\n-----Command History (most recent command last)-----\n" << endl;
    for (int i = command_count - 1; i >= 0; i--)
    {
        if (i == command_count - 1)
        {
            // oldest command
            cout << "[" << i + 1 << "] (oldest): " << command_history[i] << endl;
            continue;
        }
        else if(i == 0)
        {
            // newest command
            cout << "[" << i + 1 << "] (newest): " << command_history[i] << endl;
            continue;
        }
        else
        {
            // middle commands
            cout << "[" << i + 1 << "]: " << command_history[i] << endl;
        }

    }

    cout << "\n----------------------------------------------------\n" << endl;

} // end history

void Shell::add_to_history(const string& command)
{
    /*
        Shell::add_to_history

        params:
            command: string - the command to add to history

        This method adds a command to the history queue.
    */

    // shift all commands in the queue to the right
    for (int i = MAX_HISTORY - 1; i > 0; i--)
    {
        command_history[i] = command_history[i - 1];
    }

    // add the new command to the front of the queue
    command_history[0] = command;

} // end add_to_history

void Shell::run_nth_command()
{
    /*
        Shell::run_nth_command

        This method reruns the nth command from history.
        If no parameter is given, it reruns the most recent command.

        NOTE:: n == 0 is the same as n == 1, they will both run the most recent command.
        This is because entering "r" is the same as enterring "r 1"
    */

    int n = 0; // the command number to run

    try 
    {
        n = stoi(tokens[1]); // convert the second token to an integer
    }
    catch (exception& e) 
    {
        // if conversion fails, rerun the most recent command
        n = 0; 
    }

    // Reset tokens
    for (int i = 0; i < MAX_TOKENS; i++)
    {
        tokens[i] = "";
    }
    tokens_count = 0;

    // validate n, must be between 1 and MAX_HISTORY
    if (n >= 1 && n <= MAX_HISTORY)
    {
        input_string = command_history[n - 1]; // get the nth command from history
    }
    else if (n == 0)
    {
        // get the most recent command
        // same as entering "r 1"
        input_string = command_history[0]; 
    }
    else
    {
        cout << "[ERROR]::Command number out of range. Please enter a number between 1 and " << MAX_HISTORY << "." << endl;
        return;
    }

    // validate that the command exists
    if (input_string == "")
    {
        cout << "[ERROR]::No command found in history for the given number." << endl;
        return;
    }

    // Re-parse as if user typed it
    bool input_flag = parse_input();
    if (input_flag == false) 
    {
        cout << "[ERROR]::The command in history has too many tokens. Cannot execute." << endl;

        // the command that gets re-executed, even if it has too many params, 
        // gets added to history again
        add_to_history(input_string); 
        return;
    }

    // notify the user which command is being run
    cout << "\nRe-running command: " << input_string << endl;
    
    // if the command is "history" or "hist", just print the history again
    if (tokens[0] == "history" || tokens[0] == "hist")
    {
        add_to_history(input_string);
        history();
        return;
    }

    // Add this command to history
    add_to_history(input_string);

    // Execute the command
    execute_command();
}

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