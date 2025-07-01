cmake_minimum_required(VERSION 3.10)
project (tokenizer.c)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -march=native -funroll-loops -fprefetch-loop-arrays")
# set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -march=native -flto -fno-stack-protector -funroll-loops")


add_compile_options(-g)
include_directories(
    ../../../include/
)

add_executable(test_tokenizer
    test_tokenizer.c
    ../../../src/kernel/tokenization.c
    ../../../src/kernel/number_tokenization.c
    ../../../src/kernel/symbol_tokenization.c
)

target_compile_options(test_tokenizer PRIVATE -Wall -Wextra)