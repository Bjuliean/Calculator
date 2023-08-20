#ifndef MODEL_H
#define MODEL_H

#include "polish_notation.h"
#include "calculation.h"
#include "validation.h"

namespace s21 {
/*!
    \author Julieanb
    \brief The base class of the model.
         
    Includes class objects that perform validation, polish notation, and calculation.
*/
class CountingKernel {
public:
    CountingKernel() = default;
    ~CountingKernel() = default;
    /*!
        \brief Calculates input expression.
        
        A method that allows you to evaluate an ordinary expression given as input.
        It is divided into several stages: validation, polish notation and calculation.
    */
    std::string CalculateExpression(std::string input_str);
    /*!
        \brief Calculates input expression with x.
        
        A method that allows you to substitute the value for x into the expression and calculate it. 
        Used to work with the graph of a function. After substituting the value, calls CalculateExpression.
    */
    std::string CalculateExpressionWithX(std::string input_str, double x);
    /*!
        Applies the unary minus or plus operation.
    */
    std::string UnoPlusAndMinus(std::string input_str);


private:
    /*! Calculator class object. Evaluates a parsed expression. */
    s21::Calculator calc_;
    /*! PolishNotation class object. Performs expression parsing. */
    s21::PolishNotation pn_;
    /*! Validator class object. Performs expression validation. */
    s21::Validator va_;

    /*!
        \brief Support function for UnoPlusAndMinus.
        
        Specifies the sign of a number.
    */
    bool IsLastNegative(std::string input_str);
    /*!
        \brief Support function for UnoPlusAndMinus.
        
        Converts sign to negative.
    */
    std::string TurnToNegative(std::string input_str);
    /*!
        \brief Support function for UnoPlusAndMinus.
        
        Converts sign to positive.
    */
    std::string TurnToPositive(std::string input_str);

}; // CountingKernel

}; // namespace s21

#endif // MODEL_H