import QtQuick 2.9
import QtQuick.Window 2.2


//import QtQuick 2.5
import QtQuick.Particles 2.0


Window {
    id: root
    visible: true
    width: 740
    height: 480
    title: qsTr("Hello World")
    color: "#1F1F1F"


    FrequencyItem {
        id : frequencyDisplay
        objectName: "fpsRateDisplay"
        visible: true
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        textColor: "green"
        textSize: 24
        label: "FPS rate"
    }

    ParticleSystem {
        id: particleSystem
        anchors.top: frequencyDisplay.bottom
        z: 1
    }

    ImageParticle {
        source: "/star.png"
        system: particleSystem
        rotation: 0
        rotationVariation: 45
        rotationVelocity: 15
        rotationVelocityVariation: 15
        entryEffect: ImageParticle.Scale
    }

    Emitter {
        id: emitter
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        width: 1;
        height: 1
        system: particleSystem
        emitRate: 10
        lifeSpan: 6400
        lifeSpanVariation: 400
        size: 24
        velocity: PointDirection {
            x: 100
            y: 0
            xVariation: 0
            yVariation: 100/5
        }
    }

}
