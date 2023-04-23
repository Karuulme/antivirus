import QtQuick 2.12
import QtQuick.Controls 2.3
Rectangle {
    id: rectangle
    width: 930
    height: 470
    color: "#f2f2f2"
    state: {quarantine.setStart();
        return true
    }
    property bool deneme: false
    Rectangle{
    width: 860
    anchors.left: parent.left
    anchors.top: parent.top
    anchors.bottom: parent.bottom
    //clip: true
    anchors.bottomMargin: 15
    anchors.topMargin: 40
    anchors.leftMargin: 34
    color: "#00000000"
    ScrollView {
            width: parent.width+20
            height: parent.height
            Column {
                id: quarantineList_Column
                width:860
                height: parent.height
                spacing: 10
                state: {
                    if(quarantine.quarantineFile){
                        var component = Qt.createComponent("QuarantineListView.qml");
                        var myArray = quarantine.quarantineFile.split("--");
                        var ttt=component.createObject(quarantineList_Column);
                        ttt.fileAddress=myArray[0];
                        ttt.fileDate=myArray[1].split(" ")[0];
                        ttt.indexNo=myArray[2];
                    }
                    return true;
                }
            }
        }
    }
    Rectangle {
        x: 809
        y: 8
        width: 90
        height: 28
        color: "#00000000"
        radius: 4
        anchors.right: parent.right
        anchors.rightMargin: 36
        MouseArea {
            anchors.fill: parent
            onEntered: {
                        parent.color="#e3e3e3"
                    }
            hoverEnabled: true
            onClicked: {
                    for(var i = quarantineList_Column.children.length; i > 0 ; i--) {
                        quarantineList_Column.children[i-1].destroy()
                    }
                    quarantine.setStart();

                    }
            onExited:{
                        parent.color="#00000000"
                    }
        }
        Text {
            x:5
             height: parent.height
             text: qsTr("Refresh")
             verticalAlignment: Text.AlignVCenter
             font.bold: true
             font.pointSize: 11
        }
        Image {
            x:62
            y:2
            width: 24
            height: 24
            source: "../Image/icons8-refresh-96.png"

            fillMode: Image.PreserveAspectFit
        }


    }
}
