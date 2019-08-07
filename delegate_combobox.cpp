#include "delegate_combobox.h"

delegate_combobox::delegate_combobox()
{

}


void delegate_combobox::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    //in the dropdown list of the combobox, draw the image of the channels in large visible size
    QPixmap pix_raw = qvariant_cast<QPixmap>(index.data(Qt::UserRole));
    QPixmap pix = pix_raw.scaledToWidth(option.rect.width(),Qt::SmoothTransformation);

    painter->save();

    int a = option.rect.x()+2;
    int b = (option.rect.height()/2 - pix.height()/2) + option.rect.y();
    int w = pix.width()-4;
    int h = pix.height()-4;
    QRect rect(a,b,w,h);

    if((option.state & QStyle::State_Selected ))
    {
        painter->fillRect(option.rect,option.palette.mid());
        if(option.state & QStyle::State_Active)
        {
            painter->fillRect(option.rect,option.palette.highlight());
        }
    }
    else
        painter->fillRect(option.rect,option.palette.light());

    painter->drawPixmap(rect,pix);
    painter->restore();
}

QSize delegate_combobox::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QSize s = QStyledItemDelegate::sizeHint(option, index);
    s.setHeight(50);
    return s;
}
