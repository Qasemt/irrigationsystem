#ifndef IMAGEDELEGATE_H
#define IMAGEDELEGATE_H

#include <QItemDelegate>
#include <QSize>
#include <QPixmap>
#include <QPainter>
class ImageDelegate : public QItemDelegate
{
public:
    ImageDelegate();
public:
    ImageDelegate(QObject * parent = 0);
    void paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const;
    QSize sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const;

//    // Create Editor when we construct MyDelegate
//       QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;

//       // Then, we set the Editor
//       void setEditorData(QWidget *editor, const QModelIndex &index) const;

//       // Give the SpinBox the info on size and location
//           void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // IMAGEDELEGATE_H
