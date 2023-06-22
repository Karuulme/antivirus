import QtQuick 2.15
import QtQuick.Window 2.2
import QtQuick.Controls 2.15
import QtQuick.Window 2.0
import QtQuick.Layouts 1.3

Window {
    id: window
    property int selectMenuIndex: 0
    property int windowstastbar_close_icon: 0
    property string menuColor: "#333333"
    property int mouseLocalX: 0
    property int mouseLocalY: 0
    property point mouseGlobal: cursorPos
    width: 930
    height: 540
    title: qsTr(" ")
    color: "#f2f2f2"
    flags: Qt.Sheet
    maximumHeight: 540
    minimumHeight: 540
    maximumWidth: 930
    minimumWidth: 930
    signal startTimer()
    signal stopTimer()
    visible:true
    Rectangle{
        id:icerik
        color:"#00000000"
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: logoPanel.bottom
        anchors.bottom: parent.bottom
        anchors.leftMargin: 0
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.topMargin: -1
        z:10
        StackLayout {
            id: homeMain3
            anchors.fill: parent
            anchors.rightMargin: 0
            anchors.bottomMargin: 0
            z:100
            currentIndex:selectMenuIndex
            HomeWindowsView{
                id:pages_Home
            }
            SecurefileWindowsView {
                id:pages_Secure
            }
            QuarantineWindowsView {
                id:pages_Quarantine
            }
            SettingsWindowsView {
                id:pages_Settings
            }
        }
    }
    Rectangle{
        width: 462
        height: 43
        y:1
        color: "#00000000"
        anchors.right: parent.right
        anchors.rightMargin: 0

    }

    Rectangle {
        id: logoPanel
        x: 0
        y: 0
        width: parent.width
        height: 45
        z:10
        color: "#00000000"
        Rectangle{
            width: parent.width
            height: 1
            visible: false
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            color: "#e1e1e1"
        }
        Image {
            x: 30
            y: 10
            width: 30
            height: 30
            source: "qrc:/Image/logopng2.png"
        }

        MouseArea{
            id:windowScrollBar
            width: 470
            height: parent.height
            onPressed: {
                mouseLocalX=mouseX
                mouseLocalY=mouseY
                window.startTimer()
                time_id.start()
            }
            onReleased: {
                time_id.stop()
                window.stopTimer()
            }
        }
        Timer {
            id:time_id
            interval: 10
            repeat: true
            running: false
            onTriggered: {
                window.setX(parseInt(mouseGlobal.x)-mouseLocalX)
                window.setY(parseInt(mouseGlobal.y)-mouseLocalY)
            }
        }
        Row{
            width: 464
            height: parent.height
            anchors.right: parent.right
            layoutDirection: Qt.LeftToRight
            anchors.rightMargin: -3
            spacing:-1
            Rectangle{
                MouseArea{
                    anchors.fill: parent
                    onClicked: selectMenuIndex=0
                    hoverEnabled: true
                    onEntered: {
                        parent.color="#f9f9f9"
                    }
                    onExited:{
                        parent.color="#ffffff"
                    }
                }
                width: 100
                height: parent.height
                color: "#ffffff"
                border.width: 1
                border.color: "#dadada"
                radius: 4
                Text {
                    anchors.fill: parent
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.styleName: "Normal"
                    font.family: "Arial"
                    font.bold: true
                    font.pointSize: 11
                    text: qsTr("Home")
                }
                Rectangle{
                    z:100
                    visible: {
                        if(selectMenuIndex==0){
                            return true
                        }
                        else{
                            return false
                        }
                    }
                    radius: 4
                    height: 2
                    anchors.bottom: parent.bottom
                    anchors.leftMargin: 1
                    anchors.rightMargin: 0
                    anchors.bottomMargin: 0
                    color:"#6366f1"
                    anchors.left: parent.left
                    anchors.right: parent.right
                }
                Rectangle{
                        color:parent.color
                        width: 8
                        height: parent.height
                        anchors.right: parent.right
                        anchors.rightMargin: 0
                        Rectangle{
                            //id:_top
                            width: parent.width
                            height: 1
                            color: "#dadada"
                        }
                        Rectangle{
                            //id:_bottom
                            width: parent.width
                            height: 1
                            color: "#dadada"
                            anchors.bottom: parent.bottom
                            anchors.bottomMargin: 0
                        }
                        Rectangle{
                            //id:_right
                            width: 1
                            visible: false
                            height: parent.height
                            color: "#dadada"
                            anchors.right: parent.right
                            anchors.rightMargin: 0
                        }
                        Rectangle{
                            //id:_left
                            visible: false
                            width: 1
                            height: parent.height
                            color: "#dadada"
                            anchors.right: parent.left
                            anchors.leftMargin: 0
                        }
                }

            }
            Rectangle{
                MouseArea{
                    anchors.fill: parent
                    onClicked: selectMenuIndex=1
                    hoverEnabled: true
                    onEntered: {
                        parent.color="#f9f9f9"
                    }
                    onExited:{
                        parent.color="#ffffff"
                    }
                }
                width: 110
                height: parent.height
                color: "#ffffff"
                border.width: 1
                border.color: "#dadada"
                radius: 0
                Rectangle{
                    z:100
                    visible: {
                        if(selectMenuIndex==1){
                            return true
                        }
                        else{
                            return false
                        }
                    }
                    radius: 4
                    height: 2
                    anchors.bottom: parent.bottom
                    anchors.leftMargin: 1
                    anchors.rightMargin: 0
                    anchors.bottomMargin: 0
                    color:"#6366f1"
                    anchors.left: parent.left
                    anchors.right: parent.right
                }
                Text {
                    anchors.fill: parent
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.bold: true
                    font.pointSize: 10
                    text: qsTr("Secure File")
                }
            }
            Rectangle{
                MouseArea{
                    anchors.fill: parent
                    onClicked: selectMenuIndex=2
                    hoverEnabled: true
                    onEntered: {

                        parent.color="#f9f9f9"
                    }
                    onExited:{
                        parent.color="#ffffff"
                    }
                }
                width: 110
                height: parent.height
                color: "#ffffff"
                border.width: 1
                border.color: "#dadada"
                radius: 0
                Text {
                    anchors.fill: parent
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.bold: true
                    font.pointSize: 10
                    text: qsTr("Quarantine")
                }
                Rectangle{
                    z:100
                    visible: {
                        if(selectMenuIndex==2){
                            return true
                        }
                        else{
                            return false
                        }
                    }
                    radius: 4
                    height: 2
                    anchors.bottom: parent.bottom
                    anchors.leftMargin: 1
                    anchors.rightMargin: 0
                    anchors.bottomMargin: 0
                    color:"#6366f1"
                    anchors.left: parent.left
                    anchors.right: parent.right
                }

            }
            Rectangle{
                MouseArea{
                    anchors.fill: parent
                    onClicked: selectMenuIndex=3
                    hoverEnabled: true
                    onEntered: {

                        parent.color="#f9f9f9"
                    }
                    onExited:{
                        parent.color="#ffffff"
                    }
                }
                id: rectangle
                width: 108
                height: parent.height
                color: "#ffffff"
                border.width: 1
                border.color: "#dadada"
                radius: 4
                Rectangle{
                    z:100
                    visible: {
                        if(selectMenuIndex==3){
                            return true
                        }
                        else{
                            return false
                        }
                    }
                    radius: 4
                    height: 2
                    anchors.bottom: parent.bottom
                    anchors.leftMargin: 1
                    anchors.rightMargin: 0
                    anchors.bottomMargin: 0
                    color:"#6366f1"
                    anchors.left: parent.left
                    anchors.right: parent.right
                }
                Text {
                    anchors.fill: parent
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.bold: true
                    font.pointSize: 10
                    text: qsTr("Settings")
                }
                Rectangle{
                        width: 8
                        color:parent.color
                        height: parent.height
                        anchors.left: parent.left
                        anchors.leftMargin: 0
                        Rectangle{
                            //id:_top
                            width: parent.width
                            height: 1
                            color: "#dadada"
                        }
                        Rectangle{
                            //id:_bottom
                            width: parent.width
                            height: 1
                            color: "#dadada"
                            anchors.bottom: parent.bottom
                            anchors.bottomMargin: 0
                        }
                        Rectangle{
                            //id:_right
                            width: 1
                            visible: false
                            height: parent.height
                            color: "#dadada"
                            anchors.right: parent.right
                            anchors.rightMargin: 0
                        }
                        Rectangle{
                            //id:_left
                            width: 1
                            height: parent.height
                            color: "#dadada"
                            anchors.right: parent.left
                            anchors.leftMargin: 0
                        }
                }

            }
            Rectangle{
                width: 40
                height: parent.height
                border.width: 1
                border.color: "#dadada"
                //radius: 4
                Image {
                    id:closeImage_id
                    width: 25
                    height: 25
                    x:6
                    y:11
                    z:100
                    source:"qrc:/Image/icons8-close-64.png"
                }
                MouseArea{
                    anchors.fill: parent
                    hoverEnabled: true
                    onEntered: {
                        closeImage_id.source="qrc:/Image/icons8-close-red-64.png"
                        parent.color="#f9f9f9"
                    }
                    onExited:{ closeImage_id.source= "qrc:/Image/icons8-close-64.png"
                        parent.color="#ffffff"
                    }
                    onClicked:window.visible=false
                }
                Rectangle{
                        width: 8
                        height: parent.height
                        color: parent.color
                        anchors.left: parent.left
                        anchors.leftMargin: 0
                        Rectangle{
                            //id:_top
                            width: parent.width
                            height: 1
                            color: "#dadada"
                        }
                        Rectangle{
                            //id:_bottom
                            width: parent.width
                            height: 1
                            color: "#dadada"
                            anchors.bottom: parent.bottom
                            anchors.bottomMargin: 0
                        }
                        Rectangle{
                            //id:_right
                            width: 1
                            visible: false
                            height: parent.height
                            color: "#dadada"
                            anchors.right: parent.right
                            anchors.rightMargin: 0
                        }
                        Rectangle{
                            //id:_left
                            width: 1
                            height: parent.height
                            color: "#dadada"
                            anchors.right: parent.left
                            anchors.leftMargin: 0
                        }
                }
            }
        }
    }
}















