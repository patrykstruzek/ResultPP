add_executable(tests test.cpp)

target_link_libraries(tests CrabPP)

add_test(NAME speed_test COMMAND speed_test)
