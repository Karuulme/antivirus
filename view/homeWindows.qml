import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.15
Rectangle {
    id: rectangle
    property variant stringList: system.storageList.split("@")
    property int windowstastbar_close_icon: 0
    property bool kTextBackColor: false
    property bool scroolBarControl: false
    width: 700
    height: 470
    visible: true
    color: "#f2f4f7"
    Column {
        id: listHDD
        x: 0
        y: 0
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
            return true
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
        x: 361
        width: 338
        color:"#00000000"
        anchors.top: parent.top
        anchors.bottom: scanResultOptions.top
        anchors.bottomMargin: 0
        anchors.topMargin: 0
        clip: true
        z:50
        Column{
            id: windows_log_colmn
            width: 318
            z:51
            onChildrenChanged: {
                if(!scroolBarControl){
                    if(height>300){
                       console.log("vlaue");
                        scroolBarControl=true
                    }
                }
            }
        }
        Rectangle{
            id:windows_log_scrool_bar
            width: 5
            visible:true// scroolBarControl
            height: 150
            color: "#acacac"
            onYChanged: {
                if(windows_log_scrool_bar.visible){
                    windows_log_colmn.y=- windows_log_scrool_bar.y*(windows_log_colmn.height-windows_log.height)/(windows_log.height-windows_log_scrool_bar.height)
                }
            }
            radius:10
            anchors.right: parent.right
            anchors.rightMargin:0
            MouseArea{
                property bool scroolBarEffect: false
                anchors.fill: parent
                 drag.target: parent
                 drag.axis: Drag.YAxis
                 drag.maximumX: 0
                 drag.minimumX: 0
                 drag.maximumY: windows_log.height/2+34
                 drag.minimumY: 0
                 hoverEnabled: true
                 onEntered:parent.width=10
                 onExited: {
                     if(!scroolBarEffect){
                          parent.width=5
                     }
                 }
                 onPressed:scroolBarEffect=true
                 onReleased:{
                     parent.width=5
                     scroolBarEffect=false
                 }
            }
        }
        state:{
            if(system.scanedFileName){
                var scanedFileName=system.scanedFileName
                var KText = Qt.createComponent("KText.qml");
                var objectKText = KText.createObject(windows_log_colmn);
                var values=scanedFileName.split("q:");
                objectKText.dName=values[0];
                objectKText.dindex=parseInt(values[1]);
                if(!windows_log_scrool_bar.visible){
                   // var vlaue=windows_log_colmn.height;

                  //  if(windows_log_colmn.height>400){
                       // windows_log_scrool_bar.visible=true;
                  //  }

                }
            }
            return true
        }
        MouseArea{
            anchors.fill: parent
            anchors.rightMargin: 10
            z:100
            onWheel: {
                if(windows_log_scrool_bar){
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
                    "../Image/icons8-close-64.png"
                    }
                else{
                    windowsTaskBar_close.color= "#EDEDED"
                    "../Image/icons8-close-red-64.png"
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
        x: 0
        y: 386
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
                        system.set_get_storage()
                    }
                }
            }
        }
    }
    BusyIndicator {
        id: busyIndicator
        x: 514
        y: 144
        width: 50
        height: 50
        running: system.scandisk_status
    }
    Rectangle {
        id: scanResultOptions
        width: 338
        height: 80
        color: "#00000000"
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.rightMargin: 0
        anchors.bottomMargin: 25
        state: {
            var component = Qt.createComponent("scanresultsOptions.qml");
            var object = component.createObject(scanResultOptions);
            return true
        }
    }
}
