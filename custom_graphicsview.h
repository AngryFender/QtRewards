#ifndef CUSTOM_GRAPHICSVIEW_H
#define CUSTOM_GRAPHICSVIEW_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPainter>
#include <QPaintEvent>
#include <QDebug>

class custom_graphicsView: public QWidget
{
public:
    custom_graphicsView(QWidget *parent = nullptr);
    void set_pixmap(QPixmap _pix);

    void set_icon(QPixmap _ico);
    void set_text(QString _text);

    QPixmap get_pixmap();
    QString get_text();
protected:
    void paintEvent(QPaintEvent *event) override;
private:
    QPixmap pix;
    QPixmap ico;
    QString text;
};

#endif // CUSTOM_GRAPHICSVIEW_H
