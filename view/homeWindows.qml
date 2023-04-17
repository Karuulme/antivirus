import QtQuick 2.0
import QtQuick.Window 2.0
import QtQuick.Controls 2.0
Rectangle {
    id: rectangle
    property variant stringList: system.storageList.split("@")
    property bool kTextBackColor: false
    property bool scroolBarControl: false
    width: 930
    height: 470
    visible: true
    color: "#f2f2f2"
    Rectangle{
        x: 0
        y: 0
        color: "#00000000"
        width: 420
        height: 462
        ScrollView {
            width: parent.width
            height: parent.height
            Column{
                id:listHDD
                x: 0
                y: 40
                width: parent.width
                height: parent.height-40
                spacing: 5
                state: {
                    var component = Qt.createComponent("itemHDD.qml");
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
            radius: 5
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
                        system.set_get_storage()
                    }
                }
            }
        }
    }
   /* Rectangle{
        width: 1
        height: parent.height-65
        color: "#b9b9b9"
        anchors.left: listHDD.right
        anchors.leftMargin:15
        visible: false
        y:50
    }*/
    Rectangle{
        x: 334
        width: 460
        height: 394
        color:"#00000000"
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.topMargin: 5
        anchors.rightMargin: 5
        clip:true
        ScrollView {
            width: parent.width
            height: parent.height
            Column{
                width: parent.width
                height: parent.height
                spacing: 5
                state:{
                        if(system.scanedFileName){
                            var scanedFileName=system.scanedFileName
                            var KText = Qt.createComponent("KText.qml");
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
    Text {
        id: name
        x: 3
        y: 6
        text: qsTr("Active Drivers")
        font.pointSize: 15
    }



    /*BusyIndicator {
        id: busyIndicator
        x: 514
        y: 144
        width: 50
        height: 50
        running: system.scandisk_status
    }*/
    Rectangle {
        id: scanResultOptions
        width: 338
        height: 80
        color: "#00000000"
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.rightMargin: 15
        anchors.bottomMargin: -15
        state: {
            var component = Qt.createComponent("scanresultsOptions.qml");
            var object = component.createObject(scanResultOptions);
            return true
        }
    }
}
