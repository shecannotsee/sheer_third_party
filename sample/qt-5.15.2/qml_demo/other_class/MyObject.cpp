//
// Created by shecannotsee on 23-10-7.
//

#include <iostream>
#include "MyObject.h"

namespace t2_event_test {

MyObject::MyObject(QObject *parent) : QObject(parent) {

}

void MyObject::handleButtonClick() {
  std::cout << "Button triggered" << std::endl;
}

} // t2_event_test