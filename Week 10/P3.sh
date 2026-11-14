#!/bin/bash
# Problem 3: Write a shell script to demonstrate the use of variables

# Assigning string and integer variables (no spaces around = sign)
name="Sumit"
age=23
city="Aligarh"

# Printing variable values
echo "Name: $name"
echo "Age: $age"
echo "City: $city"

# String concatenation and variable interpolation
greeting="Hello, $name from $city"
echo "$greeting"
