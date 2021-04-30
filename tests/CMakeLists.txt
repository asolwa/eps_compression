set(BINARY ${CMAKE_PROJECT_NAME}_tests)
set(SOURCE_FILES main.cpp src/eps_objects_test.cpp src/eps_parser_test.cpp)

add_executable(${BINARY} ${SOURCE_FILES})
target_link_libraries(${BINARY} PUBLIC ${CMAKE_PROJECT_NAME}_lib gtest)
install(TARGETS ${BINARY} DESTINATION bin)