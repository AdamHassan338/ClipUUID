import QtQuick
import QtQuick.Controls
import QtQuick.Effects

Window {
    id: window
    width: 680
    height: 300
    x: Screen.width / 2 - this.width / 2
    y: Screen.height * 0.05
    visible: true
    title: qsTr("Hello World")
    flags: Qt.FramelessWindowHint | Qt.WindowDoesNotAcceptFocus | Qt.WindowTransparentForInput | Qt.WindowStaysOnTopHint | Qt.Tool

    color: "transparent"

    Item{
        id:temp
        anchors.centerIn: parent
        width: 680
        height: 300
    }

    Rectangle {
        id: main
        anchors.centerIn: parent
        width : 640
        height: 80
        color: Qt.rgba(0.98,0.98,0.98,1)
        radius: 20


        Text {
            id: name
            text: uuuidGenorator.UUID
            anchors.centerIn: parent
            font.pixelSize: 20

            color: "black"
        }




    }

    MultiEffect {
        id: windowEffects
        source: main
        anchors.fill: main
        shadowBlur: 1.3
        shadowColor: Qt.rgba(0, 0, 0, 0.5)
        shadowEnabled: true
        shadowVerticalOffset: 10
        shadowHorizontalOffset: 0
        visible: true

    }



    // MultiEffect {
    //     id: maskEffects
    //     source: windowEffects
    //     anchors.fill: main
    //     maskEnabled: true
    //     maskSource: mask
    //     maskInverted: false

    // }

    // Item {
    //         id: mask
    //         anchors.centerIn: main
    //         width: parent.width
    //         height: parent.height
    //         visible: false
    //         clip: false

    //         Rectangle {
    //             width: 680
    //             height: 300
    //             x: Screen.width / 2 - this.width / 2
    //             y: Screen.height * 0.05
    //             radius: 20
    //             color: "white"
    //         }

    //         Rectangle {
    //             anchors.centerIn: parent
    //             width: main.width
    //             height: main.height
    //             radius: 20
    //             color: "black"
    //         }


    //     }





    function calc() {
        return window.width > window.height ? window.width * 0.02 : window.height * 0.02;
    }
}
