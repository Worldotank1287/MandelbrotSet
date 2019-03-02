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
int zeros = 0;
std::vector<std::bitset<8>> digitarray;

void push0(int z){
	zeros = z;
}
int get0() {
	return zeros;
}
void adddigit(std::bitset<8> d) {
	digitarray.push_back(d);
}
std::vector<std::bitset<8>> getdigits() {
	return digitarray;
}