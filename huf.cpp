#include "huf.h"
# include <iostream>
#include<string>
#include<memory>
#include<vector>
# include<fstream>
# include "huffman.h"
namespace huf{
    //const int blocksize = 20000;
    const int blocksize = 128000;
    void encode(std::istream& inFile, std::ostream& outFile)
    {
        try{
            std::vector<std::pair<uint8_t, int> > inftree;
            if (!inFile || !outFile){
                throw std::runtime_error("wrong direction");
            }

            HufType huft;

            std::unique_ptr<uint8_t[]> data(new uint8_t[blocksize]);
            while (!inFile.eof())
            {
                inFile.read((char *) (data.get()), blocksize);
                huft.add(data.get(), inFile.gcount());
            }
            inftree = huft.info();
            uint32_t treeSize = (uint32_t)inftree.size();
            outFile.write((char *) &(treeSize), sizeof(int32_t));
            for (size_t i = 0; i < inftree.size(); i ++)
            {

                outFile.write((char *) &(inftree[i].first), 1);
                outFile.write((char *) &(inftree[i].second), sizeof(int32_t));
            }
            inFile.clear();
            inFile.seekg(0);
            Huffman ans(huft);
            while (!inFile.eof()){
                int el;
                inFile.read((char*) (data.get()), blocksize);

                std::pair<std::vector<uint8_t>, int> enc = ans.encod(data.get(), (int) inFile.gcount());
                uint32_t siz = enc.second;
                outFile.write((char *) &(siz), sizeof(int32_t));
                outFile.write((char *) enc.first.data(), enc.first.size());
            }

        } catch(std::runtime_error const& e){
            std::cout << e.what()<<'\n';
        }
    }

    void decode(std::istream& inFile, std::ostream& outFile)
    {
        try{
            std::vector<std::pair<uint8_t, int> > inftree;
            if(!inFile || !outFile){
                throw std::runtime_error("wrong direction");
            }
            uint32_t treeSize = 0;
            if(inFile.eof()){
                return ;
            }
            inFile.read((char *) &(treeSize), sizeof(int32_t));
            if(!inFile &&  treeSize > len){
                throw std::runtime_error("wrong information in line 73");
            }
            for(int i = 0; i < treeSize; i ++){
                inftree.push_back({0, 0});
                inFile.read((char *) &(inftree[i].first), 1);
                if(!inFile){
                    throw std::runtime_error("wronng information in line 80");
                }
                inFile.read((char *) &(inftree[i].second), sizeof(int32_t));
                if(!inFile){
                    throw std::runtime_error("wrong information int line 84");
                }
            }
            HufType newTree(inftree);
            Huffman dec(newTree);
            int k = 0;
            std::unique_ptr<uint8_t[]> vec(new uint8_t[blocksize + 10000]);
            while(!inFile.eof()){
                uint32_t siz = 0;
                inFile.read((char *) &(siz), sizeof(int32_t));
                if(siz == 0){
                    continue;
                }
                int vecSize = siz;
                int needsize = 0;
                if(vecSize % 8 != 0){
                    needsize = 8 - vecSize % 8;
                }
                vecSize += needsize;
                vecSize /= 8;
                inFile.read((char *) (vec.get()), vecSize);
                std::vector<uint8_t> res = dec.decod(vec.get(), vecSize, needsize);
                outFile.write((char *) res.data(), res.size());
            }


        } catch(std::runtime_error const& e){
            std::cout << e.what()<<'\n';
        }
    }

}
