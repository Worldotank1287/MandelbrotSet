#include "pch.h"
#include <bitset>
#include <vector>
#include <sstream>
#include <iostream>
#include <string>

/*Purpose of the program is to simply store individual "super" floating point numbers.
		0.00000000000012345678910nnnnnnnnn...
		[int # zeros ][vector of digits         ]
		Each digit is stored invidually, with only context to rest of number being order in which the digit comes.
		Each digit is stored as a Byte of Data, rather than an int, in order to save some memory.
*/

//typedef std::bitset<8> BYTE; Use for later, whereever calculations happen. (Probably not in this file).

class SuperFloat {
public:
	SuperFloat() {  //Implement all of this after basic algorithm setup. Replace int with appropriate memory type later.
			//zeros = z;
			//digitArray = initDigits;
	}
	/*void pushZeros(int z) {
			zeros = z;
	};
	int getZeros(void) {
			return zeros;
	};*/
	SuperFloat* addDigits(SuperFloat* s) {
		SuperFloat *newSuperFloat = new SuperFloat;
		std::vector<int> newfront;
		std::vector<int> newback;

		if (s->digitBackArray.size() >= digitBackArray.size()) {
			for (unsigned int i = 0; i < s->digitBackArray.size(); i++) {
				if (i >= digitBackArray.size()) newback.push_back(s->digitBackArray.at(i));
				else {
					newback.push_back(digitBackArray.at(i) + s->digitBackArray.at(i));
				}
			}
		}
		else {
			for (unsigned int i = 0; i < digitBackArray.size(); i++) {
				if (i >= s->digitBackArray.size()) newback.push_back(digitBackArray.at(i));
				else {
					newback.push_back(digitBackArray.at(i) + s->digitBackArray.at(i));
				}
			}
		}

		if (s->digitFrontArray.size() >= digitFrontArray.size()) {
			for (unsigned int i = 0; i < s->digitFrontArray.size(); i++) {
				if (i < digitFrontArray.size()) {
					newfront.insert(newfront.begin(), s->digitFrontArray.at(s->digitFrontArray.size() - i - 1) + digitFrontArray.at(digitFrontArray.size() - i - 1));
				}
				else {
					newfront.insert(newfront.begin(), s->digitFrontArray.at(s->digitFrontArray.size() - i - 1));
				}
			}
		}
		else {
			for (unsigned int i = 0; i < digitFrontArray.size(); i++) {
				if (i < s->digitFrontArray.size()) {
					newfront.insert(newfront.begin(), s->digitFrontArray.at(s->digitFrontArray.size() - i - 1) + digitFrontArray.at(digitFrontArray.size() - i - 1));
				}
				else {
					newfront.insert(newfront.begin(), digitFrontArray.at(digitFrontArray.size() - i - 1));
				}
			}
		}
		for (unsigned int i = newback.size() - 1; i > 0; i--) {
			if (newback.at(i) >= 10) {
				if (i == 0) {
					newfront.at(newfront.size() - 1)++;
					newback.at(i) -= 10;
				}
				else {
					newback.at(i - 1)++;
					newback.at(i) -= 10;
				}
			}
		}
		for (unsigned int i = newfront.size(); i > 0; i--) {
			if (newfront.at(i-1) >= 10) {
				if (i == 1) {
					newfront.insert(newfront.begin(), 1);
					newfront.at(i) -= 10;
				}
				else {
					newfront.at(i - 2)++;
					newfront.at(i - 1) -= 10;
				}
			}
		}
		

		newSuperFloat->assignDigits(newfront, newback);
		return newSuperFloat;
	}
	void assignDigits(std::vector<int> newfront, std::vector<int> newback) {
		digitFrontArray = newfront;
		digitBackArray = newback;
	}

	void setDigits(double digits) {
		//This method will be completely removed at some point. No real need for doubles at all.
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
				front = new std::string(mainString.substr(0, index));
				back = new std::string(mainString.substr(index + 1, mainString.length() - index));
				break;
			}
			++index;
		}

		for (unsigned int i = 0; i < front->length(); i++) {
			digitFrontArray.push_back(stoi(front->substr(i, 1)));
		}
		for (unsigned int i = 0; i < back->length(); i++) {
			digitBackArray.push_back(stoi(back->substr(i, 1)));
		}

		delete front;
		delete back;
	};
	/*std::vector<int> getDigits(void) {
			return digitArray;
	};*/
	std::string toString() {
		std::string output = "";
		for (unsigned int i = 0; i < digitFrontArray.size(); i++) {
			output = output + std::to_string(digitFrontArray.at(i)) + " ";
		}
		output = output + ".";
		for (unsigned int i = 0; i < digitBackArray.size(); i++) {
			output = output + std::to_string(digitBackArray.at(i)) + " ";
		}
		return output;
	}

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