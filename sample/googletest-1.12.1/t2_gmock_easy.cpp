#include <gtest/gtest.h>
#include <gmock/gmock.h>

namespace {
class function {
  public:
    virtual int get_number_8() const = 0;

    virtual void do_this(int n) = 0;
};

class mock_function : public function {
  public:
    MOCK_METHOD(int, get_number_8, (), (const, override));
    MOCK_METHOD(void, do_this, (int n), (override));
};
}

TEST(t2_gmock_easy, function_test) {
  mock_function temp;/* set action */ {
    EXPECT_CALL(temp, get_number_8())
      .WillOnce(testing::Return(8));
  };

  EXPECT_EQ(8, temp.get_number_8());
}
