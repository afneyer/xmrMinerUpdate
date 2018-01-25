#include "pch.h"
#include "../xmrstak/afn/cryptoStats.h"
#include "../xmrstak/misc/console.hpp"
#include "../xmrstak/afn/stats.h"
#include "cryptoStatsTests.h"

TEST(TestCryptoStats, readFromFile1) {

	// read the input file
	std::string filePathName = "../../tests/testData/hashNonceList01.txt";
	cryptoStats::readFromFile( filePathName );
	
	/* validate vectors hashBits and nonces */
	EXPECT_EQ(12, cryptoStats::getHashBits(0) );
	EXPECT_EQ(34, cryptoStats::getHashBits(1));
	EXPECT_EQ(45, cryptoStats::getHashBits(2));
	EXPECT_EQ(56, cryptoStats::getNonceFromList(0));
	EXPECT_EQ(72, cryptoStats::getNonceFromList(1));
	EXPECT_EQ(11, cryptoStats::getNonceFromList(2));
}

TEST(TestCryptoStats, writeToFile) {

	std::string filePathName = "../../tests/testData/hashNonceList01.txt";
	cryptoStats::readFromFile(filePathName);

	filePathName = "../../tests/testOutput/hashNonceList01.txt";
	cryptoStats::writeToFile(filePathName);
	cryptoStats::readFromFile(filePathName);

	/* validate vectors hashBits and nonces */
	EXPECT_EQ(12, cryptoStats::getHashBits(0));
	EXPECT_EQ(34, cryptoStats::getHashBits(1));
	EXPECT_EQ(45, cryptoStats::getHashBits(2));
	EXPECT_EQ(56, cryptoStats::getNonceFromList(0));
	EXPECT_EQ(72, cryptoStats::getNonceFromList(1));
	EXPECT_EQ(11, cryptoStats::getNonceFromList(2));
}

TEST(TestCryptoStats, getNonce) {
	
	std::string filePathName = "../../tests/testData/hashNonceList02.txt";
	cryptoStats::readFromFile(filePathName);
	cryptoStats::buildHashNonceMaps(filePathName);
	EXPECT_EQ(6, cryptoStats::getNonce(1));
	EXPECT_EQ(5, cryptoStats::getNonce(1));
	EXPECT_EQ(4, cryptoStats::getNonce(1));
	EXPECT_EQ(0, cryptoStats::getNonce(1));
	EXPECT_EQ(1, cryptoStats::getNonce(1));
	EXPECT_EQ(2, cryptoStats::getNonce(1));
	EXPECT_EQ(3, cryptoStats::getNonce(1));
	EXPECT_EQ(7, cryptoStats::getNonce(1));
	EXPECT_EQ(8, cryptoStats::getNonce(1));
	
	for (int i = 10; i <= cryptoStats::numNonces-2; i++) {
		cryptoStats::getNonce(1);
	}

	EXPECT_EQ(cryptoStats::numNonces -2, cryptoStats::getNonce(1));
	EXPECT_EQ(cryptoStats::numNonces -1, cryptoStats::getNonce(1));
	EXPECT_EQ(cryptoStats::numNonces +0 , cryptoStats::getNonce(1));
	EXPECT_EQ(cryptoStats::numNonces +1, cryptoStats::getNonce(1));
	EXPECT_EQ(cryptoStats::numNonces +2, cryptoStats::getNonce(1));
	
	EXPECT_EQ(1, cryptoStats::getNonce(2));
	EXPECT_EQ(2, cryptoStats::getNonce(2));
	EXPECT_EQ(0, cryptoStats::getNonce(2));

	EXPECT_EQ(0, cryptoStats::getNonce(500));
	EXPECT_EQ(0, cryptoStats::getNonce(700));
	EXPECT_EQ(0, cryptoStats::getNonce(1000));
	EXPECT_EQ(0, cryptoStats::getNonce(99));
}

TEST(TestCryptoStats, readFromFile2) {

	// read the input file
	std::string filePathName = "../../tests/testData/hashNonceList03.txt";
	

	cryptoStats::readFromFile(filePathName);
	cryptoStats::printStats();
	for (int i = 0; i < 1000; i++) {
		for (int j = 0; j < 1000; j++) {
			cryptoStats::addPoint(i % cryptoStats::numHashes, j % cryptoStats::numNonces);
		}
	}

	cryptoStats::buildHashNonceMaps( filePathName );
	

	EXPECT_TRUE(true);
}

TEST(TestCryptoStats, resetStats) {

	std::string filePathName = "../../tests/testData/hashNonceList02.txt";
	cryptoStats::readFromFile(filePathName);
	cryptoStats::buildHashNonceMaps( filePathName );
	
	EXPECT_EQ(cryptoStats::getValue(1, 1), 3);
	EXPECT_EQ(cryptoStats::getValueForNonce(1, 6), 3);

	cryptoStats::clearValueMaps();

	for (int i = 0; i < cryptoStats::numHashBits; i++) {
		for (int j=0; j<cryptoStats::numNonces; j++) {
			EXPECT_EQ(cryptoStats::getValue(0, 0), 0);
		}
	}
	cryptoStats::resetStats();
}

