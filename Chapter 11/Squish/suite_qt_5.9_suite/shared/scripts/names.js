import { RegularExpression, Wildcard } from 'objectmaphelper.js';

export var mainWindowMainWindow = {"name": "MainWindow", "type": "MainWindow", "visible": 1};
export var mainWindowPushButtonQPushButton = {"name": "pushButton", "type": "QPushButton", "visible": 1, "window": mainWindowMainWindow};
export var mainWindowLineEditQLineEdit = {"name": "lineEdit", "type": "QLineEdit", "visible": 1, "window": mainWindowMainWindow};
export var helloWorldQQuickWindowQmlImpl = {"title": "Hello World", "type": "QQuickWindowQmlImpl", "unnamed": 1, "visible": true};
export var helloWorldHelloQMLText = {"container": helloWorldQQuickWindowQmlImpl, "text": "Hello QML!", "type": "Text", "unnamed": 1, "visible": true};
export var helloWorldClickMeButton = {"checkable": false, "container": helloWorldQQuickWindowQmlImpl, "text": "click me!", "type": "Button", "unnamed": 1, "visible": true};
export var helloWorldClickedText = {"container": helloWorldQQuickWindowQmlImpl, "text": "clicked...", "type": "Text", "unnamed": 1, "visible": true};
