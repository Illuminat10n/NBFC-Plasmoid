import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import org.kde.plasma.components as PlasmaComponents
import org.kde.plasma.plasmoid
import org.kde.kirigami.platform as Platform
import OmenCtl as Omenctl

import org.kde.ksvg as KSvg

//pragma ComponentBehavior: Bound
PlasmoidItem {
    id: root

    fullRepresentation: Item {

        ListView {
            anchors.fill: parent
            id: fanList
            model: Plasmoid.fanModel

            Timer {
                id: refreshTimer
                running: root.expanded
                interval: 2800
                repeat: true
                onTriggered: {
                    parent.model.refresh()
                }
            }
            //After clicking and setting a value, don't refresh until one second later
            Timer {
                id: timeoutTimer
                interval: 1000
                repeat: false
                onTriggered: {
                    refreshTimer.running = true
                }
            }

            delegate: ColumnLayout {

                width: ListView.view.width

                PlasmaComponents.Label {
                    property string name
                    Layout.fillWidth: true
                    property string displayedTargetSpeed: if (control.value <= 35) {
                                                              return "Auto"
                                                          } else
                                                              return control.value
                    id: label
                    text: model.name + ": " + displayedTargetSpeed
                }

                PlasmaComponents.Slider {
                    Component.onCompleted: {
                        value = model.targetSpeed
                    }
                    Layout.fillWidth: true
                    id: control
                    implicitWidth: parent.width
                    from: 30
                    to: 100
                    value: targetSpeed
                    stepSize: 5

                    onPressedChanged: {
                        refreshTimer.running = false
                        model.targetSpeed = control.value
                        timeoutTimer.restart()
                    }

                    /* background: KSvg.FrameSvgItem {
                    imagePath: "widgets/slider"
                    prefix: "groove"

                    implicitWidth: parent.width
                    //implicitHeight: PlasmaConponents.Slider.impilicitHeight

                    width: control.horizontal ? Math.max(fixedMargins.left + fixedMargins.right, control.availableWidth) : implicitWidth
                    height: control.vertical ? Math.max(fixedMargins.top + fixedMargins.bottom, control.availableHeight) : implicitHeight

                    x: control.leftPadding + (control.horizontal ? 0 : Math.round((control.availableWidth - width) / 2))
                    y: control.topPadding + (control.vertical ? 0 : Math.round((control.availableHeight - height) / 2))

                    KSvg.FrameSvgItem {
                        imagePath: "widgets/slider"
                        prefix: "groove-highlight"

                        anchors.left: parent.left
                        anchors.verticalCenter: parent.verticalCenter
                        LayoutMirroring.enabled: control.mirrored

                        width: control.horizontal ? control.position * control.availableWidth : parent.width
                        height: control.vertical ? control.position * control.availableHeight : parent.height
                    }

                    // Optional: second highlight to represent actual speed
                    KSvg.FrameSvgItem {
                        imagePath: "widgets/slider"
                        prefix: "groove-highlight"
                        status: KSvg.FrameSvgItem.Selected
                        visible: model.currentSpeed > control.from

                        anchors.left: parent.left
                        anchors.verticalCenter: parent.verticalCenter
                        LayoutMirroring.enabled: control.mirrored

                        width: control.horizontal
                            ? ((model.currentSpeed - control.from) / (control.to - control.from)) * control.availableWidth
                            : parent.width

                        height: control.vertical
                            ? ((model.currentSpeed - control.from) / (control.to - control.from)) * control.availableHeight
                            : parent.height
                    }
                }   */
                }


                /*PlasmaComponents.ProgressBar{
                Layout.fillWidth: true
                value: model.currentSpeed * 0.01;
            } */
            }
        }
    }

    compactRepresentation: Item {
        id: compRoot

        MouseArea {
            id: mouseArea

            property bool wasExpanded: false

            anchors.fill: parent
            hoverEnabled: false
            onPressed: wasExpanded = root.expanded
            onClicked: {
                root.expanded = !wasExpanded
            }
        }

        Rectangle {
            id: rect
            anchors.centerIn: parent
            height: parent.height * 0.5
            width: height

            border.color: Platform.Theme.textColor
            border.width: 2

            radius: 1
            color: root.expanded ? Platform.Theme.highlightColor: "transparent"
            rotation: 45
        }
    }
}
