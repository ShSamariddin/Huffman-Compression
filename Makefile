all: main

main: 
	g++ -std=c++11 -fPIC -c huf.cpp huffman.cpp
	g++ -std=c++11 main.cpp huf.cpp huffman.cpp
	g++ -std=c++11 -I/home/samariddin/Documents/cpp-course/huffman gtest/gtest_main.cc gtest/gtest-all.cc gtest.cpp huf.cpp huffman.cpp -o gt -lgmp -lgmpxx -lpthread



