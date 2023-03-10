import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.15

Window {
    id: window
    property int selectMenuIndex: 0
    width: 880
    height: 600
    flags: Qt.Window
    visibility: Window.Windowed
    visible: true
    title: qsTr("Ourred")
    color: "#f2f4f7"
    maximumHeight: 540
    minimumHeight: 540
    maximumWidth: 880
    minimumWidth: 880

    Rectangle{
        width: 1
        height: 500
        color: "#b8b8b8"
        anchors.left: menuWindows.right
        anchors.top: logoPanel.bottom
        anchors.topMargin: 0
        anchors.leftMargin:8
    }

    Rectangle {
        id: menuWindows
        x: 7
        width: 150
        height: 200
        color: "#00000000"
        anchors.top: logoPanel.bottom
        anchors.topMargin: 10
        Rectangle {
            id: selectMenu
            width: 8
            height: 8
            color: "#b8b8b8"
            radius: 100
            y:(selectMenuIndex*35)+9
            anchors.right: parent.right
            anchors.rightMargin: 0
        }
        Column {
            id: column
            width: 120
            spacing: 10
            Text {
                text: qsTr("Home")
                verticalAlignment: Text.AlignVCenter
                height: 25
                leftPadding: 10
                x:20
                font.bold: true
                font.family: "Tahoma"
                color: "#949494"
                font.pointSize: 11
                width: 160
                MouseArea{
                    anchors.fill: parent
                    onClicked: selectMenuIndex=0
                }
                Image {
                    width: 24
                    height: 24
                    y:-1
                    x:-20// icons8-quarantine-64.png--icons8-security-lock-100.png---icons8-settings-96.png
                    source: "./Image/icons8-home-96.png"
                }
            }
            Text {
                x: 20
                text: qsTr("Quarantine")
                font.bold: true
                font.family: "Tahoma"
                color: "#949494"
                font.pointSize: 11
                leftPadding: 10
                verticalAlignment: Text.AlignVCenter
                height: 25
                width: 160
                MouseArea{
                    anchors.fill: parent
                    onClicked: selectMenuIndex=1
                }
                Image {
                    width: 25
                    height: 25
                    x:-21
                    y:0
                    source: "./Image/icons8-quarantine-64.png"
                }
            }
            Text {
                text: qsTr("Secure File")
                font.bold: true
                font.family: "Tahoma"
                color: "#949494"
                font.pointSize: 11
                leftPadding: 10
                x:20
                verticalAlignment: Text.AlignVCenter
                height: 25
                width: 160
                MouseArea{
                    anchors.fill: parent
                    onClicked: selectMenuIndex=2
                }
                Image {
                    width: 22
                    height: 22
                    x:-20
                    y:2
                    source: "./Image/icons8-security-lock-100.png"
                }
            }
            Text {
                text: qsTr("Setting")
                font.bold: true
                font.family: "Tahoma"
                color: "#949494"
                font.pointSize: 11
                leftPadding: 10
                x:20
                verticalAlignment: Text.AlignVCenter
                height: 25
                width: 160
                MouseArea{
                    anchors.fill: parent
                    onClicked: selectMenuIndex=3
                }
                Image {
                    width: 22
                    height: 22
                    x:-20
                    y:2
                    source: "./Image/icons8-settings-96.png"
                }
            }
        }
    }
    Rectangle{
        id:icerik
       color:"#00000000"
       anchors.left: menuWindows.right
       anchors.right: parent.right
       anchors.top: logoPanel.bottom
       anchors.bottom: parent.bottom
       anchors.leftMargin: 20
       anchors.rightMargin: 5
       anchors.bottomMargin: 0
       anchors.topMargin: 10
       Pane {
           id: menuhomeWindows
           anchors.fill: parent
           visible: {
               if( selectMenuIndex === 0 )
                    return  true
               else
                    return false
           }
           state: {
               var component = Qt.createComponent("view/homeWindows.qml");
               component.createObject(this);
               return true
           }
       }
       Pane {
           id: menuquarantineWindows
           anchors.fill: parent
           visible: {
               if( selectMenuIndex === 1 )
                    return  true
               else
                    return false
           }
           state: {
               var component = Qt.createComponent("view/quarantineWindows.qml");
               component.createObject(this);
               return true
           }
       }
       Pane {
           id: menusecurefileWindows
           anchors.fill: parent
           visible: {
               if( selectMenuIndex === 2 )
                    return  true
               else
                    return false
           }
           state: {
               var component = Qt.createComponent("view/securefileWindows.qml");
               component.createObject(this);
               return true
           }
       }
       Pane {
           id: menusettingWindows
           anchors.fill: parent
           visible: {
               if( selectMenuIndex === 3 )
                    return  true
               else
                    return false
           }
           state: {
               var component = Qt.createComponent("view/settingWindows.qml");
               component.createObject(this);
               return true;
           }
       }
    }

    Rectangle {
        id: logoPanel
        x: 0
        y: 0
        width: 880
        height: 54
        color: "#df1010"
        Text {
            x: 74
            y: 10
            text: qsTr("OURRED")
            font.pointSize: 20
            font.bold: true
            color: "#ffffff"
        }
        Image {
            x: 8
            y: 10
            width: 36
            height: 36
            source: "./Image/delogo2.png"
            rotation: 1.219
        }
    }
}
















