# include <iostream>
#include<string>
#include<memory>
#include<vector>
# include<fstream>
# include "huffman.h"
# include "huf.h"

int main(int argsi, char** args)
{


    try{
        if (argsi != 4){
            throw std::runtime_error("argumetns mistake");
        }
        std::vector<std::pair<uint8_t, int> > inftree;
        std::ifstream inFile;
        inFile.open(args[1]);
        std::ofstream outFile;
        outFile.open(args[2]);
        if ((char) args[3][0] == 'e'){
           huf::encode(inFile, outFile);
        } else if((char) args[3][0] == 'd'){
           huf::decode(inFile, outFile);
        } else{
            throw std::runtime_error("wrong request");
        }

    } catch(std::runtime_error const& e){
        std::cout << e.what()<<'\n';
        return 1;

    }
    return 0;

}

