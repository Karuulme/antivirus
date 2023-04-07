import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.15
Rectangle {
    id: rectangle
    width: 675
    height: 480
    color: "#f2f4f7"
    state: {quarantine.setStart();
        return true
    }
    property int quarantinelistIndex: 0
    Text {
        id: name
        text: qsTr("Quarantine Files")
        font.pointSize: 12
        font.bold: true
        x:5
        y:5
    }
    Column {
        id: column222
        width: 675
        spacing: 10
        y:30
        state: {
            if(quarantine.quarantineFile){
                quarantinelistIndex++;
                var myArray = quarantine.quarantineFile.split("--");
                var component = Qt.createComponent("quarantineListView.qml");
                var ttt=component.createObject(column222);
                ttt.fileAddress=myArray[0];
                ttt.fileDate=myArray[1].split(" ")[0];
                ttt.indexNo=myArray[2];
                ttt.listIndex=quarantinelistIndex;
                return false
            }

        }
    }
}
