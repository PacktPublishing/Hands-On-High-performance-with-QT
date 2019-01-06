import QtQuick 2.4
import FrequencyMonitor 1.0


Rectangle {
    id:root
    width: 120
    height: 60
    border.width: 2
    radius: 10
    anchors.margins: 10

    property color textColor
    property int textSize
    property string label

    border.color: textColor

    function framePainted() {
        monitor.notify()
    }

    color: "transparent"
    z: 999

    FrequencyMonitor {
        id: monitor
        onCurrentFrequencyChanged: {
            currentFreqText.text = monitor.currentFrequency.toFixed(2)
        }
    }

    Text {
        id: labelText
        anchors {
            left: parent.left
            top: parent.top
            margins: 10
        }
        color: root.textColor
        font.pixelSize: 0.6 * root.textSize
        text: root.label
        width: root.width - 2*anchors.margins
        elide: Text.ElideRight
    }

    Text {
        id: currentFreqText
        anchors {
            right: parent.right
            bottom: parent.bottom
            margins: 10
        }
        text: "0"
        color: root.textColor
        font.pixelSize: root.textSize
    }
}
