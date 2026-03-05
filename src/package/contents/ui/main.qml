import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import org.kde.plasma.components as PlasmaComponents
import org.kde.plasma.plasmoid
import org.kde.plasma.core as PlasmaCore
import OmenCtl as Omenctl

import org.kde.ksvg as KSvg
import org.kde.kirigami as Kirigami

//pragma ComponentBehavior: Bound

PlasmoidItem{
    id: root
    property int speed: 0;
    onSpeedChanged: {
        compRoot.rect.spinAnimation.stop();
        if (speed > 0)
            spinAnimation.start();
    }

    fullRepresentation: Item{

    ListView {
        anchors.fill: parent
        z: 100
        id: fanList
        model: Plasmoid.fanModel

        Timer{
            id: refreshTimer
            running: expanded
            interval: 2000
            repeat: true
            onTriggered: {
                parent.model.refresh();
            }
        }

        Timer{
            id: timeoutTimer
            interval: 1000
            repeat: false
            onTriggered: {
                refreshTimer.running = true
            }
        }


        delegate: ColumnLayout{
            //anchors.left: fanList.left
            //anchors.right: fanList.right

            implicitHeight: fanList.height
            implicitWidth: fanList.width

            PlasmaComponents.Label
            {
                property string name
                Layout.fillWidth: true
                property string displayedTargetSpeed: if (control.value <= 35) {return "Auto"} else return control.value;
                id: label
                text: model.name + ": "+ displayedTargetSpeed
            }

            PlasmaComponents.Slider {
                Component.onCompleted : {
                    value = model.targetSpeed
                }
                Layout.fillWidth: true
                id: control;
                implicitWidth: parent.width
                from: 30
                to: 100;
                value: targetSpeed
                stepSize: 5;

                onPressedChanged: {
                    refreshTimer.running = false
                    model.targetSpeed = control.value;
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

    compactRepresentation: Item
    {
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

        Rectangle{
            id: rect
            anchors.centerIn: parent
            height: parent.height*0.5
            width: height

            border.color: PlasmaCore.Theme.textColor
            border.width: 2

            radius: 1
            color: root.expanded ? PlasmaCore.Theme.highlightColor : "transparent"
            rotation: 45

            NumberAnimation on rotation {
                id: spinAnimation
                from: 0
                to: 360
                duration: root.speed > 0 ? 100000 / root.speed : 0 // inverse of speed
                loops: Animation.Infinite
                running: root.speed > 40
                alwaysRunToEnd: true
            }
        }

    }
}
