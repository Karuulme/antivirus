import QtQuick 2.0
import QtQuick.Controls 2.0
Rectangle{
    id: main
    width: 860
    height: 60
    color: "#f2f2f2"
    property string fPath: ""
    property string fKey: ""
    property bool fileSelect : false //secureProcessed
    state: {
        if(securefile.secureProcessed){
            var returnValue=securefile.secureProcessed.split("!secure!");
            if(returnValue[0]===fKey){
                fileSelect=false
                if(returnValue[1]==="successful"){
                    main.destroy()
                }else{
                    errorLog.visible = false;
                    timer.stop();
                    timerTransformation.start();
                }
            }
        }
        return true
    }
    MouseArea{
        hoverEnabled: true
        anchors.fill: parent
        onDoubleClicked:securefile.set_RecureOpenFile(fPath);
        onHoveredChanged:{
            rectangle.color="#f2f2f2"//"#ededed"
        }
        onExited: {
            rectangle.color="#f9f9f9"
        }
    }
    Rectangle{
        id:errorLog
        x: 404
        y: 60
        visible: false
        width: 90
        height: 10
        z:20
        border.width: 0
        color: "#00000000"
        Text {
            id: name
            x: -2
            y: -2
            color: "#d73c3c"
            text: qsTr("Something Went Wrong")
            font.pointSize: 7
        }
    }
    Timer {
        id: timerTransformation
        interval: 1000
        onTriggered: {
            timer.start()
            errorLog.visible = true;
        }
    }
    Timer {
        id: timer
        interval: 5000 // 5 seconds
        onTriggered: {
            errorLog.visible = false;
        }
    }
    Rectangle{
        id:approvalWindow
        y:2
        visible: false
        width: parent.width-64
        height: parent.height-4
        color: "#f9f9f9"
        anchors.left: parent.left
        anchors.leftMargin: 60
        border.width: 0
        z:50
        Text {
            x: 540
            y: 19
            text: qsTr("Do you want to do this?")
            font.pointSize: 10
        }
        Text {
            x: 703
            y: 17
            text: qsTr("Yes")
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            width: 35
            height: 22
            font.pointSize: 10
            MouseArea{
                anchors.fill: parent
                onClicked:{
                    parent.parent.visible=false
                    securefile.set_RecureDeleteFile(fKey,fPath);
                }
            }
        }
        Rectangle{
            x: 744
            y: 16
            width: 1
            height: 25
            color: "#999999"
        }
        Text {
            x: 753
            y: 17
            text: qsTr("No")
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            width: 35
            height: 22
            font.pointSize: 10
            MouseArea{
                anchors.fill: parent
                onClicked:{
                    parent.parent.visible=false
                    fileSelect=false
                }
            }
        }
    }
    Rectangle{
        id: rectangle
        width: 860
        height: 60
        color: "#f9f9f9"
        border.width: 1
        border.color: "#b9b9b9"
        radius: 4
        Rectangle{
            width: 43
            height: 43
            x:8
            y:9
            border.width:0
            radius: 100
            color:"#54c384"
            Image {
                y:7
                x:6.5
                width: 30
                height:30
                source: "../Image/icons8-protect-50.png"
            }
        }

        Text {
            x: 60
            y: 12
            text:fPath
            font.pointSize: 9
        }
        Text {
            x: 60
            y: 31
            text:"Key: "+fKey
            font.pointSize: 9
        }
        Rectangle{
            visible: fileSelect
            width: 180
            height: 28
            x: 644
            y: 16
            z: 100
            color: "#00000000"

            Text {
                //visible: false
                width: 80
                height: 25
                text: qsTr("Open File")
                horizontalAlignment: Text.AlignRight
                verticalAlignment: Text.AlignVCenter
                Image {
                    width: 28
                    height:28
                    source: "../Image/icons8-open-folder-64.png"
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: securefile.set_RecureOpenFile(fPath);

                }
            }
            Text {
                //visible: false
                x:110
                width: 65
                height: 25
                text: qsTr("Delete")
                horizontalAlignment: Text.AlignRight
                verticalAlignment: Text.AlignVCenter
                Image {
                    width: 28
                    height:28
                    source: "../Image/icons8-delete-document-48.png"
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        approvalWindow.visible=true
                    }

                }

            }
               }
        Image {
            x: 830
            y: 15
            visible: !fileSelect
            width: 30
            height: 30
            source: "../Image/icons8-menu-78.png"
            MouseArea{
                anchors.fill: parent
                onClicked: fileSelect=true
            }
        }
        Image {
            x: 833
            y: 17
            visible: fileSelect
            width: 25
            height: 25
            source: "../Image/icons8-close-64.png"
            MouseArea{
                anchors.fill: parent
                onClicked: fileSelect=false
            }
        }



    }
}
