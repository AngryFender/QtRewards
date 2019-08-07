#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QPixmap>
#include <QGraphicsScene>
#include <QStyleOption>
#include <QPainter>
#include "globalvariables.h"
#include "delegate_combobox.h"
#include <QString>
#include <QPointF>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>

namespace Ui {
class login;
}

class login : public QWidget
{
    Q_OBJECT


public:

    explicit login(QWidget *parent = nullptr);

    ~login() override;

        Ui::login *ui;



signals:
    void signal_matchingIDs(int channelID);
    void signal_reset();
    void signal_firstPaint();

protected:
    void setup_animation();
    void paintEvent(QPaintEvent * event) override;
    void setup_graphicsView();
    bool setup_database();
    void setup_combobox();
    void setup_login();
    void setup_loggedIn(int accountNum);

    void setup_invalidAccount();
    void show_invalidMessage(QString msg);
private slots:
    void on_btn_login_pressed();
    void on_btn_loggout_released();
    void execute_animation();

private:
    QGraphicsScene* scene_welcome;
    QGraphicsOpacityEffect * effect_opacity;
    QPropertyAnimation *animation_opacity;
    QPropertyAnimation *animation_movement;
    delegate_combobox *delegate;
    QSqlQueryModel * data_channels;
    QSqlQueryModel * data_accounts;

    bool firstPaint;

    QPushButton * btn_login;
    QPushButton *btn_logout;
    QGraphicsView *graph_welcome;
    QLabel * lbl_acc;
    QLabel * lbl_channel;
    QLineEdit * lEdit_acc;
    QComboBox * cmb_chn;
    QLabel * lbl_message;

    static const QString lbl_aca_text;
    static const QString lbl_chn_text;
    static const QString lbl_msg_correctAcc;
    static const QString lbl_msg_incorrectAcc;
    static const QString lbl_msg_databaseMissing;

public:
    QPushButton * get_btn_login();
    QPushButton *get_btn_logout();
    QGraphicsView *get_graph_welcome();
    QLabel * get_lbl_acc();
    QLabel *get_lbl_channel();
    QLineEdit *get_ledit_acc();
    QComboBox *get_cmb_chn();
    QLabel * get_lbl_message();
};

class testLogin
{
public:
    friend class Ui::login;
    Ui::login logInView();
};


#endif // LOGIN_H
