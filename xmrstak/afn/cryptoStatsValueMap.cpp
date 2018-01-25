#include "cryptoStats.h"
#include "cryptoStatsValueMap.h"
#include "xmrstak/misc/console.hpp"

#include <map>
#include <set>
#include <functional>
#include <vector>
#include <algorithm>
#include <utility>

/* TODO remove
int cryptoStatsValueMap::lastIndex;
int cryptoStatsValueMap::size;
std::vector< std::pair<int, int> > cryptoStatsValueMap::fValue;
*/

int cryptoStats::savedValues;
int cryptoStats::ignoredValues;

// Defining a lambda function to compare two pairs. It will compare two pairs using second field
bool compFunction(std::pair<int, int> elem1, std::pair<int, int> elem2) {
	return elem1.second > elem2.second;
};

cryptoStatsValueMap::cryptoStatsValueMap(int inSize)
{
	cryptoStatsValueMap::size = inSize;
	cryptoStatsValueMap::lastIndex = -1;
	for (int i = 0; i < size; i++) {
		fValue.push_back( std::make_pair(i, 0) );
	}
}

void cryptoStatsValueMap::resetValues() {
	for (int i = 0; i < fValue.size(); i++) {
		std::pair<int,int> p = fValue[i];
		p = std::make_pair(p.first, 0);
		fValue[i] = p;
	}
}

void cryptoStatsValueMap::addValue(int index, int value)
{
	if (index < cryptoStatsValueMap::size) {
		std::pair<int, int> p = fValue[index];
		int newValue = p.second + value;
		p = std::make_pair(p.first, newValue);
		fValue[index] = p;
		cryptoStats::savedValues++;
	}
	else {
		cryptoStats::ignoredValues++;
	}
}

int cryptoStatsValueMap::getValue(int index)
{
	return fValue[index].second;
}

/* only used for testing */
int cryptoStatsValueMap::getValueForNonce(int nonce) {
	int value = -1;
	int i = 0;
	while (value == -1) {
		if (fValue[i].first != nonce) {
			i++;
		}
		else {
			value = fValue[i].second;
			break;
		}
	}
	return value;
}

int cryptoStatsValueMap::getIndex(int index)
{
	return fValue[index].first;
}

int cryptoStatsValueMap::getNext()
{
	int nonce = 0;
	lastIndex++;
	if (lastIndex < size) {
		std::pair<int, int> nxt = fValue[lastIndex];
		nonce = nxt.first;
	}
	else {
		nonce = lastIndex;
	}
	return nonce;
}

void cryptoStatsValueMap::sortByValue() {
	std::sort(cryptoStatsValueMap::fValue.begin(), cryptoStatsValueMap::fValue.end(), compFunction);
	int i=0;
}

void cryptoStatsValueMap::resetNonce()
{
	lastIndex = -1;
}

void cryptoStatsValueMap::printMap(int size) {
	for (int i = 0; i < size; i++) {
		printer::inst()->print_msg(L4, "%5i %5i", fValue[i].first,fValue[i].second);
	}
}

cryptoStatsValueMap::~cryptoStatsValueMap()
{
}
