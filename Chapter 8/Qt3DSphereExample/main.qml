import QtQuick 2.2
import Qt3D.Core 2.0
import Qt3D.Render 2.0
import Qt3D.Input 2.0
import Qt3D.Extras 2.0


Entity {
    id: sceneRoot

    Camera {
        id: camera
        projectionType: CameraLens.PerspectiveProjection
        fieldOfView: 45
        aspectRatio: 16/9
        nearPlane : 0.1
        farPlane : 1000.0
        position: Qt.vector3d( 0.0, 0.0, -40.0 )
        upVector: Qt.vector3d( 0.0, 1.0, 0.0 )
        viewCenter: Qt.vector3d( 0.0, 0.0, 0.0 )
    }

    components: [
        RenderSettings {
            activeFrameGraph: ForwardRenderer {
                clearColor: Qt.rgba(1, 1, 1, 1)
                camera: camera
            }
        }
    ]
    PhongMaterial {
        id: material
    }

    SphereMesh {
        id: mesh
        radius: 10
        slices: 50
        rings: 50

    }

    Transform {
        id: transform
        property real userAngle: 0.0
        matrix: {
            var m = Qt.matrix4x4();
            m.rotate(userAngle, Qt.vector3d(0, 1, 0));
            m.translate(Qt.vector3d(10, 0, 0));
            return m;
        }
    }
    NumberAnimation {
        target: transform
        property: "userAngle"
        duration: 10000
        from: 0
        to: 360
        loops: Animation.Infinite
        running: true
    }
    Entity {
        id: sphere
        components: [ mesh, material, transform ]
    }
}
