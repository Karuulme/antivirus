import QtQuick.Controls
import Qt.labs.platform
import QtQuick 2.12

Rectangle {
    width: 750
    height: 470
    color: "#f2f2f2"
/*
    TextEdit {
        id: textLanguage
        x: 34
        y: 59
        text: qsTr("Language")
        font.pixelSize: 14
        font.bold: false
    }
    ComboBox {
        id: comboBox
        x: 158
        y: 59
        width: 120
        height: 25
        model: ["Turkish","English"]
    }
    Rectangle {
        x: 314
        y: 59
        width: 100
        height: 25
        color: "#0047ab"
        radius: 5
        border.color: "#c3c2c2"
        border.width: 1
        Text {
            color: "#ffffff"
            text: qsTr("APPLY")
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pointSize: 8
            font.bold: true
        }

        MouseArea {
            anchors.fill: parent
            onClicked: diolog.open()
        }
    }
*/
    Rectangle{
        visible:!userdefinition.userDefinition
        width: 900
        height: 470
        color: "#00000000"
        TextEdit {
            id: textEdit3
            x: 34
            y: 380
            text: qsTr("Set user definition now with open processes and single programs")
            font.pixelSize: 14
            font.bold: true
        }
        TextEdit {
            id: textEdit4
            x: 34
            y: 400
            text: qsTr("Skips the 200 hour definition time and creates the definition immediately")
            font.pixelSize: 12
            font.bold: false
        }

        Rectangle {
            x: 496
            y: 380
            width: 147
            height: 36
            color: "#0047ab"
            border.width: 1
            radius: 5
            border.color: "#c3c2c2"
            Text {
                text: qsTr("REBUILD")
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                color: "#ffffff"
                font.bold: true

            }
            MouseArea{
                anchors.fill: parent
                onClicked: diolog.open()
            }
        }
        MessageDialog {
            id:diolog
            text: qsTr("User definition is requested to be recreated")
            informativeText: qsTr("Do you want to redefine?")
            buttons: MessageDialog.Yes | MessageDialog.Cancel
            onYesClicked: userdefinition.setUserDefinition()
        }
    }


}
