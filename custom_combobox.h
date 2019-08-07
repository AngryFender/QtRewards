#ifndef CUSTOM_COMBOBOX_H
#define CUSTOM_COMBOBOX_H

#include <QWidget>
#include <QComboBox>
#include <QPainter>

class custom_combobox : public QComboBox
{
public:
    custom_combobox(QWidget * parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // CUSTOM_COMBOBOX_H
