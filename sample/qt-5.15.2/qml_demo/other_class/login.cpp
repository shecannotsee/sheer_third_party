//
// Created by shecannotsee on 23-10-8.
//

#include "login.h"
#include <string>
#include <iostream>
#include <QQmlContext>

namespace t3_login_test {

login::login(QQmlApplicationEngine* e, QObject *parent) : QObject(parent), engine(e) {

}

bool login::validateLogin(const QString &username, const QString &password) {
  return this->validateLogin(username.toStdString(),password.toStdString());
}

bool login::validateLogin(const std::string &username, const std::string &password) {
  if (username == "admin" && password == "123456") {
    std::cout << "pass" <<std::endl;
    // 修改全局变量!完成显示!
    engine->rootContext()->setContextProperty("MANAGE_SHOW", true);
    return true;
  } else {
    std::cout << "not pass" <<std::endl;
    return false;
  }
}

} // t3_login_test