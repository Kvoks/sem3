#include "../STL/stl.h"
#include "../gtest/gtest.h"
TEST(test_add, can_add_test) {
	// Arrange
	int x = 6, y = -5;
	// Act
	int res = add(x, y);
	// Assert
	EXPECT_EQ(res, 1);
}