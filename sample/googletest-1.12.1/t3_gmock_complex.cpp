#include <gtest/gtest.h>
#include <gmock/gmock.h>

namespace {
class cal {
  public:
    cal() = default;

    int get_value() const { return value_; }
    int get_value(const int&add) const { return value_ + add; }
    void set_value(const int&value) { value_ = value; }

  private:
    int value_ = 0;
};

class mock_cal : public cal {
  public:
    // zero param
    MOCK_CONST_METHOD0(get_value, int());
    // one param
    MOCK_CONST_METHOD1(get_value, int(const int& add));
    // one param
    MOCK_CONST_METHOD1(set_value, void(const int& value));
};
}

TEST(t3_gmock_complex, mock_function_test) {
  constexpr int magic_int_3 = 3;
  cal cal;
  cal.set_value(magic_int_3);
  EXPECT_EQ(cal.get_value(), magic_int_3);

  constexpr int magic_int_7 = 7;
  const mock_cal mock;
  // set return and check return, with zero param
  EXPECT_CALL(mock, get_value()).WillOnce(::testing::Return(magic_int_7));
  EXPECT_EQ(mock.get_value(), magic_int_7);

  // set return and check return, with one param
  EXPECT_CALL(mock, get_value(magic_int_7)).WillOnce(::testing::Return(magic_int_7));
  EXPECT_EQ(mock.get_value(magic_int_7), magic_int_7);

  // check param
  EXPECT_CALL(mock, set_value(magic_int_7));
  mock.set_value(magic_int_7); // if [set_value(magic_int_3)] will Failure
}
