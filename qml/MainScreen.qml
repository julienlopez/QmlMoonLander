import QtQuick 2.0

Rectangle {
    property int margin: 50

    color: "black"

    Rectangle {
        color: "lightGray"
        height: parent.margin
        width: parent.width
        anchors.bottom: parent.bottom
    }

    Image
    {
        source: "images/lander.png"
        anchors.horizontalCenter: parent.horizontalCenter
        y: Math.round((parent.height - 100) * (1.0 - simulator.height / simulator.starting_height))

        width: 50
        height: 50

    }
}
