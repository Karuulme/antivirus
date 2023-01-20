import QtQuick 2.12
import QtQuick.Controls 2.15
Rectangle {
    id: rectangle
    width: 340
    height: 60
    color:"#f9f9f9"
    border.width: 1
    border.color: "#c8c8c8"
    radius: 5
    Image {
        id: image
        x: 8
        y: 10
        width: 40
        height: 40
        source: "Image/icons8-hdd-80.png"
        fillMode: Image.PreserveAspectFit
    }

    Label {
        id: label
        x: 63
        y: 8
        height: 16
        text: qsTr("C:\\")
    }

    Label {
        id: label1
        x: 63
        y: 30
        height: 16
        text: qsTr("Total:"+500)
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
        Rectangle{
            height:45
            color: "#b9b9b9"
            anchors.left: parent.left
            anchors.leftMargin: 0
            width: 1
            y:5
        }

        Text {
            id: name
            text: qsTr("Free")
            horizontalAlignment: Text.AlignHCenter
            width: parent.width
            y:10
        }
        Text {
            id: name2
            text: qsTr("50 GB")
            horizontalAlignment: Text.AlignHCenter
            width: parent.width
            y:25
        }


    }
}
