#!/bin/bash
# Problem 2: Write a shell script to accept user input and display it

# Prompt the user for input
echo "Enter your name:"

# The read command captures terminal input into variable 'name'
read name

# Display the variable value using $ prefix
echo "Hello, $name! Welcome."
