#include "polish_notation.h"

namespace s21 {

std::pair<std::string, bool> PolishNotation::TranslateNotation(
    std::string input_str_) {
  output_str_.clear();
  bool correct_expr = true;
  std::string act("");
  stack_.push(act);
  for (size_t i = 0; i < input_str_.length(); ++i) {
    if (s21::IsDigit(input_str_, i)) {
      if (!act.empty()) {
        output_str_ = "UNKNOWN ACTION: " + act;
        correct_expr = false;
        act.clear();
        while (stack_.size() > 0) stack_.pop();
        break;
      }
      output_str_.push_back(input_str_[i]);
    } else {
      act.push_back(input_str_[i]);
      if (s21::GetPriorityValue(act) > 0) {
        if (act == "(") {
          stack_.push(act);
          act.clear();
        } else if (act == ")") {
          while (stack_.top() != "(") {
            PushToOutput();
          }
          stack_.pop();
          act.clear();
        } else {
          while (s21::GetPriorityValue(act) <=
                 s21::GetPriorityValue(stack_.top())) {
            if (s21::GetPriorityValue(act) == 4 &&
                s21::GetPriorityValue(stack_.top()) == 4)
              break;
            PushToOutput();
          }
          stack_.push(act);
          act.clear();
        }
      }
      if (output_str_.back() != ' ' && output_str_.size() > 0)
        output_str_.push_back(' ');
    }
  }
  if (!act.empty()) {
    output_str_ = "UNKNOWN ACTION: " + act;
    correct_expr = false;
  }
  while (stack_.size() > 0) PushToOutput();
  return std::pair<std::string, bool>(output_str_, correct_expr);
}

void PolishNotation::PushToOutput() {
  if (output_str_.back() != ' ') output_str_.push_back(' ');
  output_str_.append(stack_.top());
  stack_.pop();
}

};  // namespace s21