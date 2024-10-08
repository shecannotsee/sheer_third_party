//
// Created by shecannotsee on 23-10-9.
//

#include "chat_window.h"
#include <QHBoxLayout>
#include <QShortcut>
#include <QKeyEvent>
#include <QDesktopWidget>
#include <iostream>

namespace t3_chat_window_test {

ChatWidget::ChatWidget(QWidget *parent) : QWidget(parent) {
  setupUI();
}

void ChatWidget::sendMessage() {
  QString message = inputTextEdit->toPlainText();
  if (!message.isEmpty()) {
    // 在消息框中显示自己发送的消息
    displayMessage("You: " + message);

    // 在实际应用中，这里应该将消息发送给其他人或服务器
    // 在这个示例中，只是清空输入框以模拟发送消息
    inputTextEdit->clear();
  }
}

void ChatWidget::setupUI() {
  QVBoxLayout *mainLayout = new QVBoxLayout(this);

  chatTextEdit = std::make_unique<QTextEdit>(this);
  chatTextEdit->setReadOnly(true);
  chatTextEdit->setStyleSheet("background-color: #f2f2f2; border: 1px solid #ccc; padding: 10px;");
  mainLayout->addWidget(chatTextEdit.get());

  inputTextEdit = std::make_unique<QTextEdit>(this);
  inputTextEdit->setStyleSheet("background-color: #ffffff; border: 1px solid #ccc; padding: 10px;");
  mainLayout->addWidget(inputTextEdit.get());

  QPushButton *sendButton = new QPushButton("send message", this);
  sendButton->setIcon(QIcon(":/icons/send.png"));
  sendButton->setStyleSheet("background-color: #0078d4; color: #fff; border: none; padding: 10px;");
  mainLayout->addWidget(sendButton);

  connect(sendButton, &QPushButton::clicked, this, &ChatWidget::sendMessage);

  setLayout(mainLayout);
  setWindowTitle("chat window");

  // 设置默认焦点为输入文本框
  inputTextEdit->setFocus();

  // 设置窗口的默认大小适配人类的习惯
  setMinimumSize(400, 300); // 设置最小大小
  resize(800, 600); // 设置默认大小

  // 让窗口居中
  QDesktopWidget* desktopWidget = QApplication::desktop();
  // 获取第二个屏幕的信息
  int secondScreenIndex = 1;  // 1 表示第二个屏幕
  QRect secondScreenRect = desktopWidget->screenGeometry(secondScreenIndex);

  // 计算窗口在第二个屏幕中央的位置
  int x = secondScreenRect.x() + (secondScreenRect.width() - width()) / 2;
  int y = secondScreenRect.y() + (secondScreenRect.height() - height()) / 2;

  // 移动窗口到第二个屏幕的中央
  move(x, y);

  // 允许用户调节窗口大小
  setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}



void ChatWidget::displayMessage(const QString &message) {
  chatTextEdit->append(message);
}


} // t3_chat_window_test
