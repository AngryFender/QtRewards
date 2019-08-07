#include "reward.h"
#include "ui_reward.h"

const QString reward::msg_welcome = "Login to find your rewards";
const QString reward::msg_noReward = "Not eligible for rewards :(";


reward::reward(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::reward)
{
    //extract tables from the database
    data_channels = global_get_database()->getSqlChannelsRewards();

    //setup views and animation
    setup_animation1();
    setup_backgroud();
    ui->setupUi(this);
    setup_graphicsView();
}

reward::~reward()
{
    delete ui;
    delete effect_opacity;
}

custom_graphicsView *reward::get_wig_reward()
{
    return wig_reward;
}

void reward::slot_matchingID(int channelID)
{
    //receive channelID and show appropriate rewards
    update_rewards(channelID);
}

void reward::slot_reset()
{
    //reset all views and animation
    setup_graphicsView();
    setup_animation1();
}

void reward::setup_backgroud()
{
    pix_background = QPixmap( ":/IMAGE_BACKGROUND");
}

void reward::setup_animation1()
{
    //at the first paint event of the widget, emit signal to start animation, this way the widget will end up in their correct co ordinates
    firstPaint = false;
    connect(this,SIGNAL(signal_firstPaint()),this,SLOT(execute_animation1()));
}

void reward::paintEvent(QPaintEvent *event)
{
    (void)event;
    //Make the frame of the parent widget a rectagle with rounded corner, fill this rectage with background image
    QPainter * painter = new QPainter(this);

    QPainterPath path;
    path.addRoundedRect(rect(), 10, 10);
    painter->setClipPath(path);
    QPen pen(Qt::transparent, 0);
    painter->setPen(pen);
    painter->drawPixmap(rect(),pix_background);

    delete painter;

    if(!firstPaint)
    {
        firstPaint = true;
        emit signal_firstPaint();
    }
}

void reward::setup_graphicsView()
{
    ui->widget_reward->set_pixmap( QPixmap( ":/IMAGE_REWARD"));
    ui->widget_reward->set_icon(QPixmap());
    ui->widget_reward->set_text(msg_welcome);

    wig_reward = ui->widget_reward;
    this->update();
}

void reward::update_rewards(int row)
{
    QString str_reward(msg_noReward);
    QPixmap pix_bgd(":/IMAGE_NOTFOUND");
    QPixmap pix_icon;

    //show images and text of appropriate rewards

    row--;
    if(row >= 0 && row <data_channels->rowCount())
    {
        QByteArray byte;
        QByteArray byte_bgd;
        str_reward= data_channels->record(row).value(3).toString();
        byte = data_channels->record(row).value(4).toByteArray();

        pix_icon.loadFromData(byte);

        byte_bgd = data_channels->record(row).value(5).toByteArray();
        pix_bgd.loadFromData(byte_bgd);
    }

    ui->widget_reward->set_pixmap(pix_bgd);
    ui->widget_reward->set_text(str_reward);
    ui->widget_reward->set_icon(pix_icon);

    setup_animation2();
}

void reward::execute_animation1()
{
    effect_opacity    = new QGraphicsOpacityEffect(this);
    animation_opacity = new QPropertyAnimation(effect_opacity,"opacity");

    //setup and start opacity animation to the whole parent widget
    effect_opacity->setOpacity(0);
    this->setGraphicsEffect(effect_opacity);
    animation_opacity->setDuration(800);
    animation_opacity->setStartValue(0);
    animation_opacity->setEndValue(1);
    animation_opacity->setEasingCurve(QEasingCurve::InBack);
    animation_opacity->start(QPropertyAnimation::DeleteWhenStopped);

    //setup and start geometry animation only to the graphicsView showing the reward image
    QPoint pos(ui->widget_reward->x(),ui->widget_reward->y());
    int w = ui->widget_reward->minimumWidth();
    int h = ui->widget_reward->minimumHeight();
    animation_movement = new QPropertyAnimation(ui->widget_reward, "geometry");
    animation_movement->setDuration(600);
    animation_movement->setStartValue(QRect(pos.x(),pos.y(), w, h));
    animation_movement->setEndValue(QRect(pos.x(),pos.y(), w, h));
    animation_movement->setEasingCurve(QEasingCurve::InQuint);
    animation_movement->start(QPropertyAnimation::DeleteWhenStopped);
}

void reward::setup_animation2()
{
    //setup and start geometry animation only to the graphicsView showing reward image
    QPoint pos = ui->widget_reward->mapTo(this,QPoint(0,0));
    int w = ui->widget_reward->minimumWidth();
    int h = ui->widget_reward->minimumHeight();
    animation_movement2 = new QPropertyAnimation(ui->widget_reward, "geometry");
    animation_movement2->setDuration(400);
    animation_movement2->setStartValue(QRect(pos.x()+w/2, pos.y(), w, h));
    animation_movement2->setEndValue(QRect(pos.x(), pos.y(), w, h));
    animation_movement2->setEasingCurve(QEasingCurve::OutExpo);
    animation_movement2->start(QPropertyAnimation::DeleteWhenStopped);
}
