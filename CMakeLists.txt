cmake_minimum_required(VERSION 3.25)
project(tfrt VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD        17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS     OFF)
if (MSVC)
    add_compile_options(/W4 /permissive-)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# ─── 1) Header-only library for your src/ folder ─────────────────────────────
add_library(tfrt_lib INTERFACE)
target_include_directories(tfrt_lib
    INTERFACE
        ${PROJECT_SOURCE_DIR}/src
)

# ─── 2) Main executable from main.cpp, linking the header-only lib ─────────
add_executable(tfrt
    ${PROJECT_SOURCE_DIR}/src/main.cpp
)
target_link_libraries(tfrt
    PRIVATE
        tfrt_lib
)
set_target_properties(tfrt PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}
)

# ─── 3) Enable testing and pull in tests/ ──────────────────────────────────
enable_testing()
add_subdirectory(tests)
