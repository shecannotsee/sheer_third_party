//
// Created by shecannotsee on 23-10-7.
//

#ifndef QML_DEMO_T2_EVENT_TEST_H
#define QML_DEMO_T2_EVENT_TEST_H

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "other_class/MyObject.h"

namespace t2_event_test {

int main(int argc, char* argv[]) {
  QGuiApplication app(argc, argv);
  QQmlApplicationEngine engine;

  MyObject myObject;

  // 将C++对象添加到QML上下文
  engine.rootContext()->setContextProperty("myObject", &myObject);

  engine.load(QUrl(QStringLiteral("../qml_resources/t2.qml")));

  return app.exec();
}

}// namespace t2_event_test

#endif //QML_DEMO_T2_EVENT_TEST_H
