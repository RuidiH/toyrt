find_package(Catch2 3 REQUIRED)


add_executable(tests
  test_vecmath.cpp
  test_ray.cpp
)

# Include both headers and Catch2
target_include_directories(tests PRIVATE
  ${PROJECT_SOURCE_DIR}/external/catch2
)

# Link in the header-only lib so it pulls in src/ include dirs
target_link_libraries(tests 
  PRIVATE 
    Catch2::Catch2WithMain
    tfrt_lib
)

include(CTest)
include(Catch)

catch_discover_tests(tests)