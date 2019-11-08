import QtQuick 2.0
import QtQuick.Controls 2.12

Rectangle {



    Column
    {
        anchors.fill: parent
        spacing: 2

        GroupBox
        {
            id: state_groupbox
            width: parent.width

            label: Text {
                text: qsTr("State")
            }

            Column
            {
                anchors.fill: parent
                width: parent.width

                Text {
                    text: qsTr("height:")
                    width: parent.width

                }

                TextField
                {
                    text: simulator.height
                    width: parent.width
                    readOnly: true
                }
            }
        }

        GroupBox
        {
            id: control_groupbox
            width: parent.width

            label: Text {
                text: qsTr("Control")
            }

            Column
            {
               anchors.fill: parent
               width: parent.width

               Text {
                   text: qsTr("Throttle:")
                   // width: parent.width
               }

                Slider
                {
                    live: true
                    value: simulator.throttle
                    from: 0.0
                    to: 1.0
                }
            }

        }

    }

}
