#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <stack>
#include <cmath>

/*!
    \file
    \brief Support functions.

    Support functions pack, using by several classes.
*/

namespace s21 {

/*!
    Returns the priority value based on the received action. 
    If the action does not exist, then 0 will be returned.
*/
int GetPriorityValue(std::string str);
/*! 
    Determines if the character in the string at index i is a number. 
    Dot and minus in certain circumstances are also included in the number.
*/
bool IsDigit(std::string str, size_t i);
/*!
    Checking if the action is simple. In this case, these are single-character actions and mod.
*/
bool IsSimpleAction(std::string str);

}; // namespace s21

#endif // UTILS_H