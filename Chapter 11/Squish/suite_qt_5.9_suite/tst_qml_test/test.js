import * as names from 'names.js';

function main()
{
    startApplication("SimplestQMLProject");
    test.compare(waitForObjectExists(names.helloWorldHelloQMLText).text, "Hello QML!");
    mouseClick(waitForObject(names.helloWorldClickMeButton), 70, 23, Qt.LeftButton);
    test.compare(waitForObjectExists(names.helloWorldClickedText).text, "clicked...");
}
