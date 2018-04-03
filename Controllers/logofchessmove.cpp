#include "logofchessmove.h"
#include <QDebug>

LogOfChessMove::LogOfChessMove(QObject *object)
    : QAbstractItemModel(object)
{
    roles();
}

LogOfChessMove::~LogOfChessMove()
{

}

void LogOfChessMove::roles()
{
    m_roles[Id]   = "idMoveChess";
    m_roles[Move] = "moveChess";
}

int LogOfChessMove::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : m_moves.size();
}

int LogOfChessMove::columnCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : 1;
}

QModelIndex LogOfChessMove::parent(const QModelIndex &child) const
{
    Q_UNUSED(child);
    return QModelIndex();
}

QVariant LogOfChessMove::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || index.column() != 0 || index.row() < 0 || index.row() >= m_moves.size())
        return QVariant();
    MoveChess *moveChess = m_moves[index.row()];
    switch (role) {
    case Id: return moveChess->getId();
    case Move: return moveChess->getDescriptionMove();
    default: return QVariant();
    }
}

QModelIndex LogOfChessMove::index(int row, int column, const QModelIndex &parent) const
{
    return hasIndex(row, column, parent) ? createIndex(row, column) : QModelIndex();
}

QHash<int, QByteArray> LogOfChessMove::roleNames() const
{
    return m_roles;
}

void LogOfChessMove::addMove(int indexFrom, int indexTo)
{
    beginInsertRows(QModelIndex(), m_moves.size(), m_moves.size());
    m_moves.push_back(new MoveChess(m_moves.size() +1, createDescription(indexFrom, indexTo)));
    endInsertRows();
}

QString LogOfChessMove::createDescription(int indexFrom, int indexTo)
{
    return getPositionByIndex(indexFrom) + " -> "+ getPositionByIndex(indexTo);
}

QString LogOfChessMove::getPositionByIndex(int index)
{
    QString array[8]{ "A", "B", "C", "D", "E", "F", "G", "H" };
    QString column = array[index % SIZE];
    QString row = QString::number(((COUNT_OF_CHESS_FIELD - index) / SIZE) +1);
    return column+row;
}
