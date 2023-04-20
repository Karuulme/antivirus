import QtQuick 2.0
import QtQuick.Controls 2.0
Rectangle {
    id: rectangle
    color:"#f2f2f2"
    height: 70
    width: 440
    property string vFileName: "ConsoleAplication.exe"
    property string vFileAddress: ""
    property int dindex: 0
    property int vSelectIndex: 0
    Text {
        x: 5
        y: 0
        text: vFileName
        font.weight: Font.DemiBold
        font.pointSize: 10
        font.bold: true
        color: "#393939"
    }
    Text {
        x: 7
        y: 22
        text: "-"+vFileAddress
        font.pointSize: 9
        color: "#515151"
    }
    Text {
        x: 8
        y: 48
        text: qsTr("ACTION >")
        font.pointSize: 8
        color:"#333333"
    }
    Text {
        x: 60
        y: 43
        text: qsTr("[")
        font.pointSize: 12
        color:"#333333"
    }
    Text {
        x: 260
        y: 43
        text: qsTr("]")
        font.pointSize: 12
        color:"#333333"
    }
    Text {
        x: 70
        y: 48
        text: qsTr("NOTHING")
        font.pointSize: 8
        color:{
            if(vSelectIndex==0){
                return "#2fce23"
            }
            else{
                return "#333333"
            }

        }
        MouseArea {
            anchors.fill: parent
            onClicked:{vSelectIndex=0
            filepathtransactions.set_singleVirusChanges(dindex,0)
            }
        }
    }
    Text {
        x: 130
        y: 48
        text: qsTr("QUARANTINE")
        font.pointSize: 8
         color:{
            if(vSelectIndex==1){
                return "#170fb4"
            }
            else{
                return "#333333"
            }
        }
        MouseArea {
            anchors.fill: parent
            onClicked:{vSelectIndex=1
            filepathtransactions.set_singleVirusChanges(dindex,1)
            }
        }
    }
    Text {
        x: 210
        y: 48
        text: qsTr("REMOVE")
        font.pointSize: 8
        color:{
            if(vSelectIndex==2){
                return "#ff0000"
            }
            else{
                return "#333333"
            }
        }
        MouseArea {
            anchors.fill: parent
            onClicked:{vSelectIndex=2
            filepathtransactions.set_singleVirusChanges(dindex,2)
            }
        }
    }
    Rectangle{
        x:407
        y:48
        width: 35
        height: 17
        color: "#00000000"
        border.width: 1
        anchors.right: parent.right
        anchors.rightMargin: 8
        border.color: "#716e6e"
        Text {
            x: 4
            y: 0
            text: qsTr("Apply")
            font.pointSize: 8
        }
        MouseArea{
            anchors.fill: parent
            onClicked: {
                if(vSelectIndex!=0){
                    filepathtransactions.getVirusOne(vFileAddress+"\\"+vFileName,vSelectIndex,dindex);
                    rectangle.destroy()
                }
            }
        }
    }
    Rectangle{
        x: 0
        y: 84
        width: parent.width
        height: 1
        color:"#c8c8c8"
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
    }
    /*Image {
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
    }*/
   /* Image{
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
    }*/
   /* Image {
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

    }*/
}

