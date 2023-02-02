import QtQuick 2.12
import QtQuick.Controls 2.15
import QtQuick.Dialogs
Rectangle {
    property int writeFileIndex: 2
    id: rectangle
    width: 675
    height: 480
    color:"#f4f4f4"
    state:{securefile.setStart(); return true}
    Rectangle{
        id: rectangle1
        width: parent.width
        height: 65
        color:"#00000000"
        Text {
            x: 53
            y: 32
            color: "#424242"
            font.bold: true
            font.pointSize: 10
            text: qsTr("Create File Protection, Only For Desktop Files")
        }
        Text {
            x: 8
            y: 5
            text: qsTr("File")
            font.bold: true
            font.pointSize: 11
        }
        Rectangle{
            x: 51
            y: 4
            width: 616
            height: 25
            color:"#00000000"
            border.width: 1
            border.color: "black"
            radius:5
            TextInput{
                id:selectFilePath
                anchors.fill: parent
                verticalAlignment: Text.AlignVCenter
                leftPadding: 5
            }
        }
        FolderDialog {
            id: fileDialog
             onAccepted:{
                selectFilePath.text= fileDialog.selectedFolder
             }

        }
        Rectangle{
            x: 461
            y: 32
            width: 100
            height: 25
            color:"#00000000"
            border.width: 1
            radius:5
            Text {
                text: qsTr("Select")
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
            MouseArea{
                anchors.fill: parent
                onClicked: {
                        fileDialog.open();
                }
            }
        }
        Rectangle{
            x: 567
            y: 32
            width: 100
            height: 25
            color:"#00000000"
            border.width: 1
            radius:5
            Text {
                text: qsTr("Added")
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                MouseArea{
                    anchors.fill: parent
                    onClicked:{
                        securefile.set_folderPath(selectFilePath.text);
                        selectFilePath.text="";
                    }
                }
            }
        }
    }
    Column {
        width: parent.width
        height: 400
        anchors.top: rectangle1.bottom
        anchors.topMargin: 40
        state: {
            var componentSecureFileView = Qt.createComponent("secureFileView.qml");
            if(securefile.secureFiles){
                //console.log(securefile.secureFiles);
                var object2 = componentSecureFileView.createObject(this);
                object2.fPath=securefile.secureFiles;
            }
            return true
        }
    }
}
