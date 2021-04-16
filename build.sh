setup() {
  mkdir -p build
}


build() {
  cd build
  cmake ..
  make
}

test() {
  cd tests
  ./eps_tests  
}

main() {
  setup
  build
  test
}

main

