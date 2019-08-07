#include "custom_combobox.h"


custom_combobox::custom_combobox(QWidget *parent):QComboBox (parent)
{

}

void custom_combobox::paintEvent(QPaintEvent *event)
{
    (void)event;

    //extract the current item image
    QPixmap pix_raw = qvariant_cast<QPixmap>(this->currentData());
    QPixmap pix = pix_raw.scaledToWidth(this->rect().width()-10,Qt::SmoothTransformation);

    //draw the current item image
    QPainter paint(this);
    int a = rect().x()+2;
    int b = (rect().height()/2 - pix.height()/2) + rect().y();
    int w = pix.width()-4;
    int h = pix.height()-4;
    QRect currentRect(a,b,w,h);
    paint.drawPixmap(currentRect,pix);
}


