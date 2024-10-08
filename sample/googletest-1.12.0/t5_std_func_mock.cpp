//
// Created by shecannotsee on 23-12-25.
//

#include "global_test_set.h"

namespace {
// Mock std::vector
template<typename T>
class MockVector : public std::vector<T> {
public:
  MOCK_CONST_METHOD0(size, size_t());
};
}

TEST(t5_std_func_mock, vector_size_func_mock) {
  constexpr int real_size = 10;
  constexpr int not_real_size = 100;
  MockVector<int> int_list;
  int_list.reserve(real_size);
  for (int i = 0; i < real_size; ++i) {
      int_list.emplace_back(i);
  }
  // set mock
  EXPECT_CALL(int_list, size()).WillOnce(testing::Return(not_real_size));
  // get mock result
  EXPECT_EQ(int_list.size(), not_real_size);
}
