add_executable(tests
  test_main.cpp
  test_vecmath.cpp
  test_ray.cpp
  ${PROJECT_SOURCE_DIR}/external/catch2/catch_amalgamated.cpp
)

# Include both your headers and Catch2
target_include_directories(tests PRIVATE
  ${PROJECT_SOURCE_DIR}/external/catch2
  ${PROJECT_SOURCE_DIR}/src
)

# Link in the header-only lib so it pulls in src/ include dirs
target_link_libraries(tests PRIVATE tfrt_lib)

# Register tests
add_test(NAME all_tests COMMAND tests)
