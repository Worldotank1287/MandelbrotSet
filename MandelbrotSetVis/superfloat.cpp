#include "pch.h"
#include <bitset>
#include <vector>
#include <sstream>
#include <iostream>
#include <string>

/*Purpose of the program is to simply store individual "super" floating point numbers.
	0.00000000000012345678910nnnnnnnnn...
	[int # zeros ][vector of digits		]
	Each digit is stored invidually, with only context to rest of number being order in which the digit comes.
	Each digit is stored as a Byte of Data, rather than an int, in order to save some memory.
*/

//typedef std::bitset<8> BYTE; Use for later, whereever calculations happen. (Probably not in this file).

class SuperFloat {
public:
	SuperFloat() {	//Implement all of this after basic algorithm setup. Replace int with appropriate memory type later.
		//zeros = z;
		//digitArray = initDigits;
	}
	/*void pushZeros(int z) {
		zeros = z;
	};
	int getZeros(void) {
		return zeros;
	};*/
	void addDigits(double digits) {

		std::ostringstream strobj;
		strobj << std::fixed << digits;
		std::string mainString = strobj.str();
		
		int index = 0;
		std::string* front = NULL;
		std::string* back = NULL;

		for (; ;) {
			if (index == mainString.length()) {
				std::cout << "Critical Error";
				break;
			}
			std::string temp = mainString.substr(index, 1);
			if (temp == ".") {
				front = new std::string( mainString.substr(0, index) );
				back = new std::string(mainString.substr(index + 1, mainString.length() - index));
				break;
			}
			++index;
		}
		
		for (int i = 0; i < front->length(); i++) {
			digitFrontArray.push_back(stoi(front -> substr(i, 1)));
		}
		for (int i = 0; i < back->length(); i++) {
			digitBackArray.push_back(stoi(back -> substr(i, 1)));
		}

		delete front;
		delete back;

		std::cout << "Front Digit Array Output\n";
		for (int j = 0; j < digitFrontArray.size(); j++) {
			std::cout << digitFrontArray.at(j);			
		}
		std::cout << "\nEnd Output\n";

		std::cout << "Back Digit Array Output\n";
		for (int j = 0; j < digitBackArray.size(); j++) {
			std::cout << digitBackArray.at(j);
		}
		std::cout << "\nEnd Output\n";
	};
	/*std::vector<int> getDigits(void) {
		return digitArray;
	};*/
	

private:
	//int zeros = 0;
	std::vector<int> digitFrontArray;
	std::vector<int> digitBackArray;
	


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