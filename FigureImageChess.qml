import QtQuick 2.0

Item {
    id: mainItem
    width: board.sizeChessField
    height: width

    property int indexField: 0
    property int selectedIndexField: 100
    property variant listMove: figureControllers.moveList
    Image {
        id: figure
        anchors.centerIn: parent
        width: parent.width * 0.75
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
//                    console.log(i)
                }
            }
        }

        onMoveListChanged:{
        }

        onCommandMoveToIndex: {
            if (moveFromIndex === indexField)
                figure.visible = false
            if (moveToIndex === indexField)
                figure.source = figureControllers.getPathToIconByIndex(moveFromIndex)
        }

        onCommandBeat: {
            if(beatTo == indexField)
                figure.visible = false
            if(beatFrom == indexField)
                figure.visible = false
            if(beatTo == indexField)
                figure.source = figureControllers.getPathToIconByIndex(beatTo)
        }
    }
}