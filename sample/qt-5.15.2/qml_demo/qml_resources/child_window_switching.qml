import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12

ApplicationWindow {
    visible: true
    width: 480
    height: 360
    title: qsTr("TabBar工具栏")

    SwipeView {
        id: view

        currentIndex: tabBar.currentIndex
        anchors.fill: parent
        onCurrentIndexChanged: {
            tabBar.currentIndex = currentIndex;
            indicator.currentIndex = currentIndex;
        }

        //第一页
        Image {
            id: firstPage

            smooth: true
            mipmap: true
            antialiasing: true
            fillMode: Image.PreserveAspectFit
            sourceSize.height: height
            source: "cat.jpg"
        }

        //第二页
        Image {
            id: secondPage

            smooth: true
            mipmap: true
            antialiasing: true
            fillMode: Image.PreserveAspectFit
            sourceSize.height: height
            source: "cat.jpg"
        }

        //第三页
        Image {
            id: thirdPage

            smooth: true
            mipmap: true
            antialiasing: true
            fillMode: Image.PreserveAspectFit
            sourceSize.height: height
            source: "cat.jpg"
        }

    }

    PageIndicator {
        id: indicator

        count: view.count
        anchors.bottom: view.bottom
        anchors.horizontalCenter: parent.horizontalCenter
    }

    ///--1. ApplicationWindow 中才有 header
    ///--2. QtQuick.Controls 2.0 版本后才有header
    ///--3. TabBar不一定要用在header中
    header: TabBar {
        id: tabBar

        TabButton {
            text: qsTr("我是目录1")
        }

        TabButton {
            text: qsTr("我是目录2")
        }

        TabButton {
            text: qsTr("我是目录3")
        }

    }

}
