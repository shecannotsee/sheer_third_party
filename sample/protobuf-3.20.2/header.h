//
// Created by pc on 2022/10/21.
//

#ifndef PROTOBUF_TEST_PROROBUF_TEST_HEADER_H_
#define PROTOBUF_TEST_PROROBUF_TEST_HEADER_H_

#include <iostream>
#include <string>
#include "protobuf/people.pb.h"

namespace method1 {
void main() {
  // Serialization
  school::people Jerry;
  Jerry.set_name("Jerry");
  Jerry.set_age(15);
  Jerry.set_scores(686);
  std::string buff;
  Jerry.SerializeToString(&buff);

  // parse
  school::people Jerry_father;
  if (!Jerry_father.ParseFromString(buff))
    std::cout<<"parse error.\n";

  std::cout<<"Jerry_father's want to know Jerry's name   is :"<<Jerry_father.name()   <<std::endl;
  std::cout<<"Jerry_father's want to know Jerry's age    is :"<<Jerry_father.age()    <<std::endl;
  std::cout<<"Jerry_father's want to know Jerry's scores is :"<<Jerry_father.scores() <<std::endl;


};
};// namespace method1

#endif //PROTOBUF_TEST_PROROBUF_TEST_HEADER_H_
