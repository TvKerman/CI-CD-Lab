add_library(BigIntLib BigInt.cpp)
add_executable(main main.cpp)
target_link_libraries(main BigIntLib)
