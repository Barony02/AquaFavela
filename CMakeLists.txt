cmake_minimum_required(VERSION 3.5)
project(AquaFavela VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Busca os componentes necessários do Qt
find_package(Qt6 REQUIRED COMPONENTS Widgets Test)

set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/ui)

# ---------------------------------------------------------
# 1. BusinessLayer (DLL - Lógica de Negócios)
# ---------------------------------------------------------
# Esta biblioteca é coesa: contém apenas a inteligência do sistema
add_library(BusinessLayer SHARED
    src/watermonitor.cpp
    src/AuthService.cpp
    src/User.cpp
    include/watermonitor.h
    include/AuthService.h
    include/User.h
)
target_link_libraries(BusinessLayer PUBLIC Qt6::Widgets Qt6::Core)
target_include_directories(BusinessLayer PUBLIC include)

# ---------------------------------------------------------
# 2. AquaFavela (EXE - Apresentação)
# ---------------------------------------------------------
set(PROJECT_SOURCES
    src/main.cpp
    src/mainwindow.cpp
    src/LoginDialog.cpp
    include/mainwindow.h
    include/LoginDialog.h
    ui/mainwindow.ui
    ui/logindialog.ui
)

add_executable(AquaFavela WIN32 ${PROJECT_SOURCES})

# PROVA DE ACOPLAMENTO FRACO: O EXE linka com a DLL de lógica
target_link_libraries(AquaFavela PRIVATE BusinessLayer Qt6::Widgets)
target_include_directories(AquaFavela PRIVATE include)

# ---------------------------------------------------------
# 3. AquaTests (Executável de Testes)
# ---------------------------------------------------------
set(TEST_SOURCES
    src/mainwindow.cpp
    src/LoginDialog.cpp
    include/mainwindow.h
    include/LoginDialog.h
    ui/mainwindow.ui
    ui/logindialog.ui
    tests/testes.cpp
    # Note: Não incluímos os .cpp de lógica aqui, pois usaremos a DLL
)

add_executable(AquaTests ${TEST_SOURCES})

# O teste valida a BusinessLayer de forma independente da UI
target_link_libraries(AquaTests PRIVATE
    BusinessLayer
    Qt6::Test
    Qt6::Widgets
)
target_include_directories(AquaTests PRIVATE include)
