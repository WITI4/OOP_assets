#pragma once
#include <string>
#include <iostream>

class Hash {
public:
    std::string GetHash(std::string str, unsigned hashLenght);
    int GetControlSum(std::string str);

private:
    std::string hash;
    int receivingExistCodes(int x);
};