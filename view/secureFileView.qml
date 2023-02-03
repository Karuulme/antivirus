import QtQuick 2.12

Rectangle {
    width: 675
    height: 40
    color: "#f4f4f4"
    property string fPath: ""
    property string fKey: ""
    Text {
        x: 8
        y: 6
        text:fPath
        font.pointSize: 9
    }
    Text {
        x: 20
        y: 25
        text:"-"+fKey
        font.pointSize: 7
    }
    Text {
        id: text1
        text: qsTr("Open Folder")
        verticalAlignment: Text.AlignVCenter
        leftPadding: 30
        font.pointSize: 10
        x: 429
        y: 11
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
        x: 557
        font.pointSize: 10
        leftPadding: 30
        width: 110
        y: 11
        Image {
            y:-5
            source: "../Image/icons8-delete-document-48.png"
            width: 28
            height:28
        }
    }

}
