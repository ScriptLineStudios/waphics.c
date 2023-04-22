add_executable(test_setup test_setup.c)
target_link_libraries(test_setup m)
add_test(setup_gtest test_setup)