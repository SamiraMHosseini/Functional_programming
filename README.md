# Functional Programming Concepts in C++

# Description:
Functional programming languages directly support programming with functions. This can include passing functions as arguments, returning them as results, and assigning them to variables. In this code, the filter function takes a function func as a parameter, which is an example of a higher-order function.
This repository contains a basic example of some functional programming concepts implemented in C++. The aim is to illustrate how C++, while primarily an object-oriented language, also supports functional programming styles.

# Details:
The main file demonstrates the use of higher-order functions, lambda expressions, and pure functions in C++. Specifically, it uses a filter function that accepts another function as its parameter and applies this function to each element in a vector of integers. The parameter function is defined as a lambda and checks whether a given integer is even. The filter function then uses this lambda to print all the even numbers from the vector.

Although C++ is not a purely functional language, this repository demonstrates that functional programming styles can indeed be effectively implemented in C++. It's a clear example of the multi-paradigm nature of the language.
