import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.15
import QtQuick.Window 2.0


Window {
    id: window
    property int selectMenuIndex: 0
    property int windowstastbar_close_icon: 0
    property string menuColor: "#333333"
    width: 930
    height: 600
    flags: Qt.Window
    visibility: Window.Windowed
    visible: true
    title: qsTr("Ourred")
    color: "#f2f2f2"
    maximumHeight: 540
    minimumHeight: 540
    maximumWidth: 930
    minimumWidth: 930
    Rectangle{
        id:icerik
       color:"#00000000"
       anchors.left: parent.left
       anchors.right: parent.right
       anchors.top: logoPanel.bottom
       anchors.bottom: parent.bottom
       anchors.leftMargin: 5
       anchors.rightMargin: 5
       anchors.bottomMargin: 0
       anchors.topMargin: 0
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
        width: parent.width
        height: 42
        //color: "#df1010"
        color: "#00000000"
        Row {
            id: column
            x: 467
            y: 8
            width: 442
            height: 26
            layoutDirection: Qt.LeftToRight
            spacing: 30
            Text {
                text: qsTr("Home")
                verticalAlignment: Text.AlignVCenter
                height: 25
                leftPadding: 10
                x:20
                font.bold: true
                font.family: "Tahoma"
                color: menuColor
                font.pointSize: 11
                width: 60
                MouseArea{
                    anchors.fill: parent
                    onClicked: selectMenuIndex=0
                }
              /*  Image {
                    width: 24
                    height: 24
                    y:-1
                    x:-20// icons8-quarantine-64.png--icons8-security-lock-100.png---icons8-settings-96.png
                    source: "./Image/icons8-home-96.png"
                }*/
            }
            Text {
                x: 20
                text: qsTr("Quarantine")
                font.bold: true
                font.family: "Tahoma"
                color: menuColor
                font.pointSize: 11
                leftPadding: 10
                verticalAlignment: Text.AlignVCenter
                height: 25
                width: 110
                MouseArea{
                    anchors.fill: parent
                    onClicked: selectMenuIndex=1
                }
               /* Image {
                    width: 25
                    height: 25
                    x:-21
                    y:0
                    source: "./Image/icons8-quarantine-64.png"
                }*/
            }
            Text {
                text: qsTr("Secure File")
                font.bold: true
                font.family: "Tahoma"
                color: menuColor
                font.pointSize: 11
                leftPadding: 10
                x:20
                verticalAlignment: Text.AlignVCenter
                height: 25
                width: 110
                MouseArea{
                    anchors.fill: parent
                    onClicked: selectMenuIndex=2
                }
               /* Image {
                    width: 22
                    height: 22
                    x:-20
                    y:2
                    source: "./Image/icons8-security-lock-100.png"
                }*/
            }
            Text {
                text: qsTr("Setting")
                font.bold: true
                font.family: "Tahoma"
                color: menuColor
                font.pointSize: 11
                leftPadding: 10
                x:20
                verticalAlignment: Text.AlignVCenter
                height: 25
                width: 80
                MouseArea{
                    anchors.fill: parent
                    onClicked: selectMenuIndex=3
                }
              /*  Image {
                    width: 22
                    height: 22
                    x:-20
                    y:2
                    source: "./Image/icons8-settings-96.png"
                }*/
            }
        }
        Rectangle{
            width: parent.width
            height: 1
            border.width: 1
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 1
            color: "#b8b8b8"
        }

        Text {
            x: 42
            y: 4
            text: qsTr("OURRED")
            font.pointSize: 18
            font.bold: true
            color: "#df1010"
        }
        Image {
            x: 4
            y: 4
            width: 30
            height: 30
            //source: "./Image/delogo2.png"
            source: "./Image/logopng2.png"
        }


      /*  Rectangle{
            x: 820
            width: 25
            height: 25
            id:windowsTaskBar_close
            color:"#00000000"
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.topMargin: 5
            anchors.rightMargin: 5

            Image {
                id: image
                width: 25
                height: 25
                source:{
                    if(windowstastbar_close_icon==0){
                       windowsTaskBar_close.color= "#00000000"
                        "../Image/icons8-close-64.png"
                        }
                    else{
                        windowsTaskBar_close.color= "#EDEDED"
                        "../Image/icons8-close-red-64.png"
                    }
                }
                fillMode: Image.PreserveAspectFit
                MouseArea{
                    anchors.fill: parent
                    onClicked: windowstaskbar.windowsClose()
                    hoverEnabled: true
                    onEntered: {
                        windowstastbar_close_icon=1
                    }
                    onExited: {
                        windowstastbar_close_icon=0
                    }
                }
            }
        }*/
    }

}
















