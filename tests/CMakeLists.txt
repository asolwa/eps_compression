cmake_minimum_required(VERSION 3.2)

set(BINARY ${CMAKE_PROJECT_NAME}_tests)

add_subdirectory(lib/googletest)

include_directories(lib/googletest/googletest/include)

set(SOURCE_FILES main.cpp src/test.cpp)

add_executable(${BINARY} ${SOURCE_FILES})
target_link_libraries(${BINARY} PUBLIC ${CMAKE_PROJECT_NAME}_lib gtest)
install(TARGETS ${BINARY} DESTINATION bin)