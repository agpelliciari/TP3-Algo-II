cmake_minimum_required(VERSION 3.22)
project(ayp2_plantilla_tp_grupal_2c2023)

set(CMAKE_C_STANDARD 23)

add_compile_options(-Wall -Werror -Wconversion)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../")
set(CXXFLAGS "-Wall -Werror -Wconversion")
set(CMAKE_CXX_FLAGS "${CXXFLAGS}")

include_directories(include)
include_directories(src)
include_directories(bGVjdG9y)

add_executable(ayp2_plantilla_tp_grupal_2c2023
        src/Placa.cpp
        src/Arbol_de_placas.cpp
        src/Arma.cpp
        src/Inventario_de_Armas.cpp
        src/Grafo.cpp
        src/Floyd.cpp
        src/Dijkstra.cpp
        src/Matriz.cpp
        bGVjdG9y/bGVjdG9y.cpp
        bGVjdG9y/ZGVjb2Rl.cpp
        src/Menu_principal.cpp
        src/Tablero.cpp
        src/Juego.cpp
        main.cpp
)

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "main")