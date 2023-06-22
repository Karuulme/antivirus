import QtQuick 2.0
import QtQuick.Window 2.0
import QtQuick.Controls 2.0

Rectangle {
    id: rectangle
    property variant stringList: filepathtransactions.storageList.split("@")
    property bool kTextBackColor: false
    property bool scroolBarControl: false
    property int virusOptionIndex: 0
    property int computerOptionIndex: 0
    property int automatically_Index: 0
    width: 925
    height: 490
    visible: true
    color: "#f2f2f2"
    /*TextInput {
    id: textInput
    x: 213
    y: 462
    width: 246
    height: 20
    color: "#000000"
    text: qsTr("Text Input")
    font.pixelSize: 12
    Button {
    x: -111
    y: 1
    width: 81
    height: 20
    text: qsTr("Scan")
    onClicked: filepathtransactions.setTest(textInput.text)
    }
    }*/
    Rectangle{
        id: rectangle1
        y: 0
        color: "#00000000"
        anchors.left: parent.left
        anchors.leftMargin: 20
        width: 420
        height: 462
        ScrollView {
            width: parent.width
            height: parent.height
            anchors.left: parent.left
            anchors.leftMargin: 10
            Column {
                id: listHDD
                x: 0
                y: 40
                width: parent.width
                height: parent.height-40
                spacing: 5
                state: {
                    var component = Qt.createComponent("DriversView.qml");
                    for(var i=0;i<stringList.length-1;i++){
                        var disk = stringList[i].split("/")
                        var object = component.createObject(this);
                        object.dName=disk[0]
                        object.dTotal=disk[1]
                        object.dFree=disk[2]
                    }
                    return true
                }
            }


        }
        Rectangle{
            x: 295
            y: 7
            width:25
            height: 25
            color:"#00000000"
            radius: 4
            anchors.right: parent.right
            anchors.rightMargin: 10
            Image {
                id: image1
                width: 25
                height: 25
                source: "../Image/icons8-refresh-96.png"
                fillMode: Image.PreserveAspectFit
                MouseArea{
                    hoverEnabled: true
                    onEntered: {
                        parent.parent.color="#e3e3e3"
                    }
                    onExited: {
                        parent.parent.color="#00000000"
                    }
                    anchors.fill: parent
                    onClicked: {
                        for(var i = listHDD.children.length; i > 0 ; i--) {
                          listHDD.children[i-1].destroy()
                        }
                        filepathtransactions.set_get_storage()
                    }
                }
            }
        }
        Text {
            id: name
            x: 10
            y: 6
            text: qsTr("Active Drivers")
            font.pointSize: 15
        }
    }
    Rectangle{
        x: 465
        width: 460
        height: parent.height
        color: "#00000000"
        anchors.right: parent.right
        anchors.rightMargin: 0
        z:0
        Image {
            source: "../Image/back3.jpg"
            anchors.fill: parent
        }
        visible: {
            if(0<malwareList.children.length){
               return false
            }
            else{
                return true
            }
        }
    }
    Rectangle{
        id:suspiciousFile_id
        z:1
        width: 460
        height: 353
        color:"#00000000"
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.topMargin: 5
        anchors.rightMargin: 0
        clip:true
        visible: {
            if(0<malwareList.children.length){
               return true
            }
            else{
                return false
            }
        }
        ScrollView {
            width: parent.width
            height: parent.height
            anchors.right: parent.right
            anchors.rightMargin: 0
            Column{
                id:malwareList
                width: parent.width
                height: parent.height-10
                spacing: 5
                state:{
                    if(filepathtransactions.scanedFileName){
                        var scanedFileName=filepathtransactions.scanedFileName;
                        var KText = Qt.createComponent("ScanedFileView.qml");
                        var objectKText = KText.createObject(this);
                        var values=scanedFileName.split("q:*!");
                        objectKText.vFileName=values[0];
                        objectKText.dindex=parseInt(values[1]);
                        objectKText.vFileAddress=values[2]
                    }
                    return true;
                }
            }


        }
    }

    Rectangle{
        id: rectangle2
        width: suspiciousFile_id.width
        anchors.right: parent.right
        anchors.top: suspiciousFile_id.bottom
        anchors.bottom: parent.bottom
        anchors.topMargin: 5
        anchors.bottomMargin: 0
        anchors.rightMargin: 0
        color: "#00000000"
        visible: {
            if(0<malwareList.children.length){
               return true
            }
            else{
                return false
            }
        }
        Rectangle{
            id: rectangle3
            width: 455
            radius: 4
            border.width: 1
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.rightMargin: 5
            anchors.bottomMargin: 5
            anchors.topMargin:0
            border.color: "#d5d5d5"
            Column{
                width: 160
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.leftMargin: 10
                anchors.bottomMargin: 5
                anchors.topMargin: 10
                spacing: 10
                Rectangle{
                    id: rectangle5
                    width: 130
                    height: 30
                    radius: 4
                    MouseArea{
                        z:11
                        anchors.fill: parent
                        onClicked: {
                            virusOptionIndex=0
                            filepathtransactions.set_VirusComputerOption(virusOptionIndex,computerOptionIndex)
                        }
                    }
                    color:{
                        if(virusOptionIndex===0){
                            return "#ebebeb"
                        }
                        else{
                            return "#00000000"
                        }
                    }
                    Rectangle{
                        border.width: 1
                        anchors.left: parent.left
                        anchors.top: parent.top
                        anchors.bottom: parent.bottom
                        anchors.leftMargin: 2
                        anchors.bottomMargin: 2
                        anchors.topMargin: 2
                        radius: 4
                        border.color: "#d5d5d5"
                        width: height
                        Image{
                            anchors.fill: parent
                            source: "../Image/customize.png"
                            anchors.rightMargin: 4
                            anchors.leftMargin: 4
                            anchors.bottomMargin: 4
                            anchors.topMargin: 4
                        }
                    }
                    Text {
                        anchors.fill: parent
                        verticalAlignment: Text.AlignVCenter
                        anchors.leftMargin: 35
                        text: qsTr("Custom")
                        font.pointSize: 10
                        color: "#0f172a"
                    }
                }
                Rectangle{
                    id: rectangle6
                    width: 130
                    height: 30
                    radius: 4
                    MouseArea{
                        z:11
                        anchors.fill: parent
                        onClicked: {
                            virusOptionIndex=1
                            filepathtransactions.set_VirusComputerOption(virusOptionIndex,computerOptionIndex)
                        }
                    }
                    color:{
                        if(virusOptionIndex===1){
                            return "#ebebeb"
                        }
                        else{
                            return "#00000000"
                        }
                    }
                    Rectangle{

                        border.width: 1
                        anchors.left: parent.left
                        anchors.top: parent.top
                        anchors.bottom: parent.bottom
                        anchors.leftMargin: 2
                        anchors.bottomMargin: 2
                        anchors.topMargin: 2
                        radius: 4
                        border.color: "#d5d5d5"
                        width: height
                        Image{
                            anchors.fill: parent
                            source: "../Image/protection.png"
                            anchors.rightMargin: 4
                            anchors.leftMargin: 4
                            anchors.bottomMargin: 4
                            anchors.topMargin: 4
                        }
                    }
                    Text {
                        anchors.fill: parent
                        verticalAlignment: Text.AlignVCenter
                        anchors.leftMargin: 35
                        text: qsTr("Quarantine")
                        font.pointSize: 10
                        color: "#0f172a"
                    }
                }
                Rectangle{
                    id: rectangle4
                    width: 130
                    height: 30
                    radius: 4
                    MouseArea{
                        z:11
                        anchors.fill: parent
                        onClicked: {
                            virusOptionIndex=2
                            filepathtransactions.set_VirusComputerOption(virusOptionIndex,computerOptionIndex)
                        }
                    }
                    color:{
                        if(virusOptionIndex===2){
                            return "#ebebeb"
                        }
                        else{
                            return "#00000000"
                        }
                    }
                    Rectangle{

                        border.width: 1
                        anchors.left: parent.left
                        anchors.top: parent.top
                        anchors.bottom: parent.bottom
                        anchors.leftMargin: 2
                        anchors.bottomMargin: 2
                        anchors.topMargin: 2
                        radius: 4
                        border.color: "#d5d5d5"
                        width: height
                        Image{
                            anchors.fill: parent
                            source: "../Image/trash.png"
                            anchors.rightMargin: 4
                            anchors.leftMargin: 4
                            anchors.bottomMargin: 4
                            anchors.topMargin: 4
                        }
                    }
                    Text {
                        anchors.fill: parent
                        verticalAlignment: Text.AlignVCenter
                        anchors.leftMargin: 35
                        text: qsTr("Remove All")
                        font.pointSize: 10
                        color: "#0f172a"
                    }
                }

            }

            Column {
                x: -7
                y: -7
                width: 142
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                Rectangle {
                    width: 130
                    height: 30
                    color: {
                        if(computerOptionIndex===0){
                            return "#ebebeb"
                        }
                        else{
                            return "#00000000"
                        }
                    }
                    radius: 4
                    MouseArea{
                        z:11
                        anchors.fill: parent
                        onClicked: {
                            computerOptionIndex=0
                            filepathtransactions.set_VirusComputerOption(virusOptionIndex,computerOptionIndex)
                        }
                    }

                    Rectangle {
                        width: height
                        radius: 4
                        border.color: "#d5d5d5"
                        border.width: 1
                        anchors.left: parent.left
                        anchors.top: parent.top
                        anchors.bottom: parent.bottom
                        Image {
                            anchors.fill: parent
                            source: "../Image/time-left.png"
                            anchors.bottomMargin: 4
                            anchors.rightMargin: 4
                            anchors.leftMargin: 4
                            anchors.topMargin: 4
                        }
                        anchors.bottomMargin: 2
                        anchors.leftMargin: 2
                        anchors.topMargin: 2
                    }

                    Text {
                        color: "#0f172a"
                        text: qsTr("Wait")
                        anchors.fill: parent
                        verticalAlignment: Text.AlignVCenter
                        font.pointSize: 10
                        anchors.leftMargin: 35
                    }
                }

                Rectangle {
                    width: 130
                    height: 30
                    color: {
                        if(computerOptionIndex===1){
                            return "#ebebeb"
                        }
                        else{
                            return "#00000000"
                        }
                    }
                    radius: 4

                    MouseArea{
                        z:11
                        anchors.fill: parent
                        onClicked: {
                            computerOptionIndex=1
                            filepathtransactions.set_VirusComputerOption(virusOptionIndex,computerOptionIndex)
                        }
                    }

                    Rectangle {
                        width: height
                        radius: 4
                        border.color: "#d5d5d5"
                        border.width: 1
                        anchors.left: parent.left
                        anchors.top: parent.top
                        anchors.bottom: parent.bottom
                        Image {
                            anchors.fill: parent
                            source: "../Image/computer.png"
                            anchors.bottomMargin: 4
                            anchors.rightMargin: 4
                            anchors.leftMargin: 4
                            anchors.topMargin: 4
                        }
                        anchors.bottomMargin: 2
                        anchors.leftMargin: 2
                        anchors.topMargin: 2
                    }

                    Text {
                        color: "#0f172a"
                        text: qsTr("Restart")
                        anchors.fill: parent
                        verticalAlignment: Text.AlignVCenter
                        font.pointSize: 10
                        anchors.leftMargin: 35
                    }
                }

                Rectangle {
                    width: 130
                    height: 30
                    color: {
                        if(computerOptionIndex===2){
                            return "#ebebeb"
                        }
                        else{
                            return "#00000000"
                        }
                    }
                    radius: 4

                    MouseArea{
                        z:11
                        anchors.fill: parent
                        onClicked: {
                            computerOptionIndex=2
                            filepathtransactions.set_VirusComputerOption(virusOptionIndex,computerOptionIndex)
                        }
                    }

                    Rectangle {
                        width: height
                        radius: 4
                        border.color: "#d5d5d5"
                        border.width: 1
                        anchors.left: parent.left
                        anchors.top: parent.top
                        anchors.bottom: parent.bottom
                        Image {
                            anchors.fill: parent
                            source: "../Image/close (1).png"
                            anchors.bottomMargin: 4
                            anchors.rightMargin: 4
                            anchors.leftMargin: 4
                            anchors.topMargin: 4
                        }
                        anchors.bottomMargin: 2
                        anchors.leftMargin: 2
                        anchors.topMargin: 2
                    }

                    Text {
                        color: "#0f172a"
                        text: qsTr("Shut Down")
                        anchors.fill: parent
                        verticalAlignment: Text.AlignVCenter
                        font.pointSize: 10
                        anchors.leftMargin: 35
                    }
                }
                anchors.bottomMargin: 5
                anchors.leftMargin: 185
                anchors.topMargin: 10
                spacing: 10
            }
            Rectangle{
                x: 346
                y: 16
                width: 100
                height: 55
                Text {
                    x: 0
                    y: 0
                    text: qsTr("Automatically")
                }
                Rectangle{
                    id: rectangle8
                    x: 0
                    y: 16
                    radius: 4
                    border.width: 1
                    border.color: "#ededed"

                    width: 100
                    height: 23
                    Rectangle{
                        width: 40
                        height: 19
                        radius: 4
                        anchors.left: parent.left
                        anchors.top: parent.top
                        anchors.leftMargin: 2
                        anchors.topMargin: 2
                        color:{
                            if(automatically_Index===1){
                                return "#ebebeb"
                            }
                            else{
                                return "#ffffff"
                            }
                        }
                        Text {
                            anchors.fill: parent
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            text: qsTr("On")
                        }
                        MouseArea{
                            anchors.fill: parent
                            onClicked: automatically_Index=1
                        }
                    }
                    Text {
                        x: 47
                        y: 2
                        text: qsTr("/")
                    }
                    Rectangle{
                        width: 40
                        height: 19
                        radius: 4
                        anchors.right: parent.right
                        anchors.top: parent.top
                        anchors.rightMargin: 2
                        anchors.topMargin: 2
                        color:{
                            if(automatically_Index===0){
                                return "#ebebeb"
                            }
                            else{
                                return "#ffffff"
                            }
                        }
                        Text {
                            anchors.fill: parent
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            anchors.topMargin: 0
                            text: qsTr("Off")
                        }
                        MouseArea{
                            anchors.fill: parent
                            onClicked: automatically_Index=0
                        }
                    }

                }
            }


            Rectangle{
                id: rectangle7
                x: 345
                y: 90
                width: 100
                height: 30
                radius: 4
                color:"#f3f4f6"
                Text {
                    anchors.fill: parent
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    text: qsTr("Enforce ->")
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked:{
                            //filepathtransactions.set_ScanResultApply()
                            for(var i = malwareList.children.length; i > 0 ; i--) {
                            malwareList.children[i-1].destroy()
                        }
                    }
                }

                Rectangle{
                    height: 2
                    anchors.bottom: parent.bottom
                    anchors.leftMargin: 2
                    anchors.rightMargin: 2
                    anchors.bottomMargin: 0
                    color:"#6366f1"
                    anchors.left: parent.left
                    anchors.right: parent.right
                }
            }


        }


    }
/*

                    MouseArea{
                        z:11
                        anchors.fill: parent
                        onClicked: {
                            computerOptionIndex=2
                            filepathtransactions.set_VirusComputerOption(virusOptionIndex,computerOptionIndex)
                        }
                    }
/*

    /*BusyIndicator {
        id: busyIndicator
        x: 514
        y: 144
        width: 50
        height: 50
        running: system.scandisk_status
    }*/
   /* Rectangle {
        z:2
        width: 460
        height: 84
        visible: {
            if(0<malwareList.children.length){
               return true
            }
            else{
                return false
            }
        }
        color:"#00000000"
        property int virusOptionIndex: 0
        property int computerOptionIndex: 0
        x: 470
        y: 218
        ComboBox {
            visible: false
            model:ListModel {
                id: virusOption
                ListElement { text:"Custom";}
                ListElement { text:"Quarantine All"; }
                ListElement { text:"Delete Everything"; }
                }
        }
        ComboBox {
            visible: false
            model:ListModel {
                id: computerOption
                ListElement { text:"Wait" ;}
                ListElement { text:"Shut Down"; }
                ListElement { text:"Restart"; }
                }
        }
        Rectangle {
            x: 0
            y: 0
            width: 299
            height: 30
            color: "#00000000"
            Label {
                x: 82
                y: 5
                width: 90
                height: 25
                color: "#202937"
                text: qsTr(virusOption.get(virusOptionIndex).text)
                horizontalAlignment: Text.AlignRight
                font.pointSize: 9
                font.bold: true
            }

            Label {
                x: 199
                y: 5
                width: 140
                height: 25
                color: "#202937"
                text: qsTr(computerOption.get(computerOptionIndex).text)
                horizontalAlignment: Text.AlignLeft
                font.pointSize: 9
                font.bold: true
            }

            Label {
                x: 177
                y: 1
                width: 15
                height: 25
                color: "#202937"
                text: qsTr("&")
                horizontalAlignment: Text.AlignHCenter
                font.pointSize: 13
                font.bold: true
            }
            Image {
                id: image2
                width: 30
                height: 30
                anchors.left: parent.left
                source: "../Image/icons8-left-67.png"
                anchors.leftMargin: 0
                z:10
                MouseArea{
                    z:11
                    anchors.fill: parent
                    onClicked: {
                        if(virusOptionIndex>=2)
                            virusOptionIndex=0;

                        else
                            virusOptionIndex++
                        filepathtransactions.set_VirusComputerOption(virusOptionIndex,computerOptionIndex)
                    }

                }
            }

            Image {
                id: image3
                x: 309
                y: 0
                width: 30
                height: 30
                anchors.right: parent.right
                source: "../Image/icons8-right-67.png"
                anchors.rightMargin: -40

                z:10
                MouseArea{
                    z:11
                    anchors.fill: parent
                    onClicked: {
                        if(computerOptionIndex>=2)
                            computerOptionIndex=0;
                        else
                            computerOptionIndex++
                        filepathtransactions.set_VirusComputerOption(virusOptionIndex,computerOptionIndex)
                    }

                }
            }
        }
        Rectangle{
            x: 278
            y: 46
            width: 181
            height: 40
         //   color: "#15b789"
            color:"#0047ab"
            border.width: 1
            border.color: "#f9f9f9"
            radius: 4
            Text {
                x: 77
                y: 10
                height: 21
                text: qsTr("Apply")
                font.bold: true
                font.pointSize: 10
                color:"#ffffff"
            }
            MouseArea{
                anchors.fill: parent
                anchors.bottomMargin: 0
                anchors.leftMargin: 0
                anchors.topMargin: 1
                anchors.rightMargin: 0
                onClicked:filepathtransactions.set_ScanResultApply()
            }
        }

        Switch {
            id: switch1
            x: -6
            y: 48
            width: 130
            height: 30
            text: qsTr("Auto Apply")
            autoRepeat: false
            autoExclusive: false
            checked: false
            onCheckedChanged: filepathtransactions.set_ScanResultAutoApply(switch1.checked ? 1:0)
        }
        //auto apply

    }*/

}
