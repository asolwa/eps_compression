set(BINARY ${CMAKE_PROJECT_NAME})

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/mainwindow.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/mainwindow.ui
        ${CMAKE_CURRENT_SOURCE_DIR}/eps_lexer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/eps_objects.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/eps_loader.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/eps_parser.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/shape_factory.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/shape.cpp
)

SET(MODULE_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/mainwindow.h
        ${CMAKE_CURRENT_SOURCE_DIR}/mainwindow.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/eps_lexer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/eps_objects.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/eps_parser.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/shape_factory.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/shape.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/compressor_decorator.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/compressor.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/skip_n_compressor.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/radius_compressor.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/eps_loader.cpp)


if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${BINARY}_run
        ${SOURCES}
    )
else()
     add_executable(${BINARY}_run
           ${SOURCES}
        )
endif()

target_link_libraries(${BINARY}_run PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

add_library(${BINARY}_lib STATIC ${MODULE_SOURCES})

target_link_libraries(${BINARY}_lib PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
