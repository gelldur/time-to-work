import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 2.1

import QtQml 2.0

import com.AppController 1.0

import "component" as MyComponent

ApplicationWindow {
    id: mainWindow
    visible: true
    width: 640
    height: 480
    title: qsTr("TimeToWork")

    AppController {
        id: appController
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            console.log(qsTr('Clicked on background. Text: "' + comment.text + '"'))
        }
    }

    Timer {
        id: updateTimeLabel
        interval: 1000
        repeat: true
        triggeredOnStart: true
        onTriggered: {
            console.log("update")
            workingTimeLabel.text = qsTr(
                        "Working for: ") + appController.getTimeWorking()
        }
    }

    Column {
        anchors.fill: parent

        Button {
            id: buttonStartStop
            text: qsTr("Start")
            anchors.horizontalCenter: parent.horizontalCenter

            onClicked: {
                console.log(qsTr('Clicked'))

                if (appController.getTimeWorking() == "") {
                    updateTimeLabel.restart()
                    appController.onStartWorking()

                    text = qsTr("Stop")
                    setTitle(qsTr("Working..."))
                } else {
                    updateTimeLabel.stop()
                    appController.onStopWorking()

                    text = qsTr("Start")
                    setTitle(qsTr("TimeToWork"))
                    workingTimeLabel.text = ""
                }
            }
        }
        MyComponent.Space {
            height: 10
        }
        Text {
            id: workingTimeLabel

            anchors.horizontalCenter: parent.horizontalCenter
        }
        MyComponent.Space {
            height: 10
        }
        TextField {
            id: comment
            placeholderText: qsTr("Comment")
            maximumLength: 255

            verticalAlignment: Text.AlignVCenter
            anchors.horizontalCenter: parent.horizontalCenter
        }
        MyComponent.Space {
            height: 10
        }
        TextField {
            id: issue
            placeholderText: qsTr("Issue")

            verticalAlignment: Text.AlignVCenter
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
}
