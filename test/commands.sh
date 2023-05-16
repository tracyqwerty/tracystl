
# `-lpthread` is a linker option, it tells the linker to link the POSIX threads library (pthread library).
# This is actually equivalent to adding `-l pthread` in the link command. This option only affects the link phase and does not affect the compilation phase.

# `-pthread` is a compiler and linker option, which tells the compiler and linker to use the POSIX thread library.
# This option affects both the compilation phase and the link phase. In the compilation phase, it will add appropriate macro definitions and compilation options to ensure that the source code can interact with the pthread library correctly.
# In the link phase, it will ensure that the pthread library is linked like `-lpthread`.


#allocator_test
g++ -std=c++17 allocator_test.cpp -lgtest -lgtest_main -pthread -o allocator_test
#iterator_test
g++ -std=c++17 iterator_test.cpp -lgtest -lgtest_main -pthread -o iterator_test
#vector_test
g++ -std=c++20 vector_test.cpp -lgtest -lgtest_main -pthread -o vector_test