import QtQuick
import QtQuick.Effects

Window {
    id: window
    width: 680
    height: 300
    x: Screen.width / 2 - this.width / 2
    y: Screen.height * 0.05
    visible: false
    color: "transparent"
    opacity: 0
    title: qsTr("ClipUUID")
    flags: Qt.FramelessWindowHint | Qt.WindowDoesNotAcceptFocus | Qt.WindowTransparentForInput | Qt.WindowStaysOnTopHint | Qt.Tool


    property bool isVisible: false

    Behavior on opacity {NumberAnimation{}}

    Timer {
        id:timer
           interval: 500; running: false; repeat: false
           onTriggered: isVisible = false
       }

    Rectangle {
        id: main
        y:parent.height/2 - this.height / 2
        x: parent.width / 2 - this.width / 2

        width : 640
        height: 80
        color: main.focus ? Qt.rgba(0.98,0.98,0.98,1) : "red";
        radius: 20
        Behavior on y {NumberAnimation {duration: 250; easing.type: Easing.OutBack}}

        Text {
            id: name
            text: uuuidGenorator.UUID
            anchors.centerIn: parent
            font.pixelSize: 20

            color: "black"
        }


        states: [
            State {
                name: "fadingIn"
                when: isVisible
                PropertyChanges {
                    target: window
                    opacity: 1
                }
                PropertyChanges {
                    target: main
                    y:parent.height/2 - this.height / 2
                }
                PropertyChanges {
                    target: window
                    visible: true
                }
            },
            State {
                name: "fadingOut"
                when: !isVisible && !timer.running && window.opacity >0
                PropertyChanges {
                    target: window
                    opacity: 0
                }
                PropertyChanges {
                    target: main
                    y:parent.height/2 - this.height / 2
                }
                PropertyChanges {
                    target: window
                    visible: true
                }
            },
            State {
                name: "hidden"
                when: window.opacity === 0
                PropertyChanges {
                    target: window
                    opacity: 0
                }
                PropertyChanges {
                    target: main
                    y: 0
                }
                PropertyChanges {
                    target: window
                    visible: false
                }
            }
        ]
    onStateChanged: console.log(main.state)

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


    function popUp(){
        isVisible = true;
        window.raise();
        //window.requestActivate();
        main.focus = true;
        main.forceActiveFocus();
        if(timer.running)
            timer.restart()
        else
            timer.start();
    }

    Connections{
        target: uuuidGenorator
        function onFocus(){
            popUp();
        }
    }



}
