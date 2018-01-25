#pragma once

#include <map>
#include <list>
#include <vector>
#include <cmath>
#include <mutex>
#include "cryptoStatsValueMap.h"

class cryptoStats
{
public:

	static const int numHashBits = 10;
	static const int numHashes = 1024;
	static const int numNonces = 2056;

	static void readFromFile(std::string filePathName);
	static void readFromFile();
	static void buildHashNonceMaps();
	static void buildHashNonceMaps(std::string filePathName);
	static void createValueMaps();
	static void clearValueMaps();
	static void fillValueMaps();
	static void writeToFile(std::string filePathName);
	static void writeToFile();
	static void addPoint(int hashBits, int nonce);
	static void writeStats();
	static int getHashBits(int i);
	static int getNonceFromList(int i);

	static int getNonce(int hashBits);
	static void resetStats();
	static void printStats();

	~cryptoStats(); // not sure this one is needed

	static int getProcessMemory();

    // for statistics
	static int savedValues;
	static int ignoredValues;

	// for testing only
	static int getValue( int hashBits, int vmIndex );
	static int getValueForNonce( int hashBits, int nonce );

private:
	
	// list of values
	static std::vector<int> hashBits;
	static std::vector<int> nonces;
	static std::mutex mtx;
	
	// function value map array
	static std::vector<cryptoStatsValueMap*> fMap;
	
	
};

static std::vector<std::string> split(const std::string & s, char delim);
