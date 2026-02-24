cmake_minimum_required(VERSION 3.5)
project(AquaFavela VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(QT_NO_CREATE_VERSIONLESS_TARGETS ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Sql Core Test)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/ui)

# ---------------------------------------------------------
# CAMADA 1: DataLayer (DLL - Acesso a Dados)
# ---------------------------------------------------------
add_library(DataLayer SHARED
    src/DatabaseManager.cpp
    #src/ConsumptionRepository.cpp
    src/User.cpp
    include/DatabaseManager.h
    #include/ConsumptionRepository.h
    include/User.h
)
target_link_libraries(DataLayer PUBLIC Qt6::Sql Qt6::Core)
target_include_directories(DataLayer PUBLIC include)

# ---------------------------------------------------------
# CAMADA 2: BusinessLayer (DLL - Lógica de Negócios)
# ---------------------------------------------------------
add_library(BusinessLayer SHARED
    src/watermonitor.cpp
    src/AuthService.cpp
    src/ConsumptionService.cpp
    include/watermonitor.h
    include/AuthService.h
    include/ConsumptionService.h
)
# A Lógica depende dos Dados, mas a Interface não precisa saber disso
target_link_libraries(BusinessLayer PUBLIC DataLayer Qt6::Core)
target_include_directories(BusinessLayer PUBLIC include)

# ---------------------------------------------------------
# CAMADA 3: AquaFavela (EXE - Apresentação/UI)
# ---------------------------------------------------------
set(PROJECT_SOURCES
    src/main.cpp
    src/mainwindow.cpp
    src/LoginDialog.cpp
    src/AdminDialog.cpp
    include/mainwindow.h
    include/LoginDialog.h
    include/AdminDialog.h
    ui/mainwindow.ui
    ui/logindialog.ui
    ui/admindialog.ui
)

add_executable(AquaFavela WIN32 ${PROJECT_SOURCES})
# O EXE só conversa com a BusinessLayer (Fraco Acoplamento)
target_link_libraries(AquaFavela PRIVATE BusinessLayer Qt6::Widgets)
target_include_directories(AquaFavela PRIVATE include)
# -------------------------
# Testes (Corrigido)
# -------------------------
# Removi src/watermonitor.cpp e src/AuthService.cpp se eles já estiverem na DataLayer
# Mas como eles não estão na DataLayer no seu código acima, vamos mantê-los aqui
# O segredo é incluir TODOS os arquivos .h e .ui para o MOC/UIC trabalhar
set(TEST_SOURCES
    tests/testes.cpp
    src/mainwindow.cpp
    src/watermonitor.cpp
    src/AuthService.cpp
    src/AdminDialog.cpp
    #src/ConsumptionRepository.cpp

    # Headers para o MOC
    include/mainwindow.h
    include/AdminDialog.h
    include/AuthService.h
    include/watermonitor.h

    # Interfaces para o UIC
    ui/mainwindow.ui
    ui/admindialog.ui
    ui/logindialog.ui
)

add_executable(AquaTests ${TEST_SOURCES})

# Adicionado Qt6::Sql explicitamente para garantir que o Driver SQLite seja visto nos testes
target_link_libraries(AquaTests PRIVATE
    DataLayer
    BusinessLayer
    Qt6::Widgets
    Qt6::Test
    Qt6::Sql
    Qt6::Core
)

target_include_directories(AquaTests PRIVATE include)
