#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //initiate database
    SkyData = new database;
    if(!SkyData)
        qDebug()<<"Database couldn't be initialised";

    ui->setupUi(this);

    //setup for unit testing
    wig_login = ui->widget_login;
    wig_reward= ui->widget_reward;

    //setup the window widget
    this->setWindowTitle("Rewards");
    this->setWindowIcon(QIcon(":/ICON_SKY"));

    connect(ui->widget_login, SIGNAL(signal_matchingIDs(int )), ui->widget_reward, SLOT(slot_matchingID(int)));
    connect(ui->widget_login, SIGNAL(signal_reset()), ui->widget_reward, SLOT(slot_reset()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete SkyData;
}

login *MainWindow::get_wig_login()
{
    return wig_login;
}

reward *MainWindow::get_wig_reward()
{
    return wig_reward;
}
