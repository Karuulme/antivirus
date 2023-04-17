import QtQuick 2.0
import QtQuick.Window 2.0
import QtQuick.Controls 2.0
Rectangle {
    id: rectangle
    width: 930
    height: 470
    color: "#f2f2f2"
    state: {quarantine.setStart();
        return true
    }
    property int quarantinelistIndex: 0
    Rectangle{
    width: 900
    anchors.left: parent.left
    anchors.top: parent.top
    anchors.bottom: parent.bottom
    //clip: true
    anchors.bottomMargin: 15
    anchors.topMargin: 40
    anchors.leftMargin: 15
    color: "#00000000"

    ScrollView {
            width: parent.width
            height: parent.height
            Column{
                id:quarantineList_Column
                width: parent.width
                height: parent.height
                spacing: 10
                state:  {
                    if(quarantine.quarantineFile){
                        var component = Qt.createComponent("quarantineListView.qml");
                        quarantinelistIndex++;
                        var myArray = quarantine.quarantineFile.split("--");
                        var ttt=component.createObject(this);
                        ttt.fileAddress=myArray[0];
                        ttt.fileDate=myArray[1].split(" ")[0];
                        ttt.indexNo=myArray[2];
                        ttt.listIndex=quarantinelistIndex;
                    }
                    return true;
                }

            }
        }
    }
    Rectangle {
        x: 295
        y: 5
        width: 25
        height: 25
        color: "#00000000"
        radius: 5
        anchors.right: parent.right
        Image {
            width: 25
            height: 25
            source: "../Image/icons8-refresh-96.png"
            MouseArea {
                anchors.fill: parent
                onEntered: {
                            parent.parent.color="#e3e3e3"
                        }
                hoverEnabled: true
                onClicked: {
                            for(var i = quarantineList_Column.children.length; i > 0 ; i--) {
                              quarantineList_Column.children[i-1].destroy()
                            }
                            quarantinelistIndex=0;
                            //quarantine.setStart();
                        }
                onExited:{
                            parent.parent.color="#00000000"
                        }
            }
            fillMode: Image.PreserveAspectFit
        }
        anchors.rightMargin: 10
    }



}
