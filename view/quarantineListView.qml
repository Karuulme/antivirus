import QtQuick 2.12
Rectangle{
id: rectangle
width: 600
height: 20
color: "#f4f4f4"
property int listIndex: 0
    Text {
        id: qIndex
        x: 5
        y: 4
        color: "#3f3f3f"
        text:listIndex+"th"
        font.pointSize: 6
        width: 25
        height: 11
    }
    Text {
        id: qhash
        x: 30
        y: 3
        color: "#3f3f3f"
        text:"1c50fc3a98187477897b91f01065b2ef6ed5db12622a93d1bd02117c282c12f0"
        font.pointSize: 7
        width: 310
        height: 12
    }
    Text {
        id: qdate
        y: 2
        color: "#5e5e5e"
        text:"5.11.2022"
        anchors.left: qhash.right
        anchors.leftMargin: 30
        font.pointSize: 8
    }
    Text {
        id: qactionDelete
        y: 2
        color: "#525252"
        text: qsTr("Delete")
        anchors.left: qdate.right
        font.bold: true
        anchors.leftMargin: 84
        font.pointSize: 8
        MouseArea{
            anchors.fill: parent
            hoverEnabled: true
            onEntered: {
                parent.font.underline=true
                parent.color="#3f3f3f"
            }
            onExited: {
                parent.font.underline=false
                parent.color="#525252"
            }
        }
    }
    Text {
        id: qactionReturn
        y: 2
        color: "#525252"
        text: qsTr("Return")
        anchors.left: qactionDelete.right
        font.bold: true
        anchors.leftMargin: 20
        font.pointSize: 8
        MouseArea{
            anchors.fill: parent
            hoverEnabled: true
            onEntered: {
                parent.font.underline=true
                parent.color="#3f3f3f"
            }
            onExited: {
                parent.font.underline=false
                 parent.color="#525252"
            }
        }
    }
}

