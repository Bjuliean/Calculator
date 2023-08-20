#ifndef VALIDATION_H
#define VALIDATION_H

#include "utils.h"

namespace s21 {
/*!
    \author Julieanb
    \brief Support class of the model.
         
    It receives a validated expression as input and parses it into Polish notation.
*/
class Validator {
public:
    Validator() = default;
    ~Validator() = default;
    /*!
        \brief Main class method.

        Validates the expression received at the input, if possible, corrects the syntax on its own. 
        Returns a string/bool pair. If the expression is correct or corrected, 
        the expression and true will be returned. Otherwise, the error text and false will be returned.
    */
    std::pair<std::string, bool> ValidateExpression(std::string str);

private:
    /*!
        \brief Self-correction method.

       For the subsequent correctness of work with the expression, it is required to remove the spaces.
    */
    std::string DeleteSpaces(std::string str);
    /*!
        \brief Self-correction method.

        For the subsequent correctness of work with the expression, it is required to use dots.
    */
    std::string ChangeCommaToPoint(std::string str);
    /*!
        \brief Self-correction method.

        In expressions like "2x" or "(2+3)(3+2)", i.e. where the multiplication sign is implied, substitute it.
    */
    std::string AddMultSign(std::string str);
    /*!
        \brief Self-correction method.

        For convenient subsequent work with the expression, 
        replaces - multiplication by -1 in specific places, in expressions like "(-(3+3)+(2+2))".
    */
    std::string TransformNegateSign(std::string str);
    /*! Checks for correctness of record of operations concerning numbers. */
    bool IsOkActionRecord(std::string str);
    /*! Checks for placement of brackets. */
    bool CheckForBrackets(std::string str);
    /*! Checks for placement of points. */
    bool CheckForPoints(std::string str);
    /*! A method that executes existing validation methods. */
    bool CheckPackage(std::string str);

};

}; // namespace s21

#endif // VALIDATION_H