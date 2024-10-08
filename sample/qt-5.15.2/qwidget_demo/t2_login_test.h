//
// Created by shecannotsee on 23-10-9.
//

#ifndef QWIDGET_DEMO_T2_LOGIN_TEST_H
#define QWIDGET_DEMO_T2_LOGIN_TEST_H

#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>

namespace t2_login_test {

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);

  // 创建一个QWidget窗口
  QWidget window;
  window.setWindowTitle("登录界面"); // 设置窗口标题
  window.resize(400, 200); // 设置窗口大小

  // manage page
  QWidget manage_page;
  manage_page.setWindowTitle("manage_page"); // 设置窗口标题
  manage_page.resize(400, 300); // 设置窗口大小

  // 创建垂直布局管理器
  QVBoxLayout *layout = new QVBoxLayout(&window);

  // 创建用户名和密码的水平布局
  QHBoxLayout *usernameLayout = new QHBoxLayout;
  QLabel *usernameLabel = new QLabel("用户名:");
  QLineEdit *usernameInput = new QLineEdit;
  usernameLayout->addWidget(usernameLabel);
  usernameLayout->addWidget(usernameInput);

  QHBoxLayout *passwordLayout = new QHBoxLayout;
  QLabel *passwordLabel = new QLabel("密码:");
  QLineEdit *passwordInput = new QLineEdit;
  passwordInput->setEchoMode(QLineEdit::Password);
  passwordLayout->addWidget(passwordLabel);
  passwordLayout->addWidget(passwordInput);

  // 创建登录按钮
  QPushButton *loginButton = new QPushButton("登录");

  // 添加控件到布局
  layout->addLayout(usernameLayout);
  layout->addLayout(passwordLayout);
  layout->addWidget(loginButton);

  // 连接登录按钮的点击事件到槽函数
  QObject::connect(loginButton, &QPushButton::clicked, [&]() {
    QString username = usernameInput->text();
    QString password = passwordInput->text();

    // 在这里进行登录逻辑的处理，例如验证用户名和密码

    if (username == "admin" && password == "123456") {
      // 登录成功，可以执行相应操作
      window.hide();
      manage_page.show();
    } else {
      // 登录失败，可以显示错误消息
      QMessageBox::warning(&window, "登录失败", "用户名或密码不正确");
    }
  });

  window.show(); // 显示窗口

  return app.exec(); // 进入Qt应用程序主循环
}

}// namespace t2_login_test

#endif //QWIDGET_DEMO_T2_LOGIN_TEST_H
