#include "titlemodel.h"

TitleModel::TitleModel(QObject *parent) :
        QAbstractItemModel(parent)
{
}
int TitleModel::rowCount(const QModelIndex &/*parent*/) const
{
    return titleList.count();
}
int TitleModel::columnCount(const QModelIndex &/*parent*/) const
{
    return 1;
}
QVariant TitleModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();
    QVariantMap info(titleList.at(index.row()).toMap());
    switch(role)
    {
    case Qt::DisplayRole:
        return info.value("title");
    case Qt::ToolTipRole:
        return QVariant(QString(tr("author:%1\ncategory:%2\ndate:%3")).arg(
                info.value("author").toString(),info.value("category-name").toString(),
                info.value("date").toString()));
    case Qt::UserRole:
        return info.value("category-id");
    }
    return QVariant();
}
bool TitleModel::removeRow(int row, const QModelIndex &parent)
{
    if(titleList.at(row).isValid())
    {
        beginRemoveRows(parent,row,row);
        emit RowRemoved(titleList.at(row).toMap().value("id").toInt());
        endRemoveRows();
        return true;
    }
    return false;
}
QModelIndex TitleModel::parent(const QModelIndex &/*child*/) const
{
    return QModelIndex();
}
QModelIndex TitleModel::index(int row, int column, const QModelIndex &parent) const
{
    if(!hasIndex(row,column,parent))
        return QModelIndex();
    return createIndex(row,column);
}
void TitleModel::InitData(const QVariant &list)
{
    beginResetModel();
    titleList=list;
    endResetModel();
}
