import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 800
    height: 600
    title: qsTr("Hello World")

    MainScreen
    {
        id: main_screen

        anchors
        {
            top: parent.top
            bottom: parent.bottom
            left: parent.left
            right: control_panel.left
        }
    }

    ControlPanel
    {
        id: control_panel
        width: 200

        anchors
        {
            top: parent.top
            bottom: parent.bottom
            right: parent.right
        }
    }
}
