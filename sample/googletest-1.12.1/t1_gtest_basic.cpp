#include <gtest/gtest.h>
#include <gmock/gmock.h>

TEST(t1_gtest_basic, gtest_basic) {
  auto return_0 = []() { return 0; };
  auto return_9 = []() { return 9; };

  std::string intStr = std::to_string(101);
  std::string str = "100";
  // ASSERT_*：If it don't pass the test, exit the test suite
  // EXPECT_*：If it don't pass the test, continue testing
  /* string check */ {
    EXPECT_STREQ(intStr.c_str(), intStr.c_str()); // c style str, == and then pass the test
    EXPECT_STRNE(intStr.c_str(), str.c_str()); // c style str, != and then pass the test
  }
  /* number check */ {
    EXPECT_EQ(return_0(), return_0()); // ==, and then pass the test
    EXPECT_NE(return_0(), return_9()); // !=, and then pass the test
    EXPECT_LT(return_0(), return_9()); // p1 < p2, and then pass the test

    EXPECT_LE(return_0(), return_0()); // p1 <= p2, and then pass the test
    EXPECT_LE(return_0(), return_9()); // p1 <= p2, and then pass the test

    EXPECT_GT(return_9(), return_0()); // p1 > p2, and then pass the test

    EXPECT_GE(return_9(), return_9()); // p1 >= p2, and then pass the test
    EXPECT_GE(return_9(), return_0()); // p1 >= p2, and then pass the test
  }
  /* bool check */ {
    EXPECT_TRUE(true) << "EXPECT_TRUE(condition):want to condition is true"; // input true, and then pass the test
    EXPECT_FALSE(false); // input false, and then pass the test
  }

  /* Exit and Exception check */ {
    // exit example-1
    auto exit_with_success = []() {
      const char* exit_success_with_msg = "success";
      fprintf(stderr, exit_success_with_msg);
    };
    const std::string exit_success_with_msg = "success";
    EXPECT_EXIT(/* param 1 */[&](){atexit(exit_with_success);exit(0);}(),
                             /* param 2 */::testing::ExitedWithCode(0),
                             /* param 3 */exit_success_with_msg);

    // exit example-2
    auto exit_with_error = []() {
      const std::string exit_with_msg = "exit with 42";
      std::cerr << exit_with_msg << std::endl;
    };
    const std::string exit_with_msg = "exit with 42";
    EXPECT_EXIT(/* param 1 */[&](){atexit(exit_with_error);exit(42);}(),
                             /* param 2 */::testing::ExitedWithCode(42),
                             /* param 2 */exit_with_msg);

    // Exception example-1
    const std::string exception_msg = "error";
    auto throw_ex = [&]() {
      throw std::runtime_error(exception_msg);
    };
    EXPECT_THROW(throw_ex(), std::runtime_error);

    // Exception example-2
    try {
      throw_ex();
    }
    catch (const std::runtime_error&ex) {
      // check exception type
      EXPECT_THROW(throw_ex(), std::runtime_error);
      // check exception msg content
      EXPECT_EQ(ex.what(), exception_msg);
    } catch (...) {
      // other unexpected exception types
      FAIL() << "Expected std::runtime_error to be thrown.";
    }
  }
  /* ASSERT_* test */ {
    ASSERT_STREQ(intStr.c_str(), intStr.c_str());
    ASSERT_EQ(return_0(), return_0());
  }
}

namespace {
int add(int a, int b) {
  return a + b;
}
}

TEST(t1_gtest_basic, add_test) {
  EXPECT_EQ(add(1,2), 3);
  EXPECT_EQ(add(1,2), 3);
  EXPECT_EQ(add(3,4), 7);
  EXPECT_EQ(add(1,5), 6);
}
