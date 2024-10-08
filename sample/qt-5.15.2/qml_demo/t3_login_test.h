//
// Created by shecannotsee on 23-10-8.
//

#ifndef QML_DEMO_T3_LOGIN_TEST_H
#define QML_DEMO_T3_LOGIN_TEST_H

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "other_class/login.h"

namespace t3_login_test {

int main(int argc, char* argv[]) {
  QGuiApplication app(argc, argv);

  QQmlApplicationEngine engine;

  // 创建登录处理器对象
  login loginHandler(&engine);

  // 将登录处理器对象注册到 QML 上下文中
  engine.rootContext()->setContextProperty("loginHandler", &loginHandler);

  // 加载 QML 文件
  engine.load(QUrl(QStringLiteral("../qml_resources/t3_login.qml")));

  if (engine.rootObjects().isEmpty()) {
    return -1;
  }

  return app.exec();
}

}// namespace t3_login_test

#endif //QML_DEMO_T3_LOGIN_TEST_H
