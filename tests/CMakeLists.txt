set(BINARY ${CMAKE_PROJECT_NAME}_tests)
set(SOURCE_FILES main.cpp src/eps_objects_test.cpp src/eps_parser_test.cpp)
set(CMAKE_AUTOMOC ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

add_executable(${BINARY} ${SOURCE_FILES})
target_link_libraries(${BINARY} PUBLIC ${CMAKE_PROJECT_NAME}_lib gtest Qt${QT_VERSION_MAJOR}::Widgets)
install(TARGETS ${BINARY} DESTINATION bin)
