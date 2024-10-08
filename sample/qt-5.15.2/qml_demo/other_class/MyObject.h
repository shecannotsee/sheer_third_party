//
// Created by shecannotsee on 23-10-7.
//

#ifndef QML_DEMO_MYOBJECT_H
#define QML_DEMO_MYOBJECT_H

#include <QObject>

namespace t2_event_test {

class MyObject : public QObject {
 Q_OBJECT
 public:
  explicit MyObject(QObject* parent = nullptr);

 public slots:
  void handleButtonClick();
};

} // t2_event_test

#endif //QML_DEMO_MYOBJECT_H
