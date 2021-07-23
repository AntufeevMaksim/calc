
#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <algorithm>
#include <functional>

std::string Input() {
  std::string input;
  std::cin >> input;
  return input;
}

void print(std::vector<std::string>& answer) {
  printf(answer[0].c_str());
}




bool ThisOperand(const char c) {
  if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')') {
    return true;
  }
  return false;
}

bool ThisOperand(std::string& c) {
  if (c == "+" || c == "-" || c == "*" || c == "/" || c == "(" || c == ")") {
    return true;
  }
  return false;
}


std::vector<std::string> Parse(const std::string& str) {
  std::vector<std::string> result;
  std::string num;

  for (const char c : str) {
    if (ThisOperand(c)) {
      if (num != "") {
        result.push_back(num);
      }
      num = "";

      std::string operand;
      operand.push_back(c);
      result.push_back(operand);

      continue;
    }

    num.push_back(c);

  }
  result.push_back(num);

  return result;
}

bool PriorityOperand(const std::vector<std::string>& operands) {
  if (operands.size() == 0) {
    return false;
  }

  unsigned long int last = operands.size() - 1;
  if (operands[last] == "/" || operands[last] == "*") {
    return true;
  }
  return false;
}

std::vector<std::string> GetReversePolishRecording(const std::vector<std::string>& expression) {
  std::vector<std::string> result;
  std::vector<std::string> operands;



  for (const std::string& element : expression) {

    if (element == "+" || element == "-") {

      std::reverse(operands.begin(), operands.end());
      for (const auto& operand : operands) {
        result.push_back(operand);
      }
      //std::copy(operands.begin(), operands.end(), std::back_inserter(result));
      operands.clear();
      operands.push_back(element);
      continue;
    }

    if (element == "*" || element == "/") {
      if (PriorityOperand(operands)) {
        unsigned long int last_element = operands.size() - 1;
        result.push_back(operands[last_element]);
        operands.pop_back();
      }
      operands.push_back(element);
      continue;
    }



    result.push_back(element);

  }
  std::reverse(operands.begin(), operands.end());
  for (const auto& operand : operands) {
    result.push_back(operand);
  }
  return result;
}
std::string ADD(int num1, int num2, std::string& operator_) {
  if (operator_ == "+") {
    return std::to_string(num1 + num2);
  }

  if (operator_ == "-") {
    return std::to_string(num1 - num2);
  }

  if (operator_ == "*") {
    return std::to_string(num1 * num2);
  }

  if (operator_ == "/") {
    return std::to_string(num1 / num2);
  }
}

std::vector<std::string> Addition(std::vector<std::string>& expression) {
  unsigned long int size1 = 1;
  int num1 = 0;
  int num2 = 0;
  std::string operator_;


  while (expression.size() > size1) {
    unsigned long int i = 0;
    for (void; i < expression.size(); i++) {
      if (ThisOperand(expression[i])) {
        num1 = std::stoi(expression[i - 2]);
        num2 = std::stoi(expression[i - 1]);
        operator_ = expression[i];
        break;
      }
    }

    std::string res = ADD(num1, num2, operator_);

    expression.erase(expression.begin() + i - 2, expression.begin() + i);

    //if (expression.size() == i-1) {
    //  expression.insert(expression.end()-2, res);
    //}
    //else if (expression.size() > 0){
    expression[i - 2] = res;
    //    expression.insert(expression.begin() + i - 2, res);

  }

  return expression;


}





int main() {
  std::string input = Input();
  std::vector<std::string> expression = Parse(input);

  std::vector<std::string> reverse_polish_recording = GetReversePolishRecording(expression);
  std::vector<std::string> answer = Addition(reverse_polish_recording);

  print(answer);
}

