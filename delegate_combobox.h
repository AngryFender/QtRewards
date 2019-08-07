#ifndef DELEGATE_COMBOBOX_H
#define DELEGATE_COMBOBOX_H

#include <QStyledItemDelegate>
#include <QPainter>
#include <QComboBox>


class delegate_combobox : public QStyledItemDelegate
{
public:
    delegate_combobox();
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // DELEGATE_COMBOBOX_H
