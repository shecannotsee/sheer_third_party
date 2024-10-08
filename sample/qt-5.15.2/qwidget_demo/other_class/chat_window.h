//
// Created by shecannotsee on 23-10-9.
//

#ifndef QWIDGET_DEMO_CHAT_WINDOW_H
#define QWIDGET_DEMO_CHAT_WINDOW_H

#include <memory>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QPushButton>

namespace t3_chat_window_test {

class ChatWidget : public QWidget
{
 Q_OBJECT

 public:
  explicit ChatWidget(QWidget *parent = nullptr);

 private slots:
  void sendMessage();

 private:
  void setupUI();

  void displayMessage(const QString &message);

  std::unique_ptr<QTextEdit> chatTextEdit;
  std::unique_ptr<QTextEdit> inputTextEdit;

};

} // t3_chat_window_test

#endif //QWIDGET_DEMO_CHAT_WINDOW_H
