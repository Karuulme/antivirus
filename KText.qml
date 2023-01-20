import QtQuick 2.12
import QtQuick.Controls 2.15
Rectangle {
    color:"#00000000"
    height: 15
    width: 200
    property string dName: "Null"
    Text {
        id: label
        text: qsTr(dName)

    }
}

