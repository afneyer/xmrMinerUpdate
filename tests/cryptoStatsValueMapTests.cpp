#include "pch.h"
#include "gtest/gtest.h"
#include "../xmrstak/afn/cryptoStatsValueMap.h"
#include "../xmrstak/afn/cryptoStats.h"

TEST(cryptoStatsValueMap, create) {
	
	cryptoStatsValueMap v1 = cryptoStatsValueMap(4);
	v1.addValue(0, 5);
	v1.addValue(1, 3);
	v1.addValue(2, 9);

	v1.printMap(5);

	v1.sortByValue();

	v1.printMap(5);

	EXPECT_EQ(v1.getNext(), 2);
	EXPECT_EQ(v1.getNext(), 0);
	EXPECT_EQ(v1.getNext(), 1);
	EXPECT_EQ(v1.getNext(), 3);
	EXPECT_EQ(v1.getNext(), 4);

}

TEST(crptoStatsValueMap, memoryTest) {

	cryptoStatsValueMap v1 = cryptoStatsValueMap(4);
	for (int i = 0; i < 100000; i++) {
		v1.addValue(0, 1);
		v1.addValue(1, 1);
		v1.addValue(2, 1);
		v1.addValue(3, 1);
	}
}