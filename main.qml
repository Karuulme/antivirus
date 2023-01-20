import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.15

Window {
    property variant stringList: system.storageList.split("@")
    property int windowstastbar_close_icon: 0
    property int scroolbarIndex: 0
    id: window
    width: 690
    height: 480
    visible: true
    color: "#f4f4f4"
    visibility: Window.Windowed
    maximumHeight: 480
    minimumHeight: 480
    maximumWidth: 850
    minimumWidth: 690
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
        height: parent.height-100
        color: "#b9b9b9"
        anchors.left: listHDD.right
        anchors.leftMargin:15
        y:50

    }
    Column{
        id: windows_log
        x: 391
        y: 50
        width: 284

        height: 380
        spacing: 5
            Connections{
                target:system
                onScanedFileName_changed:{
                    scroolbarIndex++;
                    var component2 = Qt.createComponent("KText.qml");
                    var object2 = component2.createObject(windows_log);
                    object2.dName="->"+scanedFileName
                    windows_log.width=20*scroolbarIndex
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
        width: 360
        height: 25
        spacing: 25
        Rectangle{
            width: 25
            height: 25
            color:"#00000000"
            radius: 5
            Image {
                id: image1
                width: 25
                height: 25
                source: "Image/icons8-refresh-96.png"//
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
}






