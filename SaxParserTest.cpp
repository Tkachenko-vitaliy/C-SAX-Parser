// SaxParser.cpp : Defines the entry point for the console application.
//

#include "SaxFormatter.h"

#include <fstream>
#include <iostream>

using namespace std;

class CXmlFileFormatter : public CSaxFormatter
{
public:
    CXmlFileFormatter(ofstream& file) : m_file(file) {}
protected:
    ofstream& m_file;
    void Output(const char* szText) override { m_file << szText; }
};

int main(int argc, char* argv[])
{
    switch (argc)
    {
    case 0:
        cout << "Input file is not defined" << endl;
        return 1;
        break;
    case 1:
        cout << "Outtput file is not defined"  << endl;
        return 1;
    }

    int res = _strcmpi("A1", "A2");
    ifstream input(argv[1]);
    if (input.fail())
    {
        cout << "Error open input file" << endl;
        return 1;
    }

    ofstream output(argv[2]);
    if (output.fail())
    {
        cout << "Error open input file" << endl;
        return 1;
    }

    try
    {
        CXmlFileFormatter handler(output);
        CSaxParser parser; 
        parser.Parse(&input, &handler);
        std::cout << "Successful" << std::endl;
    }
    catch (CSaxParserException& e)
    {
        std::cout << e.what() << " Line: " << e.GetLine() << " Column: " << e.GetColumn() << std::endl;
    }
    return 0;
}

