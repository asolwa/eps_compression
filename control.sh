setup() {
  mkdir -p build
}

build() {
  cd build
  cmake ..
  make
  cd ..
}

test() {
  if [ `basename "$PWD"` = "eps_compression" ]; then
    cd build
  fi
  cd tests
  ./eps_tests 
  cd ../.. 
}

run() {
  if [ `basename "$PWD"` = "eps_compression" ]; then
    cd build
  fi
  cd src
  ./eps_run
  cd ../..  
}

clean()
{
  if [ `basename "$PWD"` = "eps_compression" ]; then
    rm -rf build
  fi
}

usage()
{
  echo "usage: ./build.sh [[-b build ] [-r run ] [-t test ]]"
}

if [ "$#" -eq 0 ]; then
  usage
fi

for arg in "$@"
do
  case $arg in
      -b | --build )
        setup
        build
        ;;
      -r | --run )
        run ;;
      -t | --test )
        test ;;
      -c | --clean )
        clean ;;
      * )
        usage ;;
  esac
done
