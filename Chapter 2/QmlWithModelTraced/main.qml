import QtQuick 2.9
import QtQuick.Controls 2.2


Page {
    width: 640
    height: 480

    header: Label {
        horizontalAlignment: Text.AlignHCenter
        color: "#15af15"
        text: qsTr("Where do people use Qt?");
        font.pointSize: 27
        font.bold: true
        font.family: "Arial"
    }

    Rectangle {
        id: root
        width: parent.width
        height: parent.height

        property int margin: 25

            Image {
                anchors.fill: parent
                anchors.rightMargin: 2 * parent.margin
                anchors.leftMargin: 2 * parent.margin
                anchors.topMargin: parent.margin
                anchors.bottomMargin: parent.margin
                id: image
                source: "qt-logo.png"
            }

            ListView {
                id: view
                anchors.fill: parent
                anchors.rightMargin: parent.margin
                anchors.leftMargin: parent.margin
                anchors.topMargin: parent.margin
                anchors.bottomMargin: parseInt(3 * parent.margin / 2)

                model: myModel
                delegate: Text {
                    font.pointSize: 15
                    horizontalAlignment: Text.AlignHCenter
                    text: modelData
                }
        }
    }
}
