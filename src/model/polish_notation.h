#ifndef POLISH_NOTATION_H
#define POLISH_NOTATION_H

#include "utils.h"

namespace s21 {
/*!
    \author Julieanb
    \brief Support class of the model.
         
    It receives a validated expression as input and parses it into Polish notation.
*/
class PolishNotation {
public:
    PolishNotation() = default;
    ~PolishNotation() = default;
    /*!
        \brief Main class method.

        Returns the expression as Polish notation. 
        The algorithm uses 2 buffers - a stack and an output (output_str_), using a loop we go along the line, 
        meeting a number means that we have finished recording the action, 
        it can be checked and arranged depending on the priority of the action. 
        The meeting "not a number" means that we have finished recording the number.
    */
    std::pair<std::string, bool> TranslateNotation(std::string input_str_);

private:
    /*! Used as buffer output */
    std::string output_str_;
    /*! Used as buffer stack, temporary storage for actions */
    std::stack<std::string> stack_;
    /*! Support method for TranslateNotation */
    void PushToOutput();

}; // PolishNotation

}; // namespace s21

#endif // POLISH_NOTATION_H