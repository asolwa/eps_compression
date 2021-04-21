set(BINARY ${CMAKE_PROJECT_NAME})

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)

set(SOURCES ${SOURCES})
set(MODULE_SOURCES square_root.cpp)

find_package(Qt5Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(${BINARY}_run ${SOURCES})

qt5_use_modules(${BINARY}_run Widgets)

add_library(${BINARY}_lib STATIC ${MODULE_SOURCES})
