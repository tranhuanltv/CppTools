#include <iostream>
#include <fstream>

using std::ifstream;
using std::ofstream;
using std::ios_base;
using std::cout;

int main(int argc, char* argv[])
{
    if(argc !=2)
    {
        cout << "Please specify : endline append filename" << std::endl;
        return 0;
    }

    //Open the file for reading in binarymode.
    ifstream fp_read(argv[1], ios_base::in
        | ios_base::binary);

    if (fp_read.bad())
    {
        cout << "append_newline: cannot open file: " << argv[1] << std::endl;
    }

    fp_read.seekg(-1, fp_read.end);

    if (fp_read.bad())
    {
        return 0;
    }

    char ch;
    fp_read.get(ch);
    if (ch == '\n')
        return 0;

    // close before open to write
    fp_read.close();

    // append new line
    ofstream fp_write(argv[1], ios_base::out
        | ios_base::app
        | ios_base::binary);
    fp_write << "\r\n";

    return 0;
}