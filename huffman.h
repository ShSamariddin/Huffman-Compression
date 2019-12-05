#ifndef HUFFMAN_H
#define HUFFMAN_H


#include<iostream>
#include<string>
#include<memory>
#include<vector>

const int len = 256;

class HufType
{
public:
    long long cnt[len] = {};
    HufType(std::vector<std::pair<uint8_t, int>> const& tree);
    HufType();
    void add(const uint8_t* a, size_t si);
    std::vector<std::pair<uint8_t, int> > info();
};

class Huffman
{

public:
   Huffman(HufType rhs);
   Huffman();
   std::pair<std::vector<uint8_t>, int> encod(const uint8_t* a, size_t si);
   std::vector<uint8_t> decod(const uint8_t* a, size_t si, int needBit);

   size_t leftson[len * 2], rightson[len * 2], parent[len * 2];
   int symbolsize = len;
   bool isrightson[len * 2];
};

#endif // HUFFMAN_H
