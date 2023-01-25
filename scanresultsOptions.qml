import QtQuick 2.12
import QtQuick.Controls 2.15
Rectangle {
    width: 340
    height: 80
    color:"#00000000"
    property int virusOptionIndex: 0
    property int computerOptionIndex: 0
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
        id: rectangle
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
            source: "Image/icons8-left-67.png"
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
                    system.set_VirusComputerOption(virusOptionIndex,computerOptionIndex)
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
            source: "Image/icons8-right-67.png"
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
                    system.set_VirusComputerOption(virusOptionIndex,computerOptionIndex)
                }

            }
        }
    }
    Rectangle{
        x: 159
        y: 40
        width: 181
        height: 40
     //   color: "#15b789"
        color:"#0047ab"
        border.width: 1
        border.color: "#f9f9f9"
        radius: 5
        Text {
            id: name
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
            onClicked:system.set_ScanResultApply()
        }
    }

    Switch {
        id: switch1
        x: -5
        y: 44
        width: 130
        height: 30
        text: qsTr("Auto Apply")
        autoRepeat: false
        autoExclusive: false
        checked: false
        onCheckedChanged: system.set_ScanResultAutoApply(switch1.checked ? 1:0)


    }
    //auto apply




}
