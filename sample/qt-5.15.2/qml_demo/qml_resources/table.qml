import QtQuick 2.13
import QtQuick.Controls 2.13
import Qt.labs.qmlmodels 1.0

Rectangle {
    width: 800
    height: 400

    Rectangle{
        id:header
        width: parent.width
        height: 30

        Row{
            spacing: 0

            Repeater{
                model: ["name","sex","id","option"]

                Rectangle{
                    width: {
                        var w = 0
                        switch(index){
                            case 0: w = 140;break;
                            case 1: w = 90;break;
                            case 2: w = 120;break;
                            case 3: w = 150;break;
                        }
                        return w
                    }
                    height: header.height
                    color: "#666666"
                    border.width: 1
                    border.color: "#848484"
                    Text {
                        text: modelData
                        anchors.centerIn: parent
                        font.pointSize: 12
                        color: "white"
                    }
                }
            }
        }
    }
    TableView{
        id:tableView
        width: parent.width
        anchors.top:header.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        clip: true
        boundsBehavior: Flickable.OvershootBounds


        ScrollBar.vertical: ScrollBar {
            anchors.right:parent.right
            anchors.rightMargin: 0
            visible: tableModel.rowCount > 5
            background: Rectangle{
                color:"#666666"
            }
            onActiveChanged: {
                active = true;
            }
            contentItem: Rectangle
                {
                implicitWidth  : 6
                implicitHeight : 30
                radius : 3
                color  : "#848484"
            }
        }

        model: TableModel {
            id:tableModel

            TableModelColumn{display: "name"}
            TableModelColumn{display: "sex"}
            TableModelColumn{display: "id"}
            TableModelColumn{display: "option"}

        }
        delegate:DelegateChooser{

            DelegateChoice{
                column: 0
                delegate: Rectangle{
                    color: "#666666"
                    implicitWidth: 140
                    implicitHeight: 32
                    border.width: 1
                    border.color: "#848484"

                    Text {
                        text: display
                        anchors.centerIn: parent
                        font.pointSize: 12
                        color: "blue"
                    }
                }
            }
            DelegateChoice{
                column: 1
                delegate: Rectangle{
                    color: "#666666"
                    implicitWidth: 90
                    implicitHeight: 32
                    border.width: 1
                    border.color: "#848484"

                    Text {
                        text: display
                        anchors.centerIn: parent
                        font.pointSize: 12
                        color: "white"
                    }
                }
            }
            DelegateChoice{
                column: 2
                delegate: Rectangle{
                    color: "#666666"
                    implicitWidth: 120
                    implicitHeight: 32
                    border.width: 1
                    border.color: "#848484"
                    clip: true

                    Text {
                        text: display
                        anchors.centerIn: parent
                        font.pointSize: 12
                        color: "white"
                    }
                }
            }
            DelegateChoice{
                column: 3
                delegate: Rectangle{
                    color: "#666666"
                    implicitWidth: 150
                    implicitHeight: 32
                    border.width: 1
                    border.color: "#848484"

                    Button{
                        width: 70
                        height: 25
                        anchors.centerIn: parent
                        text: "Delete"
                        background: Rectangle{
                            radius: 4
                            color: "cyan"
                        }

                        onClicked: {
                            console.log("btn clicked row:",row)
                        }
                    }
                }
            }
        }
    }

    Component.onCompleted: {
        tableModel.appendRow({"name":"小明","sex":"男","id":"w0000065628743342144321241","option":true})
        tableModel.appendRow({"name":"小刚","sex":"女","id":"w0000065628743342144312312","option":true})
        tableModel.appendRow({"name":"小李","sex":"男","id":"w0000065628743342144315433","option":true})
        tableModel.appendRow({"name":"小王","sex":"男","id":"w0000065628743342144313254","option":true})
        tableModel.appendRow({"name":"小张","sex":"女","id":"w0000065628743342144316573","option":true})
        tableModel.appendRow({"name":"小林","sex":"男","id":"w0000065628743342144311232","option":true})
    }

}

