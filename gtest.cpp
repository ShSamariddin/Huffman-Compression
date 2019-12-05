#include <gtest/gtest.h>
# include <bits/stdc++.h>
# include "huf.h"
# include "huffman.h"

bool cheker(std::ifstream& ans1, std::ifstream& ans2){
    const int blocksize = 10;
    std::unique_ptr<uint8_t[]> data1(new uint8_t[blocksize]);
    std::unique_ptr<uint8_t[]> data2(new uint8_t[blocksize]);
    while (!ans1.eof() && !ans2.eof()){

        ans1.read((char*) (data1.get()), blocksize);
        ans2.read((char*) (data2.get()), blocksize);
        if(ans1.gcount() != ans2.gcount()){
            return 0;
        }
        if(ans1.gcount() == 0){
            continue;
        }
        std::string t1((char *) data1.get(), (char *) data1.get() + ans1.gcount());//= (char*)data1.get();
        std::string t2((char *) data2.get(), (char *) data2.get() + ans2.gcount());// = (char*) data2.get();
        if(t1 != t2){
            return 0;
        }
    }
    if(!ans1.eof() || !ans2.eof()){
        return 0;
    }
    return 1;
}

TEST(correctness, test2) {
    std::ifstream inFile1;
    std::ofstream outFile1;
    inFile1.open("./test/testenc1");
    outFile1.open("./test/testdec1");
    huf::encode(inFile1, outFile1);
    inFile1.close();
    outFile1.close();
    std::ifstream inFile2;
    std::ofstream outFile2;
    inFile2.open("./test/testdec1");
    outFile2.open("./test/testsec1");
    huf::decode(inFile2, outFile2);
    inFile2.close();
    outFile2.close();
    std::ifstream ans1;
    std::ifstream ans2;
    ans1.open("./test/testenc1");
    ans2.open("./test/testsec1");
    EXPECT_TRUE(cheker(ans1, ans2));
    ans1.close();
    ans2.close();

}
TEST(correctness, test1){
    std::ifstream inFile1;
    std::ofstream outFile1;
    inFile1.open("./test/testenc1");
    outFile1.open("./test/testdec1");
    huf::encode(inFile1, outFile1);
    inFile1.close();
    outFile1.close();
    std::ifstream inFile2;
    std::ofstream outFile2;
    inFile2.open("./test/testdec1");
    outFile2.open("./test/testsec1");
    huf::decode(inFile2, outFile2);
    inFile2.close();
    outFile2.close();
    std::ifstream ans1;
    std::ifstream ans2;
    ans1.open("./test/testenc1");
    ans2.open("./test/testsec1");
    EXPECT_TRUE(cheker(ans1, ans2));
    ans1.close();
    ans2.close();
}
TEST(correctness, test3){
    std::ifstream inFile1;
    std::ofstream outFile1;
    inFile1.open("./test/testenc3");
    outFile1.open("./test/testdec3");
    huf::encode(inFile1, outFile1);
    inFile1.close();
    outFile1.close();
    std::ifstream inFile2;
    std::ofstream outFile2;
    inFile2.open("./test/testdec3");
    outFile2.open("./test/testsec3");
    huf::decode(inFile2, outFile2);
    inFile2.close();
    outFile2.close();
    std::ifstream ans1;
    std::ifstream ans2;
    ans1.open("./test/testenc3");
    ans2.open("./test/testsec3");
    EXPECT_TRUE(cheker(ans1, ans2));
    ans1.close();
    ans2.close();
}

TEST(correctness ,test4){
    std::ofstream text;
    text.open("./test/testenc4");
    int t = rand() % 100000;
    while(t != 0){
        t--;
        uint32_t siz = rand() % 256;
        text.write((char *) &(siz), sizeof(int32_t));
    }
    text.close();
    std::ifstream inFile1;
    std::ofstream outFile1;
    inFile1.open("./test/testenc4");
    outFile1.open("./test/testdec4");
    huf::encode(inFile1, outFile1);
    inFile1.close();
    outFile1.close();
    std::ifstream inFile2;
    std::ofstream outFile2;
    inFile2.open("./test/testdec4");
    outFile2.open("./test/testsec4");
    huf::decode(inFile2, outFile2);
    inFile2.close();
    outFile2.close();
    std::ifstream ans1;
    std::ifstream ans2;
    ans1.open("./test/testenc4");
    ans2.open("./test/testsec4");
    EXPECT_TRUE(cheker(ans1, ans2));
    ans1.close();
    ans2.close();
}

TEST(correctness ,test5){
    std::stringstream in1;
    std::stringstream out;
    std::stringstream in2;
    int t = rand() % 100000;
    while(t != 0){
        t--;
        uint32_t siz = rand() % 256;
        in1.write((char *) &(siz), sizeof(int32_t));
    }
    huf::encode(in1, out);
    huf::decode(out, in2);
    EXPECT_TRUE(in1.str()== in2.str());
}
