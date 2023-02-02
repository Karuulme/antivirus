import QtQuick 2.12

Rectangle {
    width: 675
    height: 30
    color: "#f4f4f4"
    property string fPath: ""
    Text {
        x: 8
        y: 6
        text:fPath
        font.pointSize: 9
    }
    Text {
        id: text1
        text: qsTr("Open Folder")
        verticalAlignment: Text.AlignVCenter
        leftPadding: 30
        font.pointSize: 10
        x: 430
        y: 5
        width: 110

        Image {
            y:-5
            source: "../Image/icons8-open-folder-64.png"
            width: 28
            height:28
        }
        MouseArea{
            anchors.fill: parent
            onClicked: securefile.set_RecureOpenFile(fPath);

        }
    }
    Text {
        text: qsTr("Delete Folder")
        x: 560
        font.pointSize: 10
        leftPadding: 30
        width: 110
        y: 5
        Image {
            y:-5
            source: "../Image/icons8-delete-document-48.png"
            width: 28
            height:28
        }
    }

}
