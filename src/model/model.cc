#include "model.h"

namespace s21 {

std::string CountingKernel::CalculateExpression(std::string input_str) {
  if (input_str.empty()) return input_str;
  std::pair<std::string, bool> newstr = va_.ValidateExpression(input_str);
  if (newstr.second) newstr = pn_.TranslateNotation(newstr.first);
  return newstr.second ? calc_.Calculate(newstr.first) : newstr.first;
}

std::string CountingKernel::CalculateExpressionWithX(std::string input_str,
                                                     double x) {
  std::string newstr;
  if (x < 1e-7 && x > -1e-7) x = 0;
  for (size_t i = 0; i < input_str.length(); ++i) {
    if (input_str[i] == 'x')
      newstr.append("(" + std::to_string(x) + ")");
    else
      newstr.push_back(input_str[i]);
  }
  return CalculateExpression(newstr);
}

std::string CountingKernel::UnoPlusAndMinus(std::string input_str) {
  return IsLastNegative(input_str) ? TurnToPositive(input_str)
                                   : TurnToNegative(input_str);
}

std::string CountingKernel::TurnToNegative(std::string input_str) {
  if (!isdigit(input_str.back()) && !input_str.empty()) {
    if (input_str.back() == ')')
      input_str.append("*(-");
    else
      input_str.append("(-");
  } else if (input_str.empty()) {
    input_str.append("(-");
  } else {
    for (int32_t i = input_str.length() - 1; i >= 0; --i) {
      if (i == 0) {
        input_str.insert(i, "(-");
        break;
      }
      if (!IsDigit(input_str, i)) {
        input_str.insert(++i, "(-");
        break;
      }
    }
  }
  return input_str;
}

std::string CountingKernel::TurnToPositive(std::string input_str) {
  if (IsDigit(input_str, input_str.length() - 1) && input_str.back() == '-') {
    input_str.erase(input_str.end().operator--().operator--(), input_str.end());
  } else {
    if (input_str.back() == ')') input_str.pop_back();
    for (int32_t i = input_str.length() - 1; i >= 0; --i) {
      if (IsDigit(input_str, i) && input_str[i] == '-') {
        if (i == 0)
          input_str.erase(i, 1);
        else
          input_str.erase(--i, 2);
        break;
      }
    }
  }
  return input_str;
}

bool CountingKernel::IsLastNegative(std::string input_str) {
  bool res = false;
  for (int32_t i = input_str.length() - 1; i >= 0; --i) {
    if (!IsDigit(input_str, i)) break;
    if (IsDigit(input_str, i) && input_str[i] == '-') {
      res = true;
      break;
    }
  }
  return res;
}

};  // namespace s21