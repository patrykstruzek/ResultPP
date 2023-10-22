add_executable(result_example result_example.cpp)
add_executable(matcher_example matcher_example.cpp)

target_link_libraries(result_example CrabPP::CrabPP)
target_link_libraries(matcher_example CrabPP::CrabPP)