import QtQuick 2.12
import QtQuick.Controls 2.15
Rectangle {
    property string backColor:"#f2f4f7"
    color:backColor
    height: 25
    width: 320
    property string dName: "Null"
    property int dindex: 0
    property int dselectIndex: 0
    Text {
        id: label
        x: 0
        y: 4
        text: qsTr(dName)

    }
    Image {
        id: quarantinefile
        x: 242
        y: 2
        width: 20
        height: 20
        source: "../Image/icons8-filequarantine.png"
        MouseArea{
            anchors.fill: parent
            anchors.rightMargin: 0
            anchors.bottomMargin: 0
            anchors.leftMargin: 0
            anchors.topMargin: 0
            onClicked:{
                dselectIndex=0
                system.set_singleVirusChanges(dindex,0)
                }
        }
    }
    Image{
        id: tic
        x:{
            if(dselectIndex==1)
                return 302
            else
                return 265
        }
        y: 5
        width: 15
        height: 15
        source: "../Image/icons8-double-tick-48.png"
    }
    Image {
        id: deletefile
        x: 283
        y: 2
        width: 20
        height: 20
        source: "../Image/icons8-filedelete.png"
        MouseArea{
            anchors.fill: parent
            anchors.rightMargin: 0
            anchors.bottomMargin: 0
            anchors.leftMargin: 0
            anchors.topMargin: 0
            onClicked:{
                dselectIndex=1
                system.set_singleVirusChanges(dindex,1)
            }

        }

    }
}

