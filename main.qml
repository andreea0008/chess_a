import QtQuick 2.6
import QtQuick.Window 2.2


Window {
    visible: true
    width: board.widthAndHeightBoard + rightSideBorder.width + 20
    height: board.widthAndHeightBoard + 20
    title: qsTr("Chess World")

    Item{
        anchors.fill: parent

        MainField{

        }

        Rectangle{
            id: rightSideBorder
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            color: "#1b1b1b"
            width: 300

            ListView{
                anchors.fill: parent
                model: logOfChessMove
                spacing: 1
                delegate: Rectangle{
                    width: parent.width
                    height: 30
                    Text {
                        id: name
                        text: moveChess
                        color: "black"
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: 20
                    }
                }
            }
        }
    }
}
