import QtQuick 2.0

Rectangle {
    property int margin: 50

    color: "black"

    Rectangle {
        color: "lightGray"
        height: parent.margin
        width: parent.width
        anchors.bottom: parent.bottom
        z: 2
    }

    Image
    {
        id: lander
        source: "images/lander.png"
        anchors.horizontalCenter: parent.horizontalCenter
        y: Math.round((parent.height - 100) * (1.0 - simulator.height / simulator.starting_height))

        z: 1
        width: 50
        height: 50

    }

    AnimatedImage
    {
        id: exhaust
        source: "images/flame.gif"

        playing: simulator.throttle > 0 & simulator.is_running
        visible: simulator.throttle > 0 & simulator.is_running
        anchors.top : lander.bottom

        z: 0
        x : lander.x + 17
        rotation: 180
        width: 20
        height: 20 * simulator.throttle
    }
}
