import * as names from 'names.js';

function main() {
    startApplication("ClickTestWidget");
    clickButton(waitForObject(names.mainWindowPushButtonQPushButton));
    test.compare(waitForObjectExists(names.mainWindowLineEditQLineEdit).text, "Clicked!");
    clickButton(waitForObject(names.mainWindowPushButtonQPushButton));
    test.compare(waitForObjectExists(names.mainWindowLineEditQLineEdit).text, "Un-clicked!");
    mouseDrag(waitForObject(names.mainWindowLineEditQLineEdit), 95, 44, -103, 1, 1, Qt.LeftButton);
    type(waitForObject(names.mainWindowLineEditQLineEdit), "sdsdsddssd");
    clickButton(waitForObject(names.mainWindowPushButtonQPushButton));
    test.compare(waitForObjectExists(names.mainWindowLineEditQLineEdit).text, "Clicked!");
    clickButton(waitForObject(names.mainWindowPushButtonQPushButton));
    doubleClick(waitForObject(names.mainWindowPushButtonQPushButton), 86, 41, Qt.NoModifier, Qt.LeftButton);
    clickButton(waitForObject(names.mainWindowPushButtonQPushButton));
}
