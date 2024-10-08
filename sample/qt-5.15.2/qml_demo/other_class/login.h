//
// Created by shecannotsee on 23-10-8.
//

#ifndef QML_DEMO_LOGIN_H
#define QML_DEMO_LOGIN_H

#include <QObject>
#include <QQmlApplicationEngine>

namespace t3_login_test {

class login : public QObject
{
  Q_OBJECT
 public:
  explicit login(QQmlApplicationEngine* e ,QObject *parent = nullptr);
  QQmlApplicationEngine* engine;

 public slots:
  bool validateLogin(const QString &username, const QString &password);
  bool validateLogin(const std::string &username, const std::string &password);



};

} // t3_login_test

#endif //QML_DEMO_LOGIN_H
