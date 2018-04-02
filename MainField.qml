import QtQuick 2.0

Rectangle{
    anchors.left: parent.left
    anchors.top: parent.top
    anchors.bottom: parent.bottom
    width: board.widthAndHeightBoard + 20
    color: "#1b1b1b"

    Row{
        id: bottomRow
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: 20
        anchors.rightMargin: 20
        height: 20
        property variant aToH: ["A", "B", "C", "D", "E", "F", "G", "H"]
        Repeater{
            model: 8
            Rectangle{
                width: board.widthAndHeightBoard /8
                height: 20
                color: board.getColorByIndex(0)
                Text{
                    anchors.centerIn: parent
                    text:bottomRow.aToH[index]
                    font.bold: true
                    font.pointSize: 15
                }
                Rectangle{
                    anchors.top: parent.top
                    anchors.left: parent.left
                    anchors.right: parent.right
                    height: 1
                }
            }
        }
    }

    Rectangle{
        id: mainRect
        anchors.left: columnLeft.right
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: bottomRow.top
        color: "transparent"

        Grid{
            anchors.fill: parent
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
            rows: 8
            columns: 8
            anchors.fill: parent

            Repeater{
                model: 64

                FigureImageChess{
                    indexField: index
                }
            }
        }
    }

    Column{
        id: columnLeft
        anchors.top: parent.top
        anchors.left: parent.left
        property variant numbers: ["8", "7", "6", "5", "4", "3", "2", "1"]
        Repeater{
            model: 8
            Rectangle{
                width: 20
                height: board.widthAndHeightBoard /8
                color: board.getColorByIndex(0)
                Text{
                    anchors.centerIn: parent
                    text:columnLeft.numbers[index]
                    font.bold: true
                    font.pointSize: 15
                }
                Rectangle{
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    anchors.right: parent.right
                    width: 1
                }
            }
        }
    }
}

