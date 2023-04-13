import QtQuick 2.0
import QtQuick.Controls 2.0
Rectangle {
    property double dFree: 50
    property double dTotal: 500
    property string dName: "Null"
    property string dRadiusColor: "#c8c8c8"
    state: {
        if(system.scaningDisk===dName){
            busyIndicator1.running=true
            scan_button.visible=false
            scan_button_cancel.visible=true
            dRadiusColor="#0047ab"
        }
        else{
            busyIndicator1.running=false
            scan_button.visible=true
            scan_button_cancel.visible=false
            dRadiusColor="#c8c8c8"
        }
        return true
    }
    id: rectangle
    width: 410
    height: 65
    color:"#f9f9f9"
    border.width: 1
    border.color: dRadiusColor
   // border.color: "#0047ab"
    radius: 5
    Image {
        id: image
        x: 10
        y: 10
        width: 40
        height: 40
        source: "../Image/icons8-hdd-80.png"
        fillMode: Image.PreserveAspectFit
    }
    Label {
        id: label
        x: 56
        y: 12
        height: 16
        text: qsTr(dName)
    }

    Label {
        id: label1
        x: 56
        y: 34
        height: 16
        text: qsTr("Total: "+dTotal +" "+"Free: "+dFree)
    }

    Rectangle{
        id: rectangle1
        width: 70
        y:1
        radius: 5
        height: 58
        anchors.right: parent.right
        anchors.rightMargin: 1
        color: "#00000000"
       /* Rectangle{
            height:45
            color: "#b9b9b9"
            anchors.left: parent.left
            anchors.leftMargin: 0
            width: 1
            y:5
        }*/
      /*  Text {
            id: name
            text: qsTr("Free")
            horizontalAlignment: Text.AlignHCenter
            width: parent.width
            y:10
        }*/
       /* Text {
            id: name2
            text: dFree
            horizontalAlignment: Text.AlignHCenter
            width: parent.width
            y:25
        }*/


    }



    Rectangle{
       id:scan_button
        width: 80
        height: 20
        x:309
        y:23
        visible: true
        border.width: 1
        color:"#00000000"
        radius: 5
        border.color: "#b9b9b9"
        MouseArea {
            id: mouseArea
            anchors.fill: parent
            onClicked:system.set_scandisk(dName,dTotal,dFree)

        }
        Label {
            id: label2
            text: qsTr("Scan This Disk")
            anchors.fill: parent
            font.letterSpacing: 0
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter


        }
    }
    Rectangle{
        id:scan_button_cancel
        width: 40
        visible: false
        height: 20
        x:309
        y:23
        border.width: 1
        color:"#00000000"
        radius: 5
        border.color: "#b9b9b9"
        MouseArea {
            id: mouseArea2
            anchors.fill: parent
            onClicked:system.set_scandiskClose()

        }
        Label {
            id: label22
            text: qsTr("Cancel")
            anchors.fill: parent
            font.letterSpacing: 0
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

    }
    BusyIndicator {
        x: 368
        y:16
        width: 34
        height: 34
        id: busyIndicator1
        running: false

    }

}
