#ifndef CALCULATION_H
#define CALCULATION_H

#include "utils.h"

namespace s21 {
/*!
    \author Julieanb
    \brief Support class of the model.
         
    The class takes as input a parsed expression in the form of Polish notation and returns the result of its evaluation.
*/
class Calculator {
public:
    Calculator() = default;
    ~Calculator() = default;
    /*!
        \brief Main class method.

        The method iterates over the expression and performs the calculation using the stack.
    */
    std::string Calculate(std::string str);

private:
    /*! Used as storage for numbers coming from an expression. Used in several methods. */
    std::stack<std::string> stack_;
    /*!
        \brief The method that applies the current action.

        The method that applies the current action in the expression. 
        Due to pre-validation, it does not require special security.
    */
    void ApplyAction(std::string act);
    /*! Support method for Calculate. Applies a simple action. */
    void CalcAction(std::string act, double num);
    /*! Support method for Calculate. Applies a complex action. */
    void CalcFunction(std::string act);

}; // Calculator

}; // namespace s21

#endif // CALCULATION_H