cmake_minimum_required(VERSION 3.25)
# ───────────────────────────────────────────────────────────────────────────────
# 1. Specify your project name, version (optional), and the language(s) used.
#    This creates the variable PROJECT_NAME (here "tfrt") for later.
project(tfrt
        VERSION 0.1.0    # optional: useful if you ever do `install()`
        LANGUAGES CXX)   # we're only using C++ here

# ───────────────────────────────────────────────────────────────────────────────
# 2. Tell CMake what C++ standard we need.
#    - CMAKE_CXX_STANDARD: the standard (e.g. 17 for C++17)
#    - CMAKE_CXX_STANDARD_REQUIRED: error out if compiler doesn't support it
#    - CMAKE_CXX_EXTENSIONS: disable compiler-specific extensions (like GNU++17)
set(CMAKE_CXX_STANDARD        17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS     OFF)

# ───────────────────────────────────────────────────────────────────────────────
# 3. Add some warning flags to help catch errors early.
#    We do it differently on MSVC vs. GCC/Clang.
if (MSVC)
    # /W4: high warning level on MSVC
    # /permissive-: stricter standards conformance
    add_compile_options(/W4 /permissive-)
else()
    # -Wall/-Wextra: many warnings
    # -Wpedantic: warn on non-standard code
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# ───────────────────────────────────────────────────────────────────────────────
# 4. Gather all your .cpp files under src/ into a single variable.
#    - GLOB_RECURSE: recursively find matching files
#    - CONFIGURE_DEPENDS: re-run CMake if files are added/removed
file(GLOB_RECURSE PROJECT_SOURCES
     CONFIGURE_DEPENDS
     ${PROJECT_SOURCE_DIR}/src/*.cpp
)

# ───────────────────────────────────────────────────────────────────────────────
# 5. Define an executable target:
#    - ${PROJECT_NAME} expands to "touch_fish_rt"
#    - ${PROJECT_SOURCES} is the list of .cpp files from above
add_executable(${PROJECT_NAME}
               ${PROJECT_SOURCES})

# ───────────────────────────────────────────────────────────────────────────────
# 6. Tell the compiler where to look for header files (.hpp/.h):
#    We put headers alongside your .cpp files in src/.
#    PRIVATE means “only this target needs them.”
target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${PROJECT_SOURCE_DIR}/src
)

# ───────────────────────────────────────────────────────────────────────────────
# 7. Override the default output location so the binary lands in your project root.
#    By default CMake puts executables in the build directory; this moves it to:
#      <your-repo-root>/touch_fish_rt (on Unix) or touch_fish_rt.exe (on Windows)
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}
)
