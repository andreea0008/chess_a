import QtQuick 2.0

Item {
    id: mainItem
    width: board.sizeChessField
    height: width

    property int indexField: 0
    property int selectedIndexField: 100
    property variant listMove: figureControllers.moveList
    property real percentFromWidthAndHeight: 0.75
    Image {
        id: figure
        anchors.centerIn: parent
        width: parent.width * percentFromWidthAndHeight
        height: width
        source: figureControllers.getPathToIconByIndex(index)
    }

    MouseArea{
        anchors.fill: parent
        onClicked: {
            figureControllers.getFigureByIndex(index)
            selectedIndexField = index
        }
    }

    Connections{
        target: figureControllers
        onPossibleChessMove:{
            if(index == selectedIndexField){
                for(var i = 0; i < listMove.length; i++){
                }
            }
        }

        onCommandMoveToIndex: {
            if (moveFromIndex === indexField){
                figure.source = ""
            }
            if (moveToIndex === indexField){
                figure.source = figureControllers.getPathToIconByIndex(moveFromIndex)
                logOfChessMove.addMove(moveFromIndex, moveToIndex)
            }
        }

        onCommandBeat: {
            if(beatTo == indexField){
                figure.visible = true
                figure.source = figureControllers.getPathToIconByIndex(beatTo)
            }
            if(beatFrom == indexField){
                figure.visible = false
                figure.source = ""
            }
        }
    }
}
