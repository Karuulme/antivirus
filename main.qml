import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.15

Window {
    property int selectMenuIndex: 0
    width: 880
    height: 540
    flags: Qt.Window
    visibility: Window.Windowed
    visible: true
    title: qsTr("Ourred")
    color: "#f4f4f4"
    maximumHeight: 540
    minimumHeight: 540
    maximumWidth: 880
    minimumWidth: 880

    Rectangle {
        id: menuWindows
        x: 18
        y: 166
        width: 120
        height: 200
        color: "#00000000"
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
                leftPadding: 5

                font.bold: true
                font.family: "Tahoma"
                color: "#949494"
                font.pointSize: 11
                width: 160
                MouseArea{
                    anchors.fill: parent
                    onClicked: selectMenuIndex=0
                }
            }
            Text {
                text: qsTr("Quarantine")
                font.bold: true
                font.family: "Tahoma"
                color: "#949494"
                font.pointSize: 11
                leftPadding: 5
                verticalAlignment: Text.AlignVCenter
                height: 25
                topPadding: 2
                width: 160
                MouseArea{
                    anchors.fill: parent
                    onClicked: selectMenuIndex=1
                }
            }
            Text {
                text: qsTr("Secure File")
                font.bold: true
                font.family: "Tahoma"
                color: "#949494"
                font.pointSize: 11
                leftPadding: 5
                verticalAlignment: Text.AlignVCenter
                height: 25
                width: 160
                MouseArea{
                    anchors.fill: parent
                    onClicked: selectMenuIndex=2
                }
            }
            Text {
                text: qsTr("Setting")
                font.bold: true
                font.family: "Tahoma"
                color: "#949494"
                font.pointSize: 11
                leftPadding: 5
                verticalAlignment: Text.AlignVCenter
                height: 25
                width: 160
                MouseArea{
                    anchors.fill: parent
                    onClicked: selectMenuIndex=3
                }
            }
        }
    }
    Rectangle{
        id:icerik
        x: 164
        y: 60
       width: 675
       height: 480
       color:"#00000000"

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
}
















