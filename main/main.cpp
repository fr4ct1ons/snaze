#include<string>
#include<fstream>
#include<iostream>

int main(int argc, char const *argv[])
{
    std::string filename = argv[1];

    std::ifstream inputFile(filename);

    int levelW, levelH;

    inputFile >> levelH;
    inputFile >> levelW;
    std::string *level = new std::string[levelH];
    for (int i = 0; i < levelH; i++)
    {
        std::getline(inputFile, level[i]);
    }

    for (int i = 0; i < levelH; i++)
    {
        std::cout << level[i] << "\n";
    }

    std::cout << std::endl;

    inputFile.close();

    return 0;
}
