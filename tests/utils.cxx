#include "test_utils.h"
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
