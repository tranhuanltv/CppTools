#include <string>
#include <vector>
#include <fstream>

using namespace std;

bool ReadBin(const std::string& filePath, std::vector<unsigned char> *vBuffer) 
{
	std::ifstream is(filePath.c_str(), ios::in | ios::binary);

    if (!is.good())
        return false;

	is.seekg (0, is.end);
	size_t length = is.tellg();
	is.seekg (0, is.beg);

	vBuffer->resize(length);
	return is.read((char*)&vBuffer->front(), length);
}



int main(int argc, char** argv)
{
    if (argc < 2)
        return -1;

    std::vector<unsigned char> data;
    string result;
    result.reserve(data.size() * 5); // 255 -> "0xFF,"
    if (ReadBin(argv[1], &data))
    {
        char const hex_chars[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

        int counter = 0;

        std::vector<unsigned char>::iterator iter = data.begin();
        for(; iter != data.end(); ++iter)
        {
            if (++counter % 10 == 0)
                result.append("\n\t");

            result.append("0x");
            result += string(1, (hex_chars[(*iter & 0xF0) >> 4]));
            result.append(string(1, hex_chars[(*iter & 0x0F) >> 0]));
            result.append(",");
        }

        if (!result.empty())
            result[result.size() - 1] = '\0';

        printf("{\n\t%s\n};\n", result.c_str());
    }
}
