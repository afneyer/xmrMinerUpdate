#include "cryptoStats.h"
#include "cryptoStatsValueMap.h"
#include "xmrstak/misc/console.hpp"
#include "stats.h"
#include <fstream>
#include <string>
#include <vector>
#include <iosfwd>
#include <sstream>
// #include "windows.h"
// #include "psapi.h"


std::vector<int> cryptoStats::hashBits;
std::vector<int> cryptoStats::nonces;
std::vector<cryptoStatsValueMap*> cryptoStats::fMap;
std::mutex cryptoStats::mtx;

void cryptoStats::readFromFile() {
	std::string filePathName = "hashNonceList.txt";
	cryptoStats::readFromFile(filePathName);
}


void cryptoStats::readFromFile( std::string filePathName )
{
	std::ifstream inFile;

	inFile.open(filePathName);
	if (!inFile) {
		printer::inst()->print_msg(L1, "Unable to open file %s", filePathName.c_str());
		// printer::inst()->print_msg(L1, "Path = %s", stats::getexepath().c_str());
		// stats::dir("./");
		exit(1);   // call system to stop
	}
	int k = 0;
	int i = 0;
	
	// clear the vectors
	hashBits.clear();
	nonces.clear();



	std::string line;
	while (getline(inFile, line)) {
		std::vector<std::string> v = split(line, ',');
		addPoint(std::stoi(v[0]), std::stoi(v[1]));
	}
	inFile.close();
}

void cryptoStats::writeToFile() {
	std::string filePathName = "hashNonceList.txt";
	cryptoStats::writeToFile(filePathName);
}

void cryptoStats::writeToFile( std::string filePathName )
{
	std::ofstream ofile;

	printer::inst()->print_msg(L4, "Writing %s", filePathName.c_str());
	ofile.open(filePathName);
	for (int i = 0; i < cryptoStats::hashBits.size(); i++) {
		std::string s = std::to_string(cryptoStats::hashBits[i]) + ",";
		s += std::to_string(cryptoStats::nonces[i])  + "\n";
		ofile << s;
	}
	ofile.close();
}

void cryptoStats::addPoint(int hash, int nonce)
{
	cryptoStats::mtx.lock();
		hashBits.push_back(hash);
		nonces.push_back(nonce);
	cryptoStats::mtx.unlock();
}

/* only used for testing */
int cryptoStats::getHashBits(int i) {
	return hashBits[i];
}

/* only used for testing */
int cryptoStats::getNonceFromList(int i) {
	return nonces[i];
}

/* only used for testing */
int cryptoStats::getValue(int hashBits, int vmIndex) {
	cryptoStatsValueMap * vm = fMap[hashBits];
	int value = vm->getValue(vmIndex);
	return value;
}

/* only used for testing */
int cryptoStats::getValueForNonce(int hashBits, int vmIndex) {
	cryptoStatsValueMap * vm = fMap[hashBits];
	int value = vm->getValueForNonce(vmIndex);
	return value;
}

int cryptoStats::getNonce(int hashBits) {
	int nextNonce = 0;
	
	cryptoStats::mtx.lock();
	{
		cryptoStatsValueMap * vm = fMap[hashBits];
		nextNonce = vm->getNext();
	}
	cryptoStats::mtx.unlock();
	
	return nextNonce;
}

void cryptoStats::resetStats()
{
	cryptoStats::mtx.lock(); 
	{
		cryptoStats::clearValueMaps();
		cryptoStats::fillValueMaps();
		cryptoStats::writeToFile();
	}
	cryptoStats::mtx.unlock();
}

void cryptoStats::buildHashNonceMaps()
{
	stats::mtx.lock();
	{
		cryptoStats::readFromFile();
		cryptoStats::createValueMaps();
		cryptoStats::fillValueMaps();
	}
	stats::mtx.unlock();
}

/* used for testing only */
void cryptoStats::buildHashNonceMaps( std::string file )
{
		cryptoStats::readFromFile( file );
		cryptoStats::createValueMaps();
		cryptoStats::fillValueMaps();
}

void cryptoStats::fillValueMaps() {
	
	// iterate over all hash / nonce pairs
	for (int i = 0; i < hashBits.size(); i++) {
		int h = hashBits[i];
		int n = nonces[i];
		// cryptoStatsValueMap vm = fMap[h];
		fMap[h]->addValue(n, 1);
	}

	for (int h = 0; h < numHashes; h++) {
		cryptoStatsValueMap * vm = fMap[h];
		vm->sortByValue();
		vm->resetNonce();
	}
}

void cryptoStats::clearValueMaps() {
	for (int i = 0; i<numHashes; i++) {
		cryptoStatsValueMap * vm = fMap[i];
		vm->resetValues();
	}
}

void cryptoStats::createValueMaps() {
	/* TODO incremental update */
	// create the empty data structure
	for (int i = 0; i<numHashes; i++) {
		cryptoStatsValueMap * vm = new cryptoStatsValueMap(numNonces);
		cryptoStats::fMap.push_back(vm);
	}
}

void cryptoStats::writeStats()
{
}

void cryptoStats::printStats() {
	float d = cryptoStats::ignoredValues + cryptoStats::savedValues;
	d = cryptoStats::savedValues * 100.0 / d;
	printer::inst()->print_msg(L4, "SavedValues %f", d);
}


cryptoStats::~cryptoStats()
{
}

std::vector<std::string> split(const std::string &s, char delim) {
	std::stringstream ss(s);
	std::string item;
	std::vector<std::string> tokens;
	while (getline(ss, item, delim)) {
		tokens.push_back(item);
	}
	return tokens;
}


int cryptoStats::getProcessMemory() {
	return 0;
}




