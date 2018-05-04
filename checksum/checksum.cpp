#include <iostream>
#include <cstring>
#include <sstream> 
#include <fstream>
#include <bitset>
#include <math.h>

using namespace std;

string readFile(int, string);
void error(string errorMsg);
int getChecksumValue(int bitSize, string fileData);

int main(int argc, char **argv) 
{
	if (argc != 3)
	{
		error("Compiled with wrong number of arguments. \nCompilation format: g++ checksum [input file] [bit size]: ");
	}

	int bitSize = atoi(argv[2]);

	if (bitSize < 8 || (bitSize & (bitSize - 1)) != 0 && bitSize > 32)
	{
		error("Compiled with wrong bit size. 8 <= bit size <= 32 and must be a power of 2.");
	}

	string fileData = readFile(bitSize, argv[1]);
	int checksumDecimalValue = getChecksumValue(bitSize, fileData);

	printf("%2d bit checksum is %8x for all %4d chars\n", bitSize, checksumDecimalValue, fileData.length());
}

string readFile(int bitSize, string fileName)
{
	// store file data in content
	std::ifstream ifs(fileName);
 	std::string content( (std::istreambuf_iterator<char>(ifs) ),
                       (std::istreambuf_iterator<char>()    ) );

 	if (content == "")
 	{
 		error("Unable to open file.");
 	}

 	// pad file contents
 	while (content.length() % (bitSize/8) != 0)
 	{
		content += "X";
 	}

	return content;
}

int getChecksumValue(int bitSize, string fileData)
{
	string binary;
	int decimal = 0;
	int numChars = bitSize/8;

	for (int i = 0 ; i < fileData.length() ; i = i+numChars)
	{
		binary = "";

		// represent number in binary form
		for (int j = 0 ; j < numChars ; j++)
		{
			binary += bitset<8>(int(fileData.at(i+j))).to_string();
		}

		decimal += stoi(binary, nullptr, 2);
	}

	return decimal % (int)(pow(2.0, (double)bitSize));
}

void error(string errorMsg)
{
	cerr << errorMsg << endl;
	exit(-1);
}