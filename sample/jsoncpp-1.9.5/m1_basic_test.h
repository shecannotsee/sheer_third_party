//
// Created by shecannotsee on 2023/3/21.
//

#ifndef GOOGLETEST_TEST_JSONCPP_TEST_M1_BASIC_TEST_H_
#define GOOGLETEST_TEST_JSONCPP_TEST_M1_BASIC_TEST_H_

#include <iostream>
#include <memory>

#include <json/json.h>

namespace m1_basic_test {

bool fromJson(Json::Value &value) {
  return false;
};

int main() {
  std::string str = "{\"123\":{}}";
  Json::Value root;
  JSONCPP_STRING errs;
  Json::CharReaderBuilder build;

  std::unique_ptr<Json::CharReader> const jsonReader(build.newCharReader());
  bool jsonRet = jsonReader->parse(str.c_str(), str.c_str() + str.length(),
                                   &root, &errs);
  if ((jsonRet != true) || (errs.size() != 0)) {
    std::cout << __LINE__ << std::endl;
    return false;
  }

  if (!root["123"].isObject()) {
    std::cout << __LINE__ << std::endl;
  }

  if (!fromJson(root["123"])) {
    std::cout << __LINE__ << std::endl;
    return false;
  }

  return 0;
}

};// namespace m1_basic_test

#endif //GOOGLETEST_TEST_JSONCPP_TEST_M1_BASIC_TEST_H_
