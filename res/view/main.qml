import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 2.1
import QtQuick.Dialogs 1.2

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

    MessageDialog {
        id: statusDialog
        modality: Qt.ApplicationModal
        title: "Logging time"
        text: "Logging time"
        standardButtons: StandardButton.Ok
        visible: false
    }

    Column {
        anchors.fill: parent
        MyComponent.Space {
            height: 50
        }
        Button {
            id: buttonStartStop
            text: qsTr("Start")
            anchors.horizontalCenter: parent.horizontalCenter

            function onStopWorking() {
                appController.onStopWorking({
                                                issue: issue.text,
                                                activity: activity.currentIndex,
                                                comment: comment.text
                                            })
                statusDialog.visible = true
            }

            onClicked: {
                console.log(qsTr('Clicked'))

                if (appController.getTimeWorking() == "") {
                    updateTimeLabel.restart()
                    appController.onStartWorking()

                    text = qsTr("Stop")
                    setTitle(qsTr("Working..."))
                } else {
                    updateTimeLabel.stop()
                    onStopWorking()

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
        MyComponent.Space {
            height: 10
        }
        ComboBox {
            id: activity
            anchors.horizontalCenter: parent.horizontalCenter
            displayText: "Loading..."

            onCurrentIndexChanged: {
                displayText = model[currentIndex]
            }

            model: ListModel {
                id: activityModel
            }

            Connections {
                target: appController
                onActivitiesDownloaded: {
                    console.log("Received in QML from C++: " + activitesLabels.length)
                    activityModel.clear()
                    activity.displayText = "Pick activity"
                    for (var element in activitesLabels) {
                        console.log("Append - " + activitesLabels[element])
                        activityModel.append({
                                                 text: activitesLabels[element]
                                             })
                    }
                }
            }
        }
    }
}
