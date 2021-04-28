#include "eps_loader.h"
#include <iostream>

int main() {
  EpsLoader a("przyklad.eps");
  std::cout << "Hello world" << std::endl;
  a.load();
  a.compress_eps();

  return 0;
};