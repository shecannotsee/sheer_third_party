import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    id: window

    visible: true
    width: 400
    height: 200
    title: "login"

    Rectangle {
        id: loginPage

        gradient: Gradient {
            GradientStop { position: 1; color: "slategray"}
            GradientStop { position: 0; color: "lightsteelblue"}
        }

        border.color: "slategray"
        width: parent.width
        height: parent.height

        Column {
            anchors.centerIn: parent

            TextField {
                id: usernameInput

                placeholderText: "用户名"
                width: 300
                height: 40
            }

            TextField {
                id: passwordInput

                placeholderText: "密码"
                width: 300
                height: 40
                echoMode: TextInput.Password
            }

            Button {
                // 将用户名和密码发送到 C++ 后端进行验证
                // 这里可以调用 C++ 函数来处理登录逻辑
                // 例如，使用 Qt 的信号槽机制将数据传递给 C++
                text: "登录"
                width: 100
                height: 40
                onClicked: {
                    var result = loginHandler.validateLogin(usernameInput.text, passwordInput.text);
                    if (result) {
                        window.visible = false;
                    }

                }
            }

        }

    }

}
