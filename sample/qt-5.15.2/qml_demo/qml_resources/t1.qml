import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    visible: true
    width: 400
    height: 200
    title: "My QML App"

    Rectangle {
        anchors.fill: parent
        color: "lightblue"

        Text {
            anchors.centerIn: parent
            text: "Hello, QML!"
            font.pixelSize: 24
        }
    }
}
