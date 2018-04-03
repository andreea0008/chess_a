import QtQuick 2.0

Rectangle {
    width: parent.width
    height: 50
    color: "#efeeee"

    property int widthRectangle: height * 2
    property int heightRectangle: height * 0.8
    property int radiusRectangle: height * 0.2
    property int widthBorder: 2
    property color active: "red"

    //white
    Rectangle{
        anchors.right: parent.horizontalCenter
        anchors.rightMargin: parent.height * 0.2
        anchors.verticalCenter: parent.verticalCenter
        width: widthRectangle
        height: heightRectangle
        color: "white"
        border.color: active
        border.width: figureControllers.isNextStepWhite ? widthBorder : 0
        radius: radiusRectangle
        antialiasing: true
        Text {
            anchors.centerIn: parent
            text: qsTr("White")
        }
    }

    //black
    Rectangle{
        anchors.left: parent.horizontalCenter
        anchors.leftMargin: parent.height * 0.2
        anchors.verticalCenter: parent.verticalCenter
        width: widthRectangle
        height: heightRectangle
        color: "#212121"
        border.color: active
        border.width: figureControllers.isNextStepWhite ? 0 : widthBorder
        radius: radiusRectangle
        antialiasing: true
        Text {
            anchors.centerIn: parent
            color: "#efeeee"
            text: qsTr("Black")
        }
    }
}
