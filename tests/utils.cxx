#include "utils.h"
#include <string>
#include <vector>

using namespace std;

unsigned t_utils::count_ocr(std::string str, std::string sub){
  unsigned result = 0;
  size_t pos = 0;

  while((pos = str.find(sub, pos)) != string::npos){
    result++;
    pos += sub.length();
  };
  
  return result;
}

bool t_utils::is_sub_str(string str, string sub){
  return (str.find(sub) != string::npos);
}
