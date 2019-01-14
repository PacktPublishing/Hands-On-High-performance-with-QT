import QtQuick 2.0
import QtTest 1.0

TestCase {
    name: "QmlClickTest"
    id: testCase
    when: windowShown
    visible: true


    ClickForm {
        id: clickForm
        visible: true
    }

    function initTestCase() {
    }

    function cleanupTestCase() {
    }

    function test_click() {
        var button = findChild(clickForm, "button")
        var textItem = findChild(clickForm, "textItem")

        mouseClick(button)
        compare(textItem.text, "clicked!")
    }

    function test_keyboard() {
        var textItem = findChild(clickForm, "textItem")
        var currText = textItem.text

        mouseClick(textItem, Qt.LeftButton, Qt.NoModifier) // focus

        keyPress("X")
        keyPress("X")
        keyPress("X")
        compare(textItem.text, "XXX" + currText)
    }
}
