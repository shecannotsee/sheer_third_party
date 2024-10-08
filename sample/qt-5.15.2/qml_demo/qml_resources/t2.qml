import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    visible: true
    width: 400
    height: 200
    title: "Button with C++ Response"

    Rectangle {
        color: "lightblue"
        anchors.fill: parent

        Button {
            text: "Click me"
            anchors.centerIn: parent
            onClicked: {
                myObject.handleButtonClick(); // 调用C++槽函数
            }
        }

    }

}
