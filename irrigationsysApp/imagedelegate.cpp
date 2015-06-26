#include "imagedelegate.h"
#include "QItemDelegate"
#include "QStyledItemDelegate"
#include <qlabel.h>
#include <QDebug>
#include <qgroupbox.h>
ImageDelegate::ImageDelegate(QObject * parent)
    : QItemDelegate(parent)
{

}

void ImageDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const
{

    QItemDelegate::paint(painter, option, index);

    if(index.column()==6)
    {
        int row = index.row();
        QModelIndex q = index.model()->index(row, 2);
        int data= index.model()->data(q,Qt::DisplayRole).toBool();
        QPixmap pm;
        if(data)
        {
            qDebug()<<"Icon On";
            pm=QPixmap(":/Icons/images/administrator.png");
        }else{
            pm=QPixmap(":/Icons/images/user.png");
              qDebug()<<"Icon Off";
        }
        //painter->drawPixmap(option.rect, pm);
        int x = option.rect.x()+7;
        int y = option.rect.y();

        pm.scaled(32, 32,Qt::KeepAspectRatio);
        painter->drawPixmap(x,y,32,32, pm);

    }



}

QSize ImageDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QSize(32,32);
}

//QWidget *ImageDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
//{
//    QLabel *editor = new QLabel(parent);
//    //    editor->setMinimum(0);
//    //    editor->setMaximum(100);
//    return editor;
//}

//void ImageDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
//{
//    if(index.column()==6)
//    {
//        // Get the value via index of the Model
//        int value = index.model()->data(index, Qt::EditRole).toInt();

//        // Put the value into the SpinBox
//        QLabel *lbl = static_cast<QLabel*>(editor);
//        QPixmap pix(":/Icons/images/connect.png");
//        lbl->setPixmap(pix);
//    }
//}

//void ImageDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
//{
//     editor->setGeometry(option.rect);
//}
