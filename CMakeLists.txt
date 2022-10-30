cmake_minimum_required(VERSION 3.23)
project(2DPhysicsEngine)

set(CMAKE_CXX_STANDARD 23)

add_executable(2DPhysicsEngine main.cpp)

find_package(SFML 2.5.1 COMPONENTS system window graphics network audio REQUIRED)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(2DPhysicsEngine ${SFML_LIBRARIES})
endif()

