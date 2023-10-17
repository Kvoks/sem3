#include "../TMatrix/matrix.h"
#include "../gtest/gtest.h"

TEST(TVector, can_create_vector_with_positive_length) {
  ASSERT_NO_THROW(TVector<int> v(5));
}

TEST(TVector, cant_create_too_large_vector) {
  ASSERT_ANY_THROW(TVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TVector, throws_when_create_vector_with_negative_length) {
	ASSERT_ANY_THROW(TVector<int> v(-5));
}

TEST(TVector, can_create_copied_vector) {
	std::string mass_str[5] = { "16543", "7234", "274", "274", "2645" };
	TVector<std::string> v(mass_str, 5);
	ASSERT_NO_THROW(TVector<std::string> v2(v));
}

TEST(TVector, copied_vector_is_equal_to_source_one) {
	std::string mass_str[5] = { "16543", "7234", "274", "274", "2645" };
	TVector<std::string> v(mass_str, 5);
	TVector<std::string> v2(v);
	EXPECT_EQ(v, v2);
}

TEST(TVector, copied_vector_has_its_own_memory) {
	std::string mass_str[5] = { "16543", "7234", "274", "274", "2645" };
	TVector<std::string> v(mass_str, 5);
	TVector<std::string> v2(v);
	EXPECT_NE(&v, &v2);
}

TEST(TVector, can_get_pMem_element) {
	TVector<int> v(5);
	ASSERT_NO_THROW(v[3]);
}

TEST(TVector, can_get_size) {
  TVector<int> v(4);

  EXPECT_EQ(4, v.size());
}

TEST(TVector, can_set_and_get_element) {
  TVector<int> v(4);
  v[0] = 4;

  EXPECT_EQ(4, v[0]);
}

TEST(TVector, throws_when_set_element_with_negative_index) {
	int l[5] = { 1,2,3,4,5};
	TVector<int> v(l, 6);
	ASSERT_ANY_THROW(int f = v.at(-5));
}

TEST(TVector, throws_when_set_element_with_too_large_index) {
	int l[5] = { 1,2,3,4,5 };
	TVector<int> v(l, 6);
	ASSERT_ANY_THROW(int f = v.at(55));
}

TEST(TVector, can_assign_vector_to_itself) {
	int l[5] = { 1,2,3,4,5 };
	TVector<int> v(l, 6);
	ASSERT_NO_THROW(v = v);
}

TEST(TVector, can_assign_vectors_of_equal_size) {
	int l[5] = { 1,2,3,4,5 };
	int l1[5] = { 5,6,7,8,9	};
	TVector<int> v(l, 6);
	TVector<int> v1(l1,6);
	ASSERT_NO_THROW(v = v1);
	EXPECT_EQ(v = v1, v1);
}

TEST(TVector, assign_operator_change_vector_size) {
	int l[5] = { 1,2,3,4,5 };
	int l1[6] = { 4,5,6,7,8,9 };
	TVector<int> v(l, 5);
	TVector<int> v1(l1, 6);
	v = v1;
	EXPECT_EQ(v.size(), 6);
}

TEST(TVector, can_assign_vectors_of_different_size) {
	int l[5] = { 1,2,3,4,5 };
	int l1[6] = { 4,5,6,7,8,9 };
	TVector<int> v(l, 5);
	TVector<int> v1(l1, 6);
	ASSERT_NO_THROW(v = v1);
	EXPECT_EQ(v.size(), 6);
}

TEST(TVector, compare_equal_vectors_return_true) {
	int l[5] = { 1,2,3,4,5 };
	int l1[5] = { 1,2,3,4,5 };
	TVector<int> v(l, 5);
	TVector<int> v1(l1, 5);
	EXPECT_EQ(v==v1, true);
}

TEST(TVector, compare_vector_with_itself_return_true) {
	int l[5] = { 1,2,3,4,5 };
	TVector<int> v(l, 5);
	EXPECT_EQ(v == v, true);
}

TEST(TVector, vectors_with_different_size_are_not_equal) {
	int l[5] = { 1,2,3,4,5 };
	int l1[6] = { 4,5,6,7,8,9 };
	TVector<int> v(l, 5);
	TVector<int> v1(l1, 6);
	EXPECT_NE(v, v1);
}

TEST(TVector, can_add_scalar_to_vector) {
	int l[5] = { 1,2,3,4,5 };
	int l1[5] = { 4,5,6,7,8 };
	TVector<int> v(l, 5);
	TVector<int> v1(l1, 5);
	int s = 3;
	v = v + s;
	EXPECT_EQ(v, v1);
}

TEST(TVector, can_subtract_scalar_from_vector) {
	int l[5] = { 1,2,3,4,5 };
	int l1[5] = { 4,5,6,7,8 };
	TVector<int> v(l, 5);
	TVector<int> v1(l1, 5);
	int s = 3;
	v1 = v1 - s;
	EXPECT_EQ(v1, v);
}

TEST(TVector, can_multiply_scalar_by_vector) {
	int l[5] = { 1,2,3,4,5 };
	int l1[5] = { 2,4,6,8,10 };
	TVector<int> v(l, 5);
	TVector<int> v1(l1, 5);
	int s = 2;
	v = v * s;
	EXPECT_EQ(v, v1);
}

TEST(TVector, can_add_vectors_with_equal_size) {
	int l[5] = { 1,2,3,4,5 };
	int l1[5] = { 4,5,6,7,8 };
	int l2[5] = { 3,3,3,3,3 };
	TVector<int> v(l, 5);
	TVector<int> v1(l1, 5);
	TVector<int> v2(l2, 5);
	v = v + v2;
	EXPECT_EQ(v, v1);
}

TEST(TVector, cant_add_vectors_with_not_equal_size) {
	int l[5] = { 1,2,3,4,5 };
	int l1[6] = { 4,5,6,7,8,3 };
	int l2[6] = { 3,3,3,3,3,3 };
	TVector<int> v(l, 5);
	TVector<int> v1(l1, 6);
	TVector<int> v2(l2, 6);
	ASSERT_ANY_THROW(v + v2);
}

TEST(TVector, can_subtract_vectors_with_equal_size) {
	int l[5] = { 1,2,3,4,5 };
	int l1[5] = { 4,5,6,7,8 };
	int l2[5] = { 3,3,3,3,3 };
	TVector<int> v(l, 5);
	TVector<int> v1(l1, 5);
	TVector<int> v2(l2, 5);
	v1 = v1 - v2;
	EXPECT_EQ(v1, v);
}
TEST(TVector, cant_subtract_vectors_with_not_equal_size) {
	int l[5] = { 1,2,3,4,5 };
	int l1[6] = { 4,5,6,7,8,9 };
	int l2[5] = { 3,3,3,3,3 };
	TVector<int> v(l, 5);
	TVector<int> v1(l1, 6);
	TVector<int> v2(l2, 5);
	ASSERT_ANY_THROW(v1 - v2);
}

TEST(TVector, can_multiply_vectors_with_equal_size) {
	int l[5] = { 1,2,3,4,5 };
	int l1[5] = { 3,6,9,12,15 };
	int l2[5] = { 3,3,3,3,3 };
	TVector<int> v(l, 5);
	TVector<int> v1(l1, 5);
	TVector<int> v2(l2, 5);
	int s = 0,s1=45;
	s = v * v2;
	EXPECT_EQ(s, s1);
}

TEST(TVector, cant_multiply_vectors_with_not_equal_size) {
	int l[5] = { 4, 6 , 4, 45, 5 };
	int l1[8] = { 12, 14 , 12, 53, 13, 14, 15, 16 };
	TVector<int> v(l, 5);
	TVector<int> v2(l1, 8);
	ASSERT_ANY_THROW(v * v2);
}