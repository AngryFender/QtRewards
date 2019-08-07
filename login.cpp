#include "login.h"
#include "ui_login.h"


const QString login::lbl_msg_correctAcc = "Welcome user ";
const QString login::lbl_msg_incorrectAcc = "Invalid Account Number";
const QString login::lbl_msg_databaseMissing = "Database Offline";


login::login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login)
{
    //setup all views and animations
    testLogin();
    setup_animation();
    ui->setupUi(this);
    setup_login();
    setup_graphicsView();
    if(setup_database())
        setup_combobox();
}

login::~login()
{
    delete scene_welcome;
    delete effect_opacity;
    delete ui;
}

void login::setup_animation()
{
    //at the first paint event of the widget, emit signal to start animation, this way the widget will end up in their correct co ordinates
    firstPaint = false;
    connect(this,SIGNAL(signal_firstPaint()),this,SLOT(execute_animation()));
}

void login::paintEvent(QPaintEvent *event)
{
    (void)event;

    QPainter * painter = new QPainter(this);

    //Make the frame of the parent widget a rectagle with rounded corner, fill this rectage with a gradient color
    QPointF fPoint(rect().x()+rect().width()/3  ,rect().y()+rect().height()/3);
    QPointF ePoint(rect().x()+rect().width()/3*2,rect().y()+rect().height()/3*2);

    QLinearGradient lGradient(fPoint,ePoint);
    lGradient.setColorAt(0, Qt::white);
    lGradient.setColorAt(1, Qt::transparent);

    QPainterPath path;
    path.addRoundedRect(rect(), 10, 10);
    painter->setClipPath(path);

    //use transparent pen to make this boarderless
    QPen pen(Qt::transparent, 0);
    painter->setPen(pen);
    painter->drawPath(path);
    painter->fillPath(path,lGradient);

    delete painter;

    //at the first paint event of the widget, emit signal to start animation
    if(!firstPaint)
    {
        firstPaint = true;
        emit signal_firstPaint();
    }

}

void login::setup_graphicsView()
{
    //extract Welcome/"SKY" Image and scale it to HD
    QPixmap pix_sky_raw(":/IMAGE_SKY");
    QPixmap pix_sky = pix_sky_raw.scaledToWidth(2000,Qt::SmoothTransformation);

    //Show the image transparent background and without any border
    scene_welcome = new QGraphicsScene;
    scene_welcome->addPixmap(pix_sky);
    ui->graphicsView_welcome->setScene(scene_welcome);
    ui->graphicsView_welcome->fitInView(0,0,200,200 ,Qt::KeepAspectRatio);
    ui->graphicsView_welcome->setFrameStyle(0);
    ui->graphicsView_welcome->setStyleSheet("background: transparent");
}

bool login::setup_database()
{
    //extract tables from the database
    data_accounts = global_get_database()->getSqlAccounts();
    data_channels = global_get_database()->getSqlChannelsRewards();

    //check if the tables are valid
    if(data_accounts->rowCount()>0 &&data_channels->rowCount()>0)
    {
        return true;
    }
    else
    {
        show_invalidMessage(lbl_msg_databaseMissing);
        return false;
    }
}

void login::setup_combobox()
{    

    //setup combobox
    delegate = new delegate_combobox;
    ui->cmb_channel->setItemDelegate(delegate);

    //populate combobox with images from the database, this is stored in the UserRole
    for (int i = 0 ; i < data_channels->rowCount(); i++)
    {
        QByteArray byte = data_channels->record(i).value(2).toByteArray();
        QPixmap pix;
        pix.loadFromData(byte);
        QIcon icon(pix);
        ui->cmb_channel->addItem(icon,"",pix);
    }
}

void login::setup_login()
{
    //hide unwanted views for now
    ui->btn_loggout->hide();
    ui->lbl_welcome->hide();

    //pointers for unit testing
    btn_login   = ui->btn_login;
    btn_logout  = ui->btn_loggout;
    graph_welcome= ui->graphicsView_welcome;
    lbl_acc     = ui->lbl_acc;
    lbl_channel = ui->lbl_channel;
    lEdit_acc   = ui->lineEdit_acc;
    cmb_chn     = ui->cmb_channel;
    lbl_message = ui->lbl_welcome;

}

void login::setup_loggedIn(int accountNum)
{
    //hide login input views and show welcome messsage to the valid accounts
    ui->lbl_acc->hide();
    ui->lbl_channel->hide();
    ui->lineEdit_acc->hide();
    ui->cmb_channel->hide();
    ui->btn_login->hide();

    QString str_welcome = lbl_msg_correctAcc + QString::number(accountNum);
    ui->lbl_welcome->setText(str_welcome);
    ui->lbl_welcome->setStyleSheet("QLabel {background-color: transparent; color: blue;}");
    ui->lbl_welcome->show();
    ui->btn_loggout->show();
}

void login::execute_animation()
{
    effect_opacity    = new QGraphicsOpacityEffect(this);
    animation_opacity = new QPropertyAnimation(effect_opacity,"opacity");

    //setup and start opacity animation to the whole parent widget
    effect_opacity->setOpacity(0);
    this->setGraphicsEffect(effect_opacity);
    animation_opacity->setDuration(400);
    animation_opacity->setStartValue(0);
    animation_opacity->setEndValue(1);
    animation_opacity->setEasingCurve(QEasingCurve::InBack);
    animation_opacity->start(QPropertyAnimation::DeleteWhenStopped);


    //setup and start geometry animation only to the graphicsView showing "SKY" image
    animation_movement = new QPropertyAnimation(ui->graphicsView_welcome, "geometry");
    animation_movement->setDuration(400);
    QPoint pos(ui->graphicsView_welcome->x(),ui->graphicsView_welcome->y());
    int w = ui->graphicsView_welcome->minimumWidth();
    int h = ui->graphicsView_welcome->minimumHeight();
    animation_movement->setStartValue(QRect(pos.x(), pos.y(), w, h));
    animation_movement->setKeyValueAt(0.05, QRect(pos.x()-25, pos.y(), w, h));
    animation_movement->setEndValue(QRect(pos.x(), pos.y(), w, h));
    animation_movement->setEasingCurve(QEasingCurve::InQuint);
    animation_movement->start(QPropertyAnimation::DeleteWhenStopped);
}

QPushButton *login::get_btn_login()
{
    return btn_login;
}

QPushButton *login::get_btn_logout()
{
    return btn_logout;
}

QGraphicsView *login::get_graph_welcome()
{
    return graph_welcome;
}

QLabel *login::get_lbl_acc()
{
    return lbl_acc;
}

QLabel *login::get_lbl_channel()
{
    return lbl_channel;
}

QLineEdit *login::get_ledit_acc()
{
    return lEdit_acc;
}

QComboBox *login::get_cmb_chn()
{
    return cmb_chn;
}

QLabel *login::get_lbl_message()
{
    return lbl_message;
}

void login::setup_invalidAccount()
{
    //show a vibrating animation to grab the attention of the user
    animation_movement = new QPropertyAnimation(this, "geometry");
    animation_movement->setDuration(300);
    animation_movement->setStartValue(QRect(rect().x()+30, this->y(), rect().width(), rect().height()));
    animation_movement->setEndValue(QRect(this->x(), this->y(), rect().width(), rect().height()));
    animation_movement->setEasingCurve(QEasingCurve::OutBounce);
    animation_movement->start(QPropertyAnimation::DeleteWhenStopped);

    //show appropriate message for invalid accounts
    show_invalidMessage(lbl_msg_incorrectAcc);
}

void login::show_invalidMessage(QString msg)
{
    ui->lbl_welcome->setText(msg);
    ui->lbl_welcome->setStyleSheet("QLabel {background-color: transparent; color: red;}");
    ui->lbl_welcome->show();
}

void login::on_btn_login_pressed()
{

    //check if both the account number and subsciption from the user and database matches

    bool validAccount = false;
    int channelID_user = ui->cmb_channel->currentIndex()+1;
    for (int i = 0 ; i < data_accounts->rowCount(); i++)
    {
        int accountValue_user = ui->lineEdit_acc->text().toInt();
        int accountValue_data = data_accounts->record(i).value(1).toInt();

        if(accountValue_user == accountValue_data)                                      //check if the account number matches
        {
            validAccount = true;
            int channelID_data = data_accounts->record(i).value(2).toInt();
            if(channelID_user == channelID_data)                                        //check if the subscription matches
            {
                setup_loggedIn(accountValue_user);
                emit signal_matchingIDs(channelID_user);                                //for valid accounts, show appropriate views and emit channelID
                return;
            }
        }
    }
    if(validAccount)
    {
        setup_loggedIn(ui->lineEdit_acc->text().toInt());
        emit signal_matchingIDs(-1);                                //for valid accounts, show appropriate views and emit channelID
        return;
    }
    setup_invalidAccount();                                                             //for invalid accounts
}

void login::on_btn_loggout_released()
{
    //hide log out views and show login views with animation
    ui->lbl_acc->show();
    ui->lbl_channel->show();
    ui->lineEdit_acc->show();
    ui->lineEdit_acc->clear();
    ui->cmb_channel->show();
    ui->btn_login->show();

    ui->lbl_welcome->hide();
    ui->btn_loggout->hide();

    setup_animation();
    emit signal_reset();
}
