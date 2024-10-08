import QtQuick 2.15
import QtQuick.Controls 2.15


ApplicationWindow {
    id: root
    visible: true
    width: 400
    height: 200
    title: "PUSSY"
    color: "white"

    Rectangle {
        id: rectangle
        width: 108
        height: 108
        color: "#a6a241"

        Image {
            id: cat
            // reference the parent
            x: 4
            y: 4
            width: 100
            height: 100
            source: "cat.jpg"
        }

        Text {
            id: meow
            x: rectangle.x + rectangle.width + 2
            y: cat.y
            text: 'meow meow'
            color: "#000000"
        }

    }

}