import QtQuick 2.0
import QtQuick.Controls 2.0
Rectangle {
    width: 930
    height: 470
    color: "#f2f2f2"
    property bool userDefinitionsShow: false
    Rectangle{
        x: 115
        y: 256
        width: 700
        height: 200
        color: "#00000000"
        Text {
            id: name
            x: 100
            y: 37
            color: "#252525"
            text: qsTr("CREATING DEFINITION")
            font.pointSize: 11
            font.bold: true
            visible:userDefinitionsShow
        }
        Text {
            id: progressBaryuzdesi
            x: 500
            y: 39
            width: 100
            color: "#252525"
            horizontalAlignment: Text.AlignRight
            font.bold: true
            font.pointSize: 11
            visible:userDefinitionsShow
        }
        Rectangle{
            x: 100
            y: 65
            width: 500
            height: 40
            visible:userDefinitionsShow

            ProgressBar {
                id: control
                property color contentItemColor: "#d5d5d5"
                property color backgroundColor: "#0265dc"
                property color borderColor: "#0265dc"
                property int borderWidth: 1
                property color stripColor: "green"
                property int stripGap: 10
                property int stripWidth: 2
                property color indicatorColor: "#0265dc"
                property int indicatorWidth: 2
                property int indicatorRadius: 0
                property int indicatorExtend: 0
                value:{
                    var retValue;
                    var value=filepathtransactions.userDefinitions_UploadIndexNo
                    var upload=value.split("*&*")
                    if(filepathtransactions.userDefinitions_UploadIndexNo){
                        if(userDefinitionsShow===false){
                            userDefinitionsShow=true
                            to=parseInt(upload[1])-1


                        }
                        progressBaryuzdesi.text=(parseInt(upload[0])*100 / (parseInt(upload[1])-1)).toFixed(1)+"/100.0"
                        console.log(parseInt(upload[1])-1+"----"+parseInt(upload[0]))
                        retValue=parseInt(upload[0]);
                        if(retValue===to){
                            userDefinitionsShow=false
                        }
                        return retValue
                    }
                    return 50;
                }
                to:100
                width: parent.width
                height: parent.height


                background: Rectangle {
                    color: control.backgroundColor
                    border.width: control.borderWidth
                    border.color: control.borderColor

                    Canvas {
                        x: control.borderWidth
                        y: control.borderWidth
                        width: control.width - (2 * control.borderWidth)
                        height: control.height - (2 * control.borderWidth)

                    }
                }
                contentItem: Item {
                    Rectangle {
                        anchors.fill: parent
                        anchors.leftMargin: Math.max(control.borderWidth,
                                                     control.visualPosition * control.width)

                        color: control.contentItemColor
                    }

                    Rectangle {
                        x: control.visualPosition * control.width - (control.indicatorWidth / 2)
                        y: -control.indicatorExtend
                        width: control.indicatorWidth
                        height: control.height + (2 * control.indicatorExtend)
                        color: control.indicatorColor
                        radius: control.indicatorRadius
                        visible: control.visualPosition > 0.0 && control.visualPosition < 1.0
                    }
                }
            }
        }
            Rectangle{
                visible: !userDefinitionsShow
                width: 700
                height: 80
                y: 120
                color: "#00000000"
            TextEdit {
                id: textEdit3
                x: 34
                text: qsTr("Set user definition now with open processes and single programs")
                font.pixelSize: 14
                font.bold: true
            }
            TextEdit {
                id: textEdit4
                x: 34
                y: 20
                text: qsTr("Skips the 200 hour definition time and creates the definition immediately")
                font.pixelSize: 12
                font.bold: false
            }

            Rectangle {
                x: 496
                y: 5
                width: 147
                height: 36
                color: "#0047ab"
                border.width: 1
                radius: 5
                border.color: "#c3c2c2"
                Text {
                    text: qsTr("REBUILD")
                    anchors.fill: parent
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    color: "#ffffff"
                    font.bold: true

                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: userdefinition.setUserDefinition()
                }
            }
        }

    }


}
