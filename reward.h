#ifndef REWARD_H
#define REWARD_H

#include <QWidget>
#include "globalvariables.h"
#include <QIcon>
#include <QGraphicsScene>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include "custom_graphicsview.h"

namespace Ui {
class reward;
}

class reward : public QWidget
{
    Q_OBJECT

public:
    explicit reward(QWidget *parent = nullptr);
    ~reward() override;
    custom_graphicsView * get_wig_reward();
signals:
    void signal_firstPaint();
public slots:
    void slot_matchingID(int channelID);
    void slot_reset();
    void execute_animation1();
protected:
    void setup_backgroud();
    void setup_animation1();
    void setup_animation2();
    void paintEvent(QPaintEvent * event) override;
    void setup_graphicsView();
    void update_rewards(int row);


private:
    QPixmap pix_background;
    QSqlQueryModel * data_channels;
    QGraphicsOpacityEffect * effect_opacity;
    QPropertyAnimation *animation_opacity;
    QPropertyAnimation *animation_movement;

    QPropertyAnimation *animation_opacity2;
    QPropertyAnimation *animation_movement2;
    Ui::reward *ui;
    bool firstPaint;

    custom_graphicsView * wig_reward;

    static const QString msg_welcome;
    static const QString msg_noReward;
};

#endif // REWARD_H
