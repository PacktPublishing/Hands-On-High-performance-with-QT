import QtQuick 2.9
import QtQuick.Window 2.2

import	CustomShapes 1.0


Window {
    id: root
    visible: true

    width: 640
    height: 480

    title: qsTr("Hello Triangles!")

    // a "checkers" background
    ShaderEffect {
        id: background
        anchors.fill: parent

        property real squareSize: 20
        property color color1: Qt.rgba(0.7, 0.8, 0.9, 1);
        property color color2: Qt.rgba(0.65, 0.75, 0.85, 1);
        property size pixelSize: Qt.size(width / squareSize, height / squareSize);

        fragmentShader:
            "
            uniform lowp vec4 color1;
            uniform lowp vec4 color2;
            uniform highp vec2 pixelSize;
            varying highp vec2 qt_TexCoord0;
            void main() {
                highp vec2 tc = sign(sin(3.14152 * qt_TexCoord0 * pixelSize));
                if (tc.x != tc.y)
                    gl_FragColor = color1;
                else
                    gl_FragColor = color2;
            }
            "
    }

    Item {
        width: 300;
        height: 200
        id: canvasItem
        x: 50
        y: 40

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
        y: canvasItem.y
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

    Item {
        width: 300;
        height: 200
        id: fboItem
        anchors.top: paintedItem.bottom
        anchors.left: paintedItem.left

        Text {
            id: fboItemText
            text: "FrameBufferTriangle"
        }
        FrameBufferTriangle	{
            anchors.top: fboItemText.bottom
            anchors.margins: 10
            width: parent.width * 2/3
            height: parent.height * 2/3
        }
    }

}
