cmake_minimum_required(VERSION 3.5)

project(AquaFavela VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Arquivos do projeto
set(PROJECT_SOURCES
        src/main.cpp
        src/mainwindow.cpp
        src/AuthService.cpp
        src/watermonitor.cpp
        src/LoginDialog.cpp
        include/mainwindow.h
        include/AuthService.h
        include/watermonitor.h
        include/User.h
        include/LoginDialog.h
        ui/mainwindow.ui
        ui/logindialog.ui
)

find_package(Qt6 REQUIRED COMPONENTS Widgets Test)

set(TEST_SOURCES
    tests/testes.cpp
    src/watermonitor.cpp
    src/AuthService.cpp
)

add_executable(AquaTests ${TEST_SOURCES})
target_link_libraries(AquaTests PRIVATE Qt6::Widgets Qt6::Test)
target_include_directories(AquaTests PRIVATE include)

add_executable(AquaFavela WIN32 ${PROJECT_SOURCES})

set_target_properties(AquaFavela PROPERTIES AUTOUIC_SEARCH_PATHS "ui")

target_link_libraries(AquaFavela PRIVATE Qt6::Widgets)

# Inclusão de diretórios
target_include_directories(AquaFavela PRIVATE include)
