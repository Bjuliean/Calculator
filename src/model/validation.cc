#include "validation.h"

namespace s21 {

std::pair<std::string, bool> Validator::ValidateExpression(std::string str) {
  str = DeleteSpaces(str);
  str = ChangeCommaToPoint(str);
  str = AddMultSign(str);
  str = TransformNegateSign(str);
  return CheckPackage(str) && !str.empty()
             ? std::pair<std::string, bool>(str, true)
             : std::pair<std::string, bool>("SYNTAX ERROR", false);
}

bool Validator::CheckPackage(std::string str) {
  return CheckForBrackets(str) && CheckForPoints(str) && IsOkActionRecord(str);
}

bool Validator::CheckForPoints(std::string str) {
  bool res = true, point_locked = false;
  if (str[0] == '.') {
    res = false;
  } else {
    for (size_t i = 0; i < str.length(); ++i) {
      if (str[i] == '.') {
        if (!isdigit(str[i - 1]) || !isdigit(str[i + 1])) {
          res = false;
          break;
        }
        if (point_locked == true) {
          res = false;
          break;
        }
        point_locked = true;
      }
      if (!s21::IsDigit(str, i) && str[i + 1] != '.') point_locked = false;
    }
  }

  return res;
}

bool Validator::CheckForBrackets(std::string str) {
  int counter = 0;
  for (size_t i = 0; i < str.length(); ++i) {
    if (str[i] == '(')
      counter++;
    else if (str[i] == ')')
      counter--;
    if (counter < 0) break;
  }
  return counter == 0;
}

bool Validator::IsOkActionRecord(std::string str) {
  bool res = true;
  size_t nums = 0;
  std::string act(""), prev_act("");
  for (size_t i = 0; i < str.length(); ++i) {
    if (!s21::IsDigit(str, i) && str[i] != '(' && str[i] != ')') {
      act.push_back(str[i]);
      if (s21::GetPriorityValue(act) > 0) {
        if ((s21::IsSimpleAction(act) && s21::IsSimpleAction(prev_act)) ||
            i == 0 || str[i - 1] == '(') {
          res = false;
          break;
        }
        if (s21::IsSimpleAction(act) && nums == 0) {
          res = false;
          break;
        }
        prev_act = act;
        act.clear();
      }
    }
    if ((s21::IsDigit(str, i))) {
      act.clear();
      prev_act.clear();
      nums++;
    }
    if (str[i] == ')' && !prev_act.empty()) {
      break;
    }
  }
  if (!prev_act.empty()) res = false;
  return res;
}

std::string Validator::TransformNegateSign(std::string str) {
  std::string nw;
  for (size_t i = 0; i < str.length(); ++i) {
    if (str[i] == '-' && (str[i + 1] == '(' || i == 0))
      nw.append("(-1)*");
    else
      nw.push_back(str[i]);
  }
  return nw;
}

std::string Validator::ChangeCommaToPoint(std::string str) {
  std::string nw;
  for (auto it : str) {
    if (it == ',')
      nw.push_back('.');
    else
      nw.push_back(it);
  }
  return nw;
}

std::string Validator::DeleteSpaces(std::string str) {
  std::string nw;
  for (auto it : str) {
    if (it != ' ' && it != '\n') nw.push_back(it);
  }
  return nw;
}

std::string Validator::AddMultSign(std::string str) {
  std::string nw, act;
  for (size_t i = 0; i < str.length(); ++i) {
    nw.push_back(str[i]);
    if (str[i] != '.' && (s21::IsDigit(str, i) || str[i] == ')')) {
      if (!s21::IsDigit(str, i + 1) &&
          !s21::IsSimpleAction(std::string(1, str[i + 1])) &&
          str[i + 1] != 'm' && str[i + 1] != ')' && i != str.length() - 1)
        nw.push_back('*');
    }
  }
  return nw;
}

};  // namespace s21