#include "pch.h"
#include <bitset>
#include <vector>

/*Purpose of the program is to simply store individual "super" floating point numbers.
	0.00000000000012345678910nnnnnnnnn...
	[int # zeros ][vector of digits		]
	Each digit is stored invidually, with only context to rest of number being order in which the digit comes.
	Each digit is stored as a Byte of Data, rather than an int, in order to save some memory.
*/

//typedef std::bitset<8> BYTE; Use for later, whereever calculations happen. (Probably not in this file).

class SuperFloat {
public:
	SuperFloat(int z, std::vector<std::bitset<8>> initDigits) {
		zeros = z;
		digitArray = initDigits;
	}
	void pushZeros(int z) {
		zeros = z;
	};
	int getZeros(void) {
		return zeros;
	};
	void addDigits(std::bitset<8> digits) {
		digitArray.push_back(digits);
	};
	std::vector<std::bitset<8>> getDigits(void) {
		return digitArray;
	};
private:
	int zeros = 0;
	std::vector<std::bitset<8>> digitArray;
};
/*
void SuperFloat::pushZeros(int z){
	zeros = z;
}

int SuperFloat::getZeros() {
	return zeros;
}

void SuperFloat::addDigits(std::bitset<8> digits) {
	digitArray.push_back(digits);
}

std::vector<std::bitset<8>> SuperFloat::getdigits() {
	return digitArray;
}*/