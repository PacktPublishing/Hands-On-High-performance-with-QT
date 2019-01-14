import QtQuick 2.9
import QtQuick.Controls 2.2

Item {    
    id: root
    visible: true
    width: 640
    height: 480

    TextInput {
     id: textItem
     objectName: "textItem" // test suport
     text: "Hello QML!"
   }

   Button {
        id: button
        objectName: "button" // test suport
        text: "click me!"
        anchors.top: textItem.bottom
        onClicked:  textItem.text = "clicked!"
   }

}
