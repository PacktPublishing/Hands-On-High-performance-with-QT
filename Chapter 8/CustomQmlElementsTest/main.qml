import QtQuick 2.9
import QtQuick.Window 2.2

import	CustomShapes 1.0


Window {
    id: root
    visible: true

    width: 640
    height: 480

    title: qsTr("Hello Triangles!")

    Item {
        width: 300;
        height: 200
        id: canvasItem
        x: 10

        Text {
            id: canvasItemTxt
            text: "CanvasTriangle"
        }
        CanvasTriangle {
            anchors.top: canvasItemTxt.bottom
            anchors.margins: 10
            width: parent.width * 2/3
            height: parent.height * 2/3
        }
    }

    Item {
        width: 300;
        height: 200
        id: paintedItem
        anchors.left: canvasItem.right

        Text {
            id: paintedItemTxt
            text: "PaintedItemTriangle"

        }
        PaintedItemTriangle	{
            anchors.top: paintedItemTxt.bottom
            anchors.margins: 10
            width: parent.width * 2/3
            height: parent.height * 2/3
        }
    }

    Item {
        width: 300;
        height: 200
        id: quickItem
        anchors.top: canvasItem.bottom
        anchors.left: canvasItem.left

        Text {
            id: quickItemTxt
            text: "QuickItemTriangle"
        }
        QuickItemTriangle	{
            anchors.top: quickItemTxt.bottom
            anchors.margins: 10
            width: parent.width * 2/3
            height: parent.height * 2/3
        }
    }



}
