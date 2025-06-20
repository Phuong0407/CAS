cmake_minimum_required(VERSION 3.10)
project (tokenizer.c)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

include_directories(
    ../../../include/kernel
)

add_executable(test_tokenizer
    test_tokenizer.c
    ../../../src/kernel/tokenizer.c
)

target_compile_options(test_tokenizer PRIVATE -Wall -Wextra)