cmake_minimum_required(VERSION 3.25)
project(tfrt LANGUAGES CXX)

# Cpp standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)                                     # Visual Studio / MSVC
    add_compile_options(/W4 /permissive-)
else()                                       # GCC / Clang / MinGW
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

file(GLOB_RECURSE PROJECT_SOURCES
     CONFIGURE_DEPENDS
     ${PROJECT_SOURCE_DIR}/src/*.cpp
)

# source
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

# headers
target_include_directories(${PROJECT_NAME}
  PUBLIC
      $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
      $<INSTALL_INTERFACE:include>
)