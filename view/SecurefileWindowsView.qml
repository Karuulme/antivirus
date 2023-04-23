import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Dialogs
Rectangle {
    property int writeFileIndex: 2
    id: rectangle
    width: 930
    height: 470
    color: "#f2f2f2"
    state:{securefile.setStart(); return true}
    Rectangle{
        id: rectangle1
        width: parent.width
        height: 65
        color:"#00000000"
        y:5
        Text {
            x: 40
            y: 32
            color: "#424242"
            font.bold: true
            font.pointSize: 10
            text: qsTr("Create File Protection, Only For Desktop Files")
        }
        Text {
            x: 5
            y: 5
            text: qsTr("File:")
            font.bold: true
            font.pointSize: 11
        }
        Rectangle{
            id: rectangle2
            x: 38
            y: 4
            width: 857
            height: 25
            color:"#00000000"
            border.width: 1
            border.color: "black"
            radius:4
            Text{
                id:selectFilePath
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                verticalAlignment: Text.AlignVCenter
                font.pointSize: 10
                anchors.leftMargin: 5
            }
        }
        FolderDialog {
            id: fileDialog
            onAccepted:{
                selectFilePath.text= fileDialog.selectedFolder
             }
        }
        Rectangle{
            x: 680
            y: 35
            width: 100
            height: 25
            color:"#00000000"
            border.width: 1
            radius:4
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
            x: 795
            y: 35
            width: 100
            height: 25
            color:"#00000000"
            border.width: 1
            radius:4
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
    Rectangle{
        width: 880
        height: 390
        color: "#00000000"
        anchors.left: parent.left
        anchors.top: rectangle1.bottom
        anchors.leftMargin: 35
        anchors.topMargin: 0
        ScrollView {
            width: parent.width
            height: parent.height
            //ScrollBar.horizontalPolicy: ScrollBar.AlwaysOff
            Column{
                width: parent.width
                height: parent.height
                spacing: 10
                state: {
                    var componentSecureFileView = Qt.createComponent("SecureFileView.qml");
                    if(securefile.secureFiles){
                        var fileValue=securefile.secureFiles.split(":?!?:");
                        if(fileValue[0]==="new"){
                            secureFolderPath.text=fileValue[1];
                            secureKey.text=fileValue[2];
                            secureNewFolderNotification.visible=true;
                        }
                        var object2 = componentSecureFileView.createObject(this);
                        object2.fPath=fileValue[1]
                        object2.fKey=fileValue[2]
                    }
                    return true
                }
            }
        }
    }

    Rectangle {
        id: secureNewFolderNotification
        y: 365
        width: 659
        height: 97
        color: "#04AA6D"
        radius: 4
        border.color: "#006619"
        border.width: 2
        anchors.left: parent.left
        anchors.leftMargin: 146
        visible: false
        Image {

            width: 25
            height: 25
            anchors.right: parent.right
            anchors.top: parent.top
            source: "../Image/icons8-close-64.png"
            anchors.topMargin: 5
            anchors.rightMargin: 5
            MouseArea{
                anchors.fill: parent
                onClicked: secureNewFolderNotification.visible=false
            }
        }
        Text {
            id: secureFolderPath
            x: 7
            y: 7
            font.pointSize: 10
            font.bold: true
            color: "#ffffff"
            text: "C:\Users\XXXX\Desktop\XXXXX"
        }

        Text {
            id: name1
            x: 7
            y: 30
            color: "#ffffff"
            text: "Under the secure file address you provided"
            font.bold: false
            font.pointSize: 10
        }

        Text {
            id: secureKey
            x: 7
            y: 54
            color: "#ffffff"
            text: "'11eb6aeda16af43cdff6dd1d9657387016f3bd1fa6b9e743670c02fb3d4cd4ad'"
            font.bold: true
            font.pointSize: 10
        }
        Text {
            id: name4
            y: 54
            color: "#ffffff"
            text: "folder created."
            anchors.left: secureKey.right
            anchors.leftMargin: 5
            font.bold: false
            font.pointSize: 10
        }

        Text {
            id: name3
            x: 7
            y: 74
            color: "#ffffff"
            text: "Move your files to the created folder."
            font.bold: false
            font.pointSize: 10
        }
    }
}
