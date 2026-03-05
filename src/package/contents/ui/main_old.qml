import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import org.kde.plasma.components as PlasmaComponents
import org.kde.plasma.plasmoid
import org.kde.plasma.core as PlasmaCore
import OmenCtl as Omenctl

pragma ComponentBehavior: Bound

PlasmoidItem{
    id: root
    property int speed: 0;
    onSpeedChanged: {
        compRoot.rect.spinAnimation.stop();
        if (speed > 0)
            spinAnimation.start();
    }

    fullRepresentation: Item{


    Omenctl.FanModel{
        id:modelka
    }

    ListView {
        anchors.fill: parent
        z: 100
        id: fanList
        model: modelka

        delegate: ColumnLayout{
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top

            PlasmaComponents.Label
            {
                property string name
                Layout.fillWidth: true
                //property string display: if (slider1.value <= 30) {return "Auto"} else return slider.value;
                id: label
                text: model.name
            }

            PlasmaComponents.Slider {
                property double targetSpeed: model.targetSpeed
                Layout.fillWidth: true
                id: slider;
                implicitWidth: parent.width
                from: 30
                to: 100;
                value: targetSpeed
                stepSize: 5;
                onPressedChanged: {
                    model.targetSpeed = slider.value;
                }
            }
        }
    }

    ColumnLayout{

        id: coolers
        anchors.top: fanList.bottom
        anchors.left: parent.left
        anchors.right: parent.right

        PlasmaComponents.Label
        {
            property string display: if (slider1.value <= 30) {return "Auto"} else return slider1.value;
            id: label1
            text: "CPU Cooler: " + display;
        }

        PlasmaComponents.Slider
        {
            id: slider1;
            implicitWidth: parent.width
            from: 30
            to: 100;
            stepSize: 5;
            onPressedChanged: {
                Plasmoid.cpuCool = slider1.value;
                root.speed = slider1.value;
            }
        }

        PlasmaComponents.Label
        {
            property string display: if (slider2.value <= 30) {return "Auto"} else return slider2.value;
            id: label2
            text: "GPU Cooler: " + display;
        }

        PlasmaComponents.Slider
        {
            id: slider2
            from: 30
            to: 100;
            stepSize: 5;
            implicitWidth: parent.width;
            onPressedChanged: {
                Plasmoid.gpuCool = slider2.value;
            }
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
