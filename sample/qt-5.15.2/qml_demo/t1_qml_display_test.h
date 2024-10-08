//
// Created by shecannotsee on 23-10-7.
//

#ifndef QML_DEMO_T1_QML_DISPLAY_TEST_H
#define QML_DEMO_T1_QML_DISPLAY_TEST_H

#include <QGuiApplication>
#include <QQmlApplicationEngine>

namespace t1_qml_display_test {

int main(int argc,char* argv[]) {
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QGuiApplication app(argc, argv);

  QQmlApplicationEngine engine;
  engine.load(QUrl(QStringLiteral("../qml_resources/t1.qml")));
  if (engine.rootObjects().isEmpty()) {
    return -1;
  }

  return app.exec();
}

}// namespace t1_qml_display_test

#endif //QML_DEMO_T1_QML_DISPLAY_TEST_H
