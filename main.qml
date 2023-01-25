import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.15
Window {
    property variant stringList: system.storageList.split("@")
    property int windowstastbar_close_icon: 0
    property bool kTextBackColor: false
    property bool scroolBarControl: false
    id: window
    width: 720
    height: 500
    visible: true
    color: "#f4f4f4"
   // color:"#f6f6f6"
    visibility: Window.Windowed

    contentOrientation: Qt.PortraitOrientation
    modality: Qt.WindowModal
   // flags: Qt.Drawer
    flags: Qt.Window
    title: qsTr("")
    Column {
        id: listHDD
        x: 19
        y: 50
        width: 340
        height: 380
        spacing: 5
        state: {
            var component = Qt.createComponent("itemHDD.qml");

            for(var i=0;i<stringList.length-1;i++){
                var disk = stringList[i].split("/")
                var object = component.createObject(listHDD);
                object.dName=disk[0]
                object.dTotal=disk[1]
                object.dFree=disk[2]
            }
        }
    }
    Rectangle{
        width: 1
        height: parent.height-65
        color: "#b9b9b9"
        anchors.left: listHDD.right
        anchors.leftMargin:15
        visible: false
        y:50
    }
    Rectangle{
        id:windows_log
        x: 381
        y: 50
        width: 338
        height: 368
        color:"#00000000"
        clip: true
        z:50
        Column{
            id: windows_log_colmn
            width: 318
            z:51
            Connections{
                target:system
                onScanedFileName_changed:{
                    var component2 = Qt.createComponent("KText.qml");
                    var object2 = component2.createObject(windows_log_colmn);
                    var values=scanedFileName.split("q:")
                    object2.dName=values[0]
                    object2.dindex=values[1]
                    if(kTextBackColor===false){
                        object2.backColor="#e3e3e3"
                        kTextBackColor=true
                    }
                    else
                        kTextBackColor=false
                    if(windows_log_colmn.height-windows_log.height>0){
                        scroolBarControl=true
                    }
                }
            }
        }
        Rectangle{
            id:windows_log_scrool_bar
            width: 10
            visible: scroolBarControl
            height: 150
            color: "#acacac"
            onYChanged: {
                if(scroolBarControl){
                    windows_log_colmn.y=- windows_log_scrool_bar.y*(windows_log_colmn.height-windows_log.height)/(windows_log.height-windows_log_scrool_bar.height)
                }
            }
            radius:10
            anchors.right: parent.right
            anchors.rightMargin:0
            MouseArea{
                anchors.fill: parent
                 drag.target: parent
                 drag.axis: Drag.YAxis
                 drag.maximumX: 0
                 drag.minimumX: 0
                 drag.maximumY: windows_log.height/2+34
                 drag.minimumY: 0
            }
        }
        MouseArea{
            anchors.fill: parent
            anchors.rightMargin: 10
            onWheel: {
                if(scroolBarControl){
                    if (wheel.angleDelta.y > 0)
                    {
                        if(windows_log_scrool_bar.y>0){
                            windows_log_scrool_bar.y-=10
                        }
                        else{
                            windows_log_scrool_bar.y=0
                        }
                    }
                    else
                    {
                        if(windows_log_scrool_bar.y<windows_log.height/2+34){
                            windows_log_scrool_bar.y+=10
                        }
                        else{
                             windows_log_scrool_bar.y=218
                        }
                    }
                    wheel.accepted=true
                }
            }
        }
    }
    Rectangle{
        x: 820
        y: 5
        width: 25
        height: 25
        id:windowsTaskBar_close
        color:"#00000000"
        Image {
            id: image
            width: 25
            height: 25
            source:{
                if(windowstastbar_close_icon==0){
                   windowsTaskBar_close.color= "#00000000"
                    "Image/icons8-close-64.png"
                    }
                else{
                    windowsTaskBar_close.color= "#EDEDED"
                    "Image/icons8-close-red-64.png"
                }
            }
            fillMode: Image.PreserveAspectFit
            MouseArea{
                anchors.fill: parent
                onClicked: windowstaskbar.windowsClose()
                hoverEnabled: true
                onEntered: {
                    windowstastbar_close_icon=1
                }
                onExited: {
                    windowstastbar_close_icon=0
                }
            }
        }
    }
    Row {
        id: row
        x: 30
        y: 436
        width: 329
        height: 30
        spacing: 30
        Rectangle{
            width:30
            height: 30
            color:"#00000000"
            radius: 5
            Image {
                id: image1
                width: 30
                height: 30
                source: "Image/icons8-refresh-96.png"
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
                        system.set_get_storage()
                    }
                }
            }
        }


    }

    BusyIndicator {
        id: busyIndicator
        x: 520
        y: 209
        width: 50
        height: 50
        running: system.scandisk_status
    }

    Rectangle {
        id: scanResultOptions
        x: 379
        y: 420
        width: 338
        height: 80
        color: "#00000000"
        state: {
            var component = Qt.createComponent("scanresultsOptions.qml");
            var object = component.createObject(scanResultOptions);
        }

    }


}







