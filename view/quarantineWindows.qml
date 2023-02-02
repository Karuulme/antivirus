import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.15

Rectangle {
    id: rectangle
    width: 675
    height: 480
    color:"#f4f4f4"


    Column {
        id: column222
        width: 675
        spacing: 10
        state: {
            var component = Qt.createComponent("quarantineListView.qml");
            for(var i=0;i<10;i++){
                var ttt=component.createObject(this);
               ttt.listIndex=i+1;
            }
            return true
        }
    }
}
