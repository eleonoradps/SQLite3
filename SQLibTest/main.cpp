#include <gtest/gtest.h>
#include "SQLibTest.h"

int main(int ac, char** av) {
	testing::InitGoogleTest(&ac, av);
	return RUN_ALL_TESTS();
}