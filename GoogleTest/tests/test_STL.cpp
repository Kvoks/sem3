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

TEST(test_division, can_div_test) {
	// Arrange
	int x = 6, y = -7;
	// Act
	float res = division(x, y), eps = 0.01;
	// Assert
	EXPECT_NEAR(res, -0.85, eps);
}
TEST(test_division, throw_when_try_div_by_zero_test) {
	// Arrange
	int x = 6, y = 0;
	// Act & Assert
	ASSERT_ANY_THROW(division(x, y));
}
TEST(test_division, positive_zero_after_div_zero_on_negative_value_test) {
	// Arrange
	int x = 0, y = -5;
	// Act
	float res = division(x, y);
	// Assert
	EXPECT_EQ(res, 0);
}