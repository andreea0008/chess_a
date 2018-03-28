import QtQuick 2.0

Rectangle {
    id: fieldMain
    width: board.sizeChessField
    height: width

    property int indexField: 0
    property variant listMove: figureControllers.moveList

    color: board.getColorByIndex(indexField)

    Connections{
        target: figureControllers
        onMoveListChanged:{
            fieldMain.border.width = 0
            for(var i = 0; i < moveList.length; i++){
                if(indexField === moveList[i]){
                    fieldMain.border.color = board.colorBorderSelect()
                    fieldMain.border.width = 2
                }
            }
        }

        onBeatListChanged:{
            fieldMain.color = board.getColorByIndex(indexField)
            for(var i = 0; i < beatList.length; i++){
                if(indexField === beatList[i]){
                    fieldMain.color = board.colorBeat()
                }
            }
        }
        onCommandMoveToIndex: resetVisibleBoardAfterBeatOrMove();

        onCommandBeat: resetVisibleBoardAfterBeatOrMove();
    }

    function resetVisibleBoardAfterBeatOrMove(){
        fieldMain.border.width = 0
        fieldMain.color = board.getColorByIndex(indexField)
    }
}
