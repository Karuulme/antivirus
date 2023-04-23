import QtQuick 2.0
import QtQuick.Controls 2.0
Item{
    id: rectangle
    height: 85
    focus: false
    antialiasing: false
    smooth: true
    enabled: true
    width: 435
    property string vFileName: "null.exe"
    property string vFileAddress: "null"
    property int dindex: 0
    property int vSelectIndex: 0
    Rectangle {
        clip: true

        color:"#ffffff"
        height: 85
        width: 440
        border.width: 1
        border.color: "#c8c8c8"
        radius: 4
        Text {
            id:vFileName_id
            width: 43
            height: 18
            text: vFileName
            anchors.left: parent.left
            anchors.top: parent.top
            verticalAlignment: Text.AlignVCenter
            anchors.leftMargin: 5
            anchors.topMargin: 2
            font.pixelSize:{
                if(76<=text.length){
                    console.log(Math.floor(852/text.length))
                    return Math.floor(852/text.length)
                }
                else{
                    return 12
                }
            }

            font.bold: true
            color: "#393939"
        }
        Text {
            width: 430
            text:vFileAddress
            anchors.left: parent.left
            anchors.top: vFileName_id.bottom
            font.pixelSize:12/*{
                if(76<=text.length){
                    console.log(Math.floor(852/text.length))
                    return Math.floor(852/text.length)
                }
                else{
                    return 12
                }
            }*/
            color: "#515151"
            wrapMode: Text.WrapAnywhere
            anchors.leftMargin: 7
            anchors.topMargin: 0 // metni birden fazla satıra bölmek için kullanılır
            horizontalAlignment: Text.AlignLeft

        }
        Rectangle{
            id: rectangle1
            x: 5
            y: 49
            width: 222
            height: 26
            color:"#eeeeee"
            border.width: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 5
            radius: 4
            Rectangle{
                id:vSelect_Id1
                y:1
                x:1
                width: 70
                height: 24
                radius: 4
                color: "#ffffffff"
                Text {
                    anchors.fill: parent
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    anchors.topMargin: 2
                    font.family: "Arial"
                    text: qsTr("Nothing")
                    font.pointSize: 9
                    font.bold:{
                        if(vSelectIndex===0){
                            parent.color="#ffffffff"
                            return true
                        }
                        else{
                            parent.color="#00000000"
                            return false
                        }
                    }
                    MouseArea {
                        anchors.fill: parent
                        onClicked:{vSelectIndex=0
                        filepathtransactions.set_singleVirusChanges(dindex,0)
                        }
                    }
                }
            }
            Rectangle{
                id:vSelect_Id2
                y:1
                width: 70
                height: 24
                radius: 4
                anchors.left: vSelect_Id1.right
                anchors.leftMargin: 5
                color: "#ffffffff"
                Text {
                    anchors.fill: parent
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    anchors.topMargin: 2
                    font.family: "Arial"
                    text: qsTr("Quarantine")
                    font.pointSize: 9
                    font.bold:{
                        if(vSelectIndex===1){
                            parent.color="#ffffffff"
                            return true
                        }
                        else{
                            parent.color="#00000000"
                            return false
                        }
                    }
                    MouseArea {
                        anchors.fill: parent
                        onClicked:{vSelectIndex=1
                        filepathtransactions.set_singleVirusChanges(dindex,1)
                        }
                    }
                }
            }
            Rectangle{
                id:vSelect_Id3
                y:1
                width: 70
                height: 24
                radius: 4
                anchors.left: vSelect_Id2.right
                anchors.leftMargin: 5
                color: "#ffffffff"
                Text {
                    anchors.fill: parent
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    anchors.topMargin: 2
                    font.family: "Arial"
                    text: qsTr("Remove")
                    font.pointSize: 9
                    font.bold:{
                        if(vSelectIndex===2){
                            parent.color="#ffffffff"
                            return true
                        }
                        else{
                            parent.color="#00000000"
                            return false
                        }
                    }
                    MouseArea {
                        anchors.fill: parent
                        onClicked:{vSelectIndex=2
                        filepathtransactions.set_singleVirusChanges(dindex,2)
                        }
                    }
                }
            }

        }

       /* Text {
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
        }*/
        Rectangle{
            x:363
            y:54
            width: 70
            height: 20
            color: "#00000000"
            border.width: 0
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 5
            anchors.rightMargin: 7
            border.color: "#716e6e"
            Text {
                id:enforceId
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

                text: qsTr("Enforce ->")
                font.pointSize: 9
            }
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    if(vSelectIndex!=0){
                        filepathtransactions.getVirusOne(vFileAddress+"\\"+vFileName,vSelectIndex,dindex);
                        rectangle.destroy()
                    }
                }
                hoverEnabled: true
                onEntered: enforceId.font.underline = true
                onExited:  enforceId.font.underline = false
            }
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
}
