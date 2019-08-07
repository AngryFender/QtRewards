#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "globalvariables.h"
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include "login.h"
#include "reward.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    login * get_wig_login();
    reward * get_wig_reward();

private:
    Ui::MainWindow *ui;
    login * wig_login;
    reward * wig_reward;
};

#endif // MAINWINDOW_H
