#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../model/model.h"

namespace s21 {
/*!
    \author Julieanb
    \brief The base class of the controller.
         
    Redirects requests from view to model and returns the result from model to view.
*/
class Controller {
public:
    Controller() : ck_() {}
    /*!
        \brief Calculates input expression.
        
        A method that allows you to evaluate an ordinary expression given as input.
        It is divided into several stages: validation, polish notation and calculation.
    */
    std::string CountExpression(std::string input_str);
    /*!
        Applies the unary minus or plus operation.
    */
    std::string UnoOperation(std::string input_str);
    /*!
        \brief Calculates input expression with x.
        
        A method that allows you to substitute the value for x into the expression and calculate it. 
        Used to work with the graph of a function. After substituting the value, calls CalculateExpression.
    */
    std::string CountExpressionWithX(std::string input_str, double num);

private:
    /*! An object of the model's base class. */
    s21::CountingKernel ck_;
};

}; // namespace s21

#endif // CONTROLLER_H