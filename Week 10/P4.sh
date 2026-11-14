#!/bin/bash
# Problem 4: Write a shell script to perform basic arithmetic operations

echo "Enter first number:"
read a

echo "Enter second number:"
read b

# Arithmetic expansion using $(( ... )) syntax
sum=$((a + b))
diff=$((a - b))
prod=$((a * b))
div=$((a / b))
mod=$((a % b))

echo "Addition: $sum"
echo "Subtraction: $diff"
echo "Multiplication: $prod"
echo "Division: $div"
echo "Modulus: $mod"
