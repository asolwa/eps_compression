#include <iostream>
#include "eps_loader.h"

int main() {
  std::cout << "Hello world" << std::endl;
  EpsLoader a;
  a.setInFile("przyklad.eps");
  a.setOutFile("try1.eps");
  a.load();
  a.write();

  return 0;
};