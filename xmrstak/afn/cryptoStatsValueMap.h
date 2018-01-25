#pragma once

#include <map>
#include <list>
#include <vector>
#include <set>

class cryptoStatsValueMap
{

public:
	cryptoStatsValueMap(int size);
	void addValue(int index,int value);
	// void clear();
	int getValue(int index);
	int getValueForNonce(int nonce);
	int getIndex(int index);
	int getNext();
	void sortByValue();
	void resetNonce();
	void resetValues();

	void printMap(int size);


	~cryptoStatsValueMap();

private:
	int lastIndex;
	int size;
	std::vector< std::pair<int, int> > fValue;
};

