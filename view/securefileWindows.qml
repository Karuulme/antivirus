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
        height: 370
        anchors.top: rectangle1.bottom
        anchors.topMargin: 40
        state: {
            var componentSecureFileView = Qt.createComponent("secureFileView.qml");
            if(securefile.secureFiles){
                var fileValue=securefile.secureFiles.split(":?!?:");
                if(fileValue[0]==="new"){
                    //Bildirim açılacak
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
    Rectangle {
        id: secureNewFolderNotification
        x: 8
        y: 357
        width: 659
        height: 97
        color: "#04AA6D"
        radius: 7
        border.color: "#006619"
        border.width: 2
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
            text: "C:\Users\karuulme\Desktop\web-projesi"
        }

        Text {
            id: name1
            x: 7
            y: 30
            color: "#ffffff"
            text: "Ouşturduğunuz güvenli dosya adresi altında"
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
            text: "adında klasör oluşturuldu."
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
            text: "Oluşturulan klasöre dosyalarınızı taşıyınız."
            font.bold: false
            font.pointSize: 10
        }
    }
}
