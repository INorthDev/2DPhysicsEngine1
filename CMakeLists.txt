cmake_minimum_required(VERSION 3.23)
project(2DPhysicsEngine1)

set(CMAKE_CXX_STANDARD  23)

add_executable(2DPhysicsEngine1 sfml-app.cpp)

find_package(SFML 2.5.1 COMPONENTS system window graphics network audio REQUIRED)
if(SFML_FOUND)
    message(FOUND: ${SFML_INCLUDE_DIR} ${SFML_LIBRARIES})
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(2DPhysicsEngine1 ${SFML_LIBRARIES})
else()
    message(SFML NOT FOUND)
endif()
