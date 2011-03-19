#include "titleitem.h"
#include <QtGui>
TitleItem::TitleItem(QObject *parent) :
        QStyledItemDelegate(parent)
{
    frame=new QFrame(this);
    frame->setLineWidth(1);
    frame->setFrameStyle(QFrame::StyledPanel | QFrame::Plain);

    title=new QLabel(frame);
    title->setAttribute(Qt::WA_TranslucentBackground,true);
    title->setAutoFillBackground(false);

    del=new QPushButton(tr("X"),frame);
    del->setToolTip(tr("delete"));
    del->setMinimumSize(10,10);
    del->setMaximumSize(10,10);
    connect(del,SIGNAL(clicked()),this,SLOT(DeleteTitle()));

    QHBoxLayout layout(frame);
    layout.addWidget(title,0,Qt::AlignLeft);
    layout.addWidget(del,0,Qt::AlignRight);
}
void TitleItem::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.column() == 0)
    {
        if(option.state & QStyle::State_Selected)
        {
            QPalette pal;
            pal.setColor(QPalette::Background,Qt::Blue);
            frame->setPalette(pal);
        }
        if(option & QStyle::State_MouseOver)
        {
            QPalette pal;
            pal.setColor(QPalette::Background,Qt::Blue);
            frame->setPalette(pal);
        }
    }
    else
        QStyledItemDelegate::paint(painter, option, index);

}
void TitleItem::DeleteTitle()
{

}
void TitleItem::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    if(editor==NULL)
        model->removeRow(index.row());
}
