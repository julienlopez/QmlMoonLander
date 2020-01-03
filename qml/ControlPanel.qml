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

                Text {
                    text: qsTr("speed:")
                    width: parent.width
                }

                TextField
                {
                    text: simulator.speed
                    width: parent.width
                    readOnly: true
                }

                Text {
                    text: qsTr("fuel")
                    width: parent.width
                }

                ProgressBar
                {
                    from: 0
                    to: simulator.starting_fuel
                    value: simulator.fuel
                    width: 0.9 * parent.width
                    anchors.horizontalCenter: parent.horizontalCenter
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

               Text {
                   text: qsTr("Throttle:")
                   // width: parent.width
               }

                Slider
                {
                    id: throttle_slider
                    live: true
                    value: simulator.throttle
                    from: 0.0
                    to: 1.0
                    onValueChanged: simulator.throttle = value
                }
            }
        }

        Button
        {
            text: qsTr("Start")
            enabled: !simulator.is_running
            onClicked: simulator.start();
            width: parent.width
        }

    }

}
