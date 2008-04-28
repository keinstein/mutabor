#include <iostream>
#include <string>

int main() {
  std::string s="",s1;
  char s2[100];
  bool start = true;
  while (std::cin.good()) {
    std::cin.getline(s2,99);
    s1=s2;
    //    std::cerr << ": " <<  s1;
    if (s1.find('=')!=s1.npos) {
      std::cout << s;
      if (!start) std::cout << std::endl;
      else start=false;
      s = s1;
    } else { s += " "; s += s1; }
  }
  std::cout << s << std::endl;
}
