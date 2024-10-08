//
// Created by shecannotsee on 23-10-8.
//

#ifndef QML_DEMO_T4_MORE_QML_WINDOWS_SWITCH_TEST_H
#define QML_DEMO_T4_MORE_QML_WINDOWS_SWITCH_TEST_H

#include <thread>
#include <unistd.h>
#include "other_class/login.h"

namespace t4_more_qml_windows_switch_test {

int main(int argc, char* argv[]) {
  QGuiApplication app(argc, argv);

  QQmlApplicationEngine engine;

  // 创建登录处理器对象
  t3_login_test::login loginHandler(&engine);

  // 将登录处理器对象注册到 QML 上下文中
  engine.rootContext()->setContextProperty("loginHandler", &loginHandler);
  engine.rootContext()->setContextProperty("MANAGE_SHOW", false);


  // 加载 QML 文件
  engine.load(QUrl(QStringLiteral("../qml_resources/t4_login.qml")));
  engine.load(QUrl(QStringLiteral("../qml_resources/t4_manage_window.qml")));

  if (engine.rootObjects().isEmpty()) {
    return -1;
  }

  return app.exec();
}

}// namespace t4_more_qml_windows_switch_test

#endif //QML_DEMO_T4_MORE_QML_WINDOWS_SWITCH_TEST_H
