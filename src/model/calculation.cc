#include "calculation.h"

namespace s21 {

std::string Calculator::Calculate(std::string str) {
  std::string val(""), act("");
  for (size_t i = 0; i < str.length(); ++i) {
    if (s21::GetPriorityValue(act) > 0) {
      ApplyAction(act);
      if (isalpha(stack_.top()[0])) break;
      act.clear();
    }
    if (s21::IsDigit(str, i)) {
      val.push_back(str[i]);
    }
    if (str[i] == ' ') {
      if (val.length() > 0) {
        stack_.push(val);
        val.clear();
      }
    }
    if (!s21::IsDigit(str, i) && str[i] != ' ') {
      act.push_back(str[i]);
    }
  }
  stack_.top().erase(stack_.top().find_last_not_of('0') + 1, std::string::npos);
  stack_.top().erase(stack_.top().find_last_not_of('.') + 1, std::string::npos);
  return stack_.top();
}

void Calculator::ApplyAction(std::string act) {
  if (GetPriorityValue(act) > 3)
    CalcFunction(act);
  else
    CalcAction(act, std::stod(stack_.top()));
}

void Calculator::CalcAction(std::string act, double num) {
  stack_.pop();
  double res = std::stod(stack_.top());
  if (act == "+") res += num;
  if (act == "-") res -= num;
  if (act == "*" || act == "∙") res *= num;
  if (act == "/" || act == "÷") {
    if (num == 0) {
      stack_.top() = "DIV BY ZERO";
      return;
    } else {
      res /= num;
    }
  }
  if (act == "mod" || act == "%") {
    if (num == 0) {
      stack_.top() = "DIV BY ZERO";
      return;
    } else {
      res = std::fmod(res, num);
    }
  }
  stack_.top() = std::to_string(res);
}

void Calculator::CalcFunction(std::string act) {
  double res = std::stod(stack_.top());
  if (act == "sin") res = sin(res);
  if (act == "cos") res = cos(res);
  if (act == "tan" || act == "tg") res = tan(res);
  if (act == "asin") {
    if (res > 1 || res < -1) {
      stack_.top().assign("ASIN ERROR: asin(" + stack_.top() + ")");
      return;
    }
    res = asin(res);
  }
  if (act == "acos") {
    if (res > 1 || res < -1) {
      stack_.top().assign("ACOS ERROR: acos(" + stack_.top() + ")");
      return;
    }
    res = acos(res);
  }
  if (act == "atan" || act == "atg") res = atan(res);
  if (act == "sqrt" || act == "√") {
    if (res < 0) {
      stack_.top().assign("SQRT ERROR: sqrt(" + stack_.top() + ")");
      return;
    }
    res = sqrt(res);
  }
  if (act == "ln") {
    if (res < 0) {
      stack_.top().assign("LN ERROR: ln(" + stack_.top() + ")");
      return;
    }
    res = log(res);
  }
  if (act == "log" || act == "lg") {
    if (res < 0) {
      stack_.top().assign("LOG ERROR: log(" + stack_.top() + ")");
      return;
    }
    res = log10(res);
  }
  if (act == "^") {
    stack_.pop();
    res = pow(std::stod(stack_.top()), res);
  }
  stack_.top() = std::to_string(res);
}

};  // namespace s21