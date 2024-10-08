import QtQuick 2.15
import QtQuick.Controls 2.15

// window containing the application
ApplicationWindow {
    id: manage_window
    // Content Area

    visible: MANAGE_SHOW
    // title of the application
    title: qsTr("Hello World")
    width: 640
    height: 480

    // a button in the middle of the content area
    Button {
        text: qsTr("Hello World")
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
    }

    // menu containing two menu items
    menuBar: MenuBar {
        Menu {
            title: qsTr("File")

            MenuItem {
                text: qsTr("&Open")
                onTriggered: console.log("Open action triggered")
            }

            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit()
            }

        }

    }

}

