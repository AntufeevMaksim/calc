#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <algorithm>
#include <functional>

std::string Input(){
  std::string input;
  std::cin >> input;
  return input;
}

bool ThisOperand(const char c){
  if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')'){
    return true;
  }
  return false;
}

std::vector<std::string> Parse(const std::string& str){
  std::vector<std::string> result;
  std::string num;

  for (const char c : str){
    if (ThisOperand(c)){
      if (num != ""){
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


std::vector<std::string> GetReversePolishRecording(const std::vector<std::string>& expression){
  std::vector<std::string> result;
  std::vector<std::string> operands;



  for (const std::string& element : expression){

    if (element == "+" || element == "-"){
      for (const auto& operand : operands){
        result.push_back(operand);
      }
      //std::copy(operands.begin(), operands.end(), std::back_inserter(result));
      operands.clear();
      operands.push_back(element);
      continue;
    }

    if (element == "*" || element == "/"){
      operands.push_back(element);
      continue;
    }



    result.push_back(element);

  }
  for (const auto& operand : operands){
    result.push_back(operand);
  }
  return std::vector<std::string>{};
}















int main(){
  std::string input = Input();
  std::vector<std::string> expression = Parse(input);

  std::vector<std::string> reverse_polish_recording = GetReversePolishRecording(expression); 

}
