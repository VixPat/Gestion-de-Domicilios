cmake_minimum_required(VERSION 3.31)
project(untitled2)

set(CMAKE_CXX_STANDARD 20)

add_executable(untitled2 main.cpp
        include/Estructuras/Colas.h
        include/Estructuras/Pilas.h
        include/Estructuras/Listas_Dobles.h
        include/Estructuras/ABB.h
        src/Cliente.cpp
        include/Cliente.h
        src/Domiciliario.cpp
        include/Domiciliario.h
        src/Restaurante.cpp
        include/Restaurante.h
        src/Pedido.cpp
        include/Pedido.h
        src/Zona.cpp
        include/Zona.h
        src/DB/DB.cpp
        include/DB/DB.h
        src/Helpers/Helpers.cpp
        include/Helpers/Helpers.h
        Tests/Test_1.cpp
        Tests/Test.h
        Tests/Test_2.cpp
        Tests/Test_3.cpp
        include/Estructuras/ColasConPrioridad.h
        include/Estructuras/Grafo.cpp
        include/Estructuras/Grafo.h
)