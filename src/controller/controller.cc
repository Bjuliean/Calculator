#include "controller.h"

namespace s21 {

std::string Controller::CountExpression(std::string input_str) {
  return ck_.CalculateExpression(input_str);
}

std::string Controller::UnoOperation(std::string input_str) {
  return ck_.UnoPlusAndMinus(input_str);
}

std::string Controller::CountExpressionWithX(std::string input_str,
                                             double num) {
  return ck_.CalculateExpressionWithX(input_str, num);
}

};  // namespace s21