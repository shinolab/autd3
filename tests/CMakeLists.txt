cmake_minimum_required(VERSION 3.16)

enable_testing()

add_executable(test_autd3)
target_include_directories(test_autd3 PRIVATE .)
target_link_libraries(test_autd3 gtest_main)
target_link_libraries(test_autd3 autd3_common)

add_subdirectory(${PROJECT_SOURCE_DIR}/tests/driver)
add_subdirectory(${PROJECT_SOURCE_DIR}/tests/core)
add_subdirectory(${PROJECT_SOURCE_DIR}/tests/gain/primitive)
add_subdirectory(${PROJECT_SOURCE_DIR}/tests/modulation/primitive)
add_subdirectory(${PROJECT_SOURCE_DIR}/tests/link)

if(BUILD_GAIN_HOLO)
  add_subdirectory(${PROJECT_SOURCE_DIR}/tests/gain/holo)
  target_link_libraries(test_autd3 gain_holo)
  if(BUILD_BACKEND_CUDA)
    target_compile_definitions(test_autd3 PRIVATE TEST_BACKEND_CUDA)
    target_link_libraries(test_autd3 backend_cuda)
  endif()
  if(BUILD_BACKEND_BLAS)
    target_compile_definitions(test_autd3 PRIVATE TEST_BACKEND_BLAS)
    target_link_libraries(test_autd3 backend_blas)
  endif()
endif()

if(BUILD_MODULATION_AUDIO_FILE)
  add_subdirectory(${PROJECT_SOURCE_DIR}/tests/modulation/audio_file)
endif()

target_sources(test_autd3 PRIVATE test.cpp)
add_test(NAME test_autd3 COMMAND test_autd3)

include(GoogleTest)
gtest_discover_tests(test_autd3)

if(WIN32)
  set_target_properties(test_autd3 PROPERTIES FOLDER "test")
  set_target_properties(gtest PROPERTIES FOLDER "test/gtest")
  set_target_properties(gtest_main PROPERTIES FOLDER "test/gtest")
endif()
