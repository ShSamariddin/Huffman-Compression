#ifndef HUF_H
#define HUF_H
# include<fstream>
# include<vector>
#include <iostream>

namespace huf{
    void encode(std::istream& inFile, std::ostream& outFile);
    void decode(std::istream& inFile, std::ostream& outFile);
};

#endif // HUF_H
