//
// Created by shecannotsee on 23-12-25.
//

#include "global_test_set.h"

#include <dlfcn.h>
#include <sys/socket.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* global mock set */
static bool mock_fopen = false;
constexpr int mock_fopen_errno = 1;
enum class fopen_case_des : int {
  ret_nullptr,
  ret_FILE,
};
static fopen_case_des fopen_case = fopen_case_des::ret_nullptr;
/* fopen mock set */
typedef FILE* (*fopen_func_t)(
  const char *__restrict __filename,
  const char *__restrict __modes);
/* The real function address function */
fopen_func_t fopen_func = reinterpret_cast<fopen_func_t>(dlsym(RTLD_NEXT,"fopen"));
/* fopen mock */
extern "C" FILE* fopen(const char *__restrict __filename,
                       const char *__restrict __modes) {
  if (mock_fopen) {
    if (fopen_case == fopen_case_des::ret_nullptr) {
      return nullptr;
    } else if (fopen_case == fopen_case_des::ret_FILE) {
      return new FILE;
    } else {
      return nullptr;
    }
  } else {
    return fopen_func(__filename, __modes);
  }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// extern int fclose (FILE *__stream);
/* global mock set */
static bool mock_fclose = false;
constexpr int mock_fclose_errno = 1;
enum class fclose_case_des : int {
  ret_0,
  ret_1,
};
static fclose_case_des fclose_case = fclose_case_des::ret_0;
/* fclose mock set */
typedef int (*fclose_func_t)(FILE *__stream);
/* The real function address function */
fclose_func_t fclose_func = reinterpret_cast<fclose_func_t>(dlsym(RTLD_NEXT,"fclose"));
/* fopen mock */
extern "C" int fclose(FILE *__stream) {
  if (mock_fclose) {
    if (fclose_case == fclose_case_des::ret_0) {
      return 0;
    } else if (fclose_case == fclose_case_des::ret_1) {
      return 1;
    } else {
      return 0;
    }
  } else {
    return fclose_func(__stream);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int test_function_with_system_interface() {
  // file pathty
  const std::string file_path = "../README.md";

  // open file
  FILE* file_handle = fopen(file_path.c_str(), "r");
  if (file_handle == nullptr) {
    return -1;
  }

  // close file
  if (fclose(file_handle) != 0) {
    return -2;
  }

  return 0;
}

TEST(t4_system_interface_mock, linux_system_interface) {
  mock_fopen = true;
  mock_fclose = true;

  fopen_case = fopen_case_des::ret_nullptr;
  fclose_case = fclose_case_des::ret_0;
  EXPECT_EQ(test_function_with_system_interface(), -1);
  fopen_case = fopen_case_des::ret_FILE;
  fclose_case = fclose_case_des::ret_0;
  EXPECT_EQ(test_function_with_system_interface(), 0);

  fopen_case = fopen_case_des::ret_FILE;
  fclose_case = fclose_case_des::ret_1;
  EXPECT_EQ(test_function_with_system_interface(), -2);

  mock_fopen = false; // close mock fopen
  mock_fclose = false; // close mock fclose
}

TEST(t4_system_interface_mock, std_interface) {

}
