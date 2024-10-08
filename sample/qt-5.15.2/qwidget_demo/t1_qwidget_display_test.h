//
// Created by shecannotsee on 23-10-7.
//

#ifndef QML_DEMO_T1_QML_DISPLAY_TEST_H
#define QML_DEMO_T1_QML_DISPLAY_TEST_H

#include <QApplication>
#include <QWidget>

namespace t1_qwidget_display_test {

int main(int argc,char* argv[]) {
  QApplication app(argc, argv);

  // 创建一个QWidget窗口
  QWidget window;
  window.setWindowTitle("我的第一个窗口"); // 设置窗口标题
  window.resize(400, 300); // 设置窗口大小

  window.show(); // 显示窗口

  return app.exec(); // 进入Qt应用程序主循环
}

}// namespace t1_qml_display_test

#endif //QML_DEMO_T1_QML_DISPLAY_TEST_H
