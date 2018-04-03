import QtQuick 2.6
import QtQuick.Window 2.2


Window {
    visible: true
    width: board.widthAndHeightBoard + 300 + 20
    height: board.widthAndHeightBoard + 20
    title: qsTr("Chess World")

    Item{
        anchors.fill: parent

        MainField{
            id: mainField
        }


        Rectangle{
            id: rightSideBorder
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.left: mainField.right
            color: "#1b1b1b"
            QueueOfMove{
                id: queue
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right
            }

            ListView{
                anchors.fill: parent
                anchors.topMargin: queue.height
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
