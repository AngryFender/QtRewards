#include "custom_graphicsview.h"

custom_graphicsView::custom_graphicsView(QWidget *parent):QWidget (parent)
{

}

void custom_graphicsView::set_pixmap(QPixmap _pix)
{
    pix = _pix.scaledToWidth(rect().width(),Qt::SmoothTransformation);
    this->update();
}

QPixmap custom_graphicsView::get_pixmap()
{
    return pix;
}

QString custom_graphicsView::get_text()
{
    return text;
}

void custom_graphicsView::set_icon(QPixmap _ico)
{
    if(!ico.isNull())ico= _ico.scaledToWidth(100,Qt::SmoothTransformation);
    this->update();
}

void custom_graphicsView::set_text(QString _text)
{
    text = _text;
}

void custom_graphicsView::paintEvent(QPaintEvent *event)
{
    (void)event;
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    //create a rectanglur background with rounded corners using path
    QPainterPath path;
    QRectF box(rect().x()+1,rect().y()+1,rect().width()-2,rect().height()-2);
    path.addRoundedRect(box, 10, 10);
    painter.setClipPath(path);
    painter.drawPath(path);
    painter.fillPath(path,Qt::white);

    //draw the reware image in the upper half
    painter.drawPixmap(box,pix,box);

    //draw the reward text in the middle of lower half
    int x_text = rect().width()/2 - text.count()*2-10;
    QPoint pos_text(x_text,rect().height()/4*3);
    painter.drawText(pos_text,text);
    QRectF icon(x_text-30,rect().height()/4*3-15,100,100);
    painter.drawPixmap(icon,ico,box);
}
