//
// Created by shecannotsee on 23-10-9.
//

#ifndef QWIDGET_DEMO_T3_CHAT_WINDOW_TEST_H
#define QWIDGET_DEMO_T3_CHAT_WINDOW_TEST_H

#include "other_class/chat_window.h"

namespace t3_chat_window_test {

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);

  ChatWidget chatWidget;
  chatWidget.show();

  return app.exec();
}

}// namespace t3_chat_window_test

#endif //QWIDGET_DEMO_T3_CHAT_WINDOW_TEST_H
