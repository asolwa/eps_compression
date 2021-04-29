#include "eps_loader.h"
#include <iostream>

int main() {
  std::cout << "Hello world" << std::endl;
  EpsLoader a;
  a.setInFile("przyklad.eps");
  a.setOutFile("try.eps");
  a.load();
  a.write();

  return 0;
};