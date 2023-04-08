import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.15
import QtQuick.Controls
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
    anchors.bottomMargin: 15
    anchors.topMargin: 40
    anchors.leftMargin: 15
    color: "#00000000"
        ScrollView {
            width: parent.width
            height: parent.height
            Column{
                width: parent.width
                height: parent.height
                spacing: 10
                state: {
                    if(quarantine.quarantineFile){
                        quarantinelistIndex++;
                        var myArray = quarantine.quarantineFile.split("--");
                        var component = Qt.createComponent("quarantineListView.qml");
                        var ttt=component.createObject(this);
                        ttt.fileAddress=myArray[0];
                        ttt.fileDate=myArray[1].split(" ")[0];
                        ttt.indexNo=myArray[2];
                        ttt.listIndex=quarantinelistIndex;
                        return false
                    }
                    return false
                }
            }
        }
    }

}
