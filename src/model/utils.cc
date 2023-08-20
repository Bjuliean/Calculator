#include "utils.h"

namespace s21 {

bool IsDigit(std::string str, size_t i) {
  return std::isdigit(str[i]) ||
         (str[i] == '.' && std::isdigit(str[i + 1]) &&
          std::isdigit(str[i - 1])) ||
         (str[i] == '-' && (i == 0 || str[i - 1] == '(' || str[i - 1] == ' ') &&
          (std::isdigit(str[i + 1]) || i == str.length() - 1));
}
int GetPriorityValue(std::string str) {
  int res = 0;
  if (str == "+") res = 2;
  if (str == "-") res = 2;
  if (str == "*" || str == "∙") res = 3;
  if (str == "/" || str == "÷") res = 3;
  if (str == "mod" || str == "%") res = 3;
  if (str == "^") res = 4;
  if (str == "cos") res = 5;
  if (str == "sin") res = 5;
  if (str == "tan" || str == "tg") res = 5;
  if (str == "acos") res = 5;
  if (str == "asin") res = 5;
  if (str == "atan" || str == "atg") res = 5;
  if (str == "sqrt" || str == "√") res = 5;
  if (str == "log" || str == "lg") res = 5;
  if (str == "ln") res = 5;
  if (str == "(") res = 1;
  if (str == ")") res = 1;
  return res;
}
bool IsSimpleAction(std::string str) {
  return GetPriorityValue(str) < 5 && GetPriorityValue(str) > 1;
}

};  // namespace s21