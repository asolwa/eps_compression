build() {
  cd build
  make eps_tests
}

test() {
  cd tests
  ./eps_tests  
}

main() {
  build
  test
}

main

