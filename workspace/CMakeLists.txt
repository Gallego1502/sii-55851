CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
PROJECT (TENIS)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)

SET(COMMON_SRCS
    src/Mundo.cpp
    src/Esfera.cpp
    src/Plano.cpp
    src/Raqueta.cpp
    src/Vector2D.cpp
)


add_executable(servidor src/servidor.cpp src/MundoServidor.cpp src/Esfera.cpp src/Raqueta.cpp src/Plano.cpp src/Vector2D.cpp)
target_link_libraries(servidor glut GLU GL pthread)

add_executable(cliente src/cliente.cpp src/MundoCliente.cpp src/Esfera.cpp src/Raqueta.cpp src/Plano.cpp src/Vector2D.cpp)
target_link_libraries(cliente glut GLU GL)
ADD_EXECUTABLE(logger src/logger.cpp)
ADD_EXECUTABLE(bot src/bot.cpp)

