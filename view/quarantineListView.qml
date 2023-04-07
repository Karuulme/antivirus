import QtQuick 2.12
import QtQuick 2.15
Rectangle{
id: main
width: 600
height: 20
color: "#f2f4f7"
property int indexNo: -1
property int listIndex: 0
property string fileAddress: ""
property string fileDate: "25.02.2023 12.25"
    Text {
        id: qIndex
        x: 5
        y: 1
        color: "#3f3f3f"
        text:listIndex+"th"
        font.bold: true
        font.pointSize: 9
        width: 25
        height: 15
    }
    Text {
        id: qhash
        x: 30
        y: 2
        color: "#3f3f3f"
        text:fileAddress
        font.pointSize: 9
        width: 310
        height: 15
        wrapMode: Text.Wrap
        clip: true
        MouseArea{
            anchors.fill: parent;
            //onH:
        }
    }
    Text {
        id: qdate
        y: 2
        color: "#5e5e5e"
        text:fileDate
        anchors.left: qhash.right
        anchors.leftMargin: 30
        font.pointSize: 9
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
            onClicked:{ quarantine.getQuarantineOptions(indexNo,0);
             main.destroy();
            }
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
            onClicked: {quarantine.getQuarantineOptions(indexNo,1);
             main.destroy();
            }
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

