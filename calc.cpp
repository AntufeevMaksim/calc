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


unsigned long int IndexAfterBrackets(std::vector<std::string>& operands) {
  unsigned long int i = 0;
  for (void; i < operands.size(); i++) {
    if (operands[i] == "(") {
      return i;
    }
  }
  return i;
}

std::vector<std::string> GetReversePolishRecording(const std::vector<std::string>& expression) {
  std::vector<std::string> result;
  std::vector<std::string> operands;

  

  for (const std::string& element : expression) {

    if (element == "+" || element == "-") {

      while (operands.size() > 0) {
        if (operands.back() != "(") {
          result.push_back(operands.back());
          operands.pop_back();
        }
        else {
          break;
        }
      }


      //std::copy(operands.begin(), operands.end(), std::back_inserter(result));
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

    if (element == ")") {
      while (operands.size() > 0) {
        if (operands.back() != "(") {
          result.push_back(operands.back());
          operands.pop_back();
        }
        else {
          operands.pop_back();
          break;
        }
      }
      continue;
    }

    if (element == "(") {
      operands.push_back(element);
      continue;
    }

    if (element != "") {
      result.push_back(element);
    }
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

    expression[i - 2] = res;

  }

  return expression;


}

std::vector<std::string> FiLLInTests() {
  std::vector<std::string> tests;
  std::string s;

  s = "3*3-3*3";
  tests.push_back(s);
  s = "10-2*3-2+1";
  tests.push_back(s);
  s = "5+10-2*3-2+1";
  tests.push_back(s);
  s = "10-5-2*3-2+1";
  tests.push_back(s);
  s = "3*3-1+1-3*3";
  tests.push_back(s);
  s = "3*3-1+1-3*3+1";
  tests.push_back(s);
  s = "2+2+2+3*3-2-2-2";
  tests.push_back(s);
  s = "3*3-1+1-3*3-1+1+3*3";
  tests.push_back(s);
  s = "3*3-1+1-3*3-1+1+3*3+1";
  tests.push_back(s);
  s = "3*3-1+1+3*3";
  tests.push_back(s);
  s = "1+1+1+1";
  tests.push_back(s);
  s = "2 * 2 * 2 * 2";
  tests.push_back(s);
  s = "1+1+1+1+2*2*2*2";
  tests.push_back(s);
  s = "1+1+1+1-2*2*2*2+12+1";
  tests.push_back(s);
  s = "3*3-3*3+3*3-3*3";
  tests.push_back(s);
  s = "1*2*3*4*5";
  tests.push_back(s);
  s = "1*2*3*4*5-5*4*3*2*1*0";
  tests.push_back(s);
  s = "((((1+2)*(2-1)-(1+2))*2)*2+(1*0)*10)+(1+1)*2";
  tests.push_back(s);
  s = "10-(((10-7)+5-4)*3)";
  tests.push_back(s);
  s = "2*3-2+(1-1+(5-4)+1-1)-(2+2)";
  tests.push_back(s);
  s = "2+3+(5+4)-((5-4)*3)";
  tests.push_back(s);
  s = "(((1+2)*(2-1)-(1+2))*2)+1";
  tests.push_back(s);
  s = "(((1+2)*(2-1)-(1+2))*2)+(1*0)*10";
  tests.push_back(s);
  s = "(((1+2)*(2-1)-(1+2))*2)*2+(1*0)*10";
  tests.push_back(s);
  s = "(8+2*5)/(1+3*2-4)";
  tests.push_back(s);
  s = "6/3*5";
  tests.push_back(s);
  s = "3+4*2/(1-5)";
  tests.push_back(s);

  return tests;

}




std::vector<std::string> GetAnswers() {
  std::vector<std::string> tests;
  std::string s;


  s = "0";
  tests.push_back(s);
  s = "3";
  tests.push_back(s);
  s = "8";
  tests.push_back(s);
  s = "-2";
  tests.push_back(s);
  s = "0";
  tests.push_back(s);
  s = "1";
  tests.push_back(s);
  s = "9";
  tests.push_back(s);
  s = "9";
  tests.push_back(s);
  s = "10";
  tests.push_back(s);
  s = "18";
  tests.push_back(s);
  s = "4";
  tests.push_back(s);
  s = "16";
  tests.push_back(s);
  s = "20";
  tests.push_back(s);
  s = "1";
  tests.push_back(s);
  s = "0";
  tests.push_back(s);
  s = "120";
  tests.push_back(s);
  s = "120";
  tests.push_back(s);
   
  s = "4";
  tests.push_back(s);
  s = "-2";
  tests.push_back(s);
  s = "1";
  tests.push_back(s);
  s = "11";
  tests.push_back(s);
  s = "1";
  tests.push_back(s);
  s = "0";
  tests.push_back(s);
  s = "0";
  tests.push_back(s);
  s = "6";
  tests.push_back(s);
  s = "10";
  tests.push_back(s);
  s = "1";
  tests.push_back(s);
  return tests;
}



int main() {
  
  std::vector<std::string> tests = FiLLInTests();
  std::vector<std::string> answers = GetAnswers();
  unsigned long int i = 0;
  for (void; i < tests.size(); i++) {
    std::string input = tests[i];
    std::vector<std::string> expression = Parse(input);

    std::vector<std::string> reverse_polish_recording = GetReversePolishRecording(expression);
    std::vector<std::string> answer = Addition(reverse_polish_recording);

    if (answer[0] != answers[i]) {
      printf("EROR");
      printf(tests[i].c_str());
    }
    printf(answer[0].c_str());
    printf("   ");
    printf(answers[i].c_str());
    printf("\n");

  }
 
}
