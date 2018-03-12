import QtQuick 2.6
import QtQuick.Window 2.2


Window {
    visible: true
    width: board.widthAndHeightBoard
    height: width
    title: qsTr("Hello World")

    Rectangle{
        anchors.fill: parent
        color: "transparent"

        Grid{
            anchors.centerIn: parent
            width: board.widthAndHeightBoard
            height: width
            rows: 8
            columns: 8

            Repeater{
                model: 64

                FieldChess{
                    indexField: index
                }
            }

        }
        Grid{
            anchors.fill: parent
            rows: 8
            columns: 8
            anchors.centerIn: parent
            width: board.widthAndHeightBoard
            height: width

            Repeater{
                model: 64

                FigureImageChess{
                    indexField: index
                }
            }
        }
    }
}
