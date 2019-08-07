#include <QtTest>
#include <QCoreApplication>

#include "database.h"
#include "globalvariables.h"
#include "login.h"
#include "mainwindow.h"
#include "custom_combobox.h"
#include <QLineEdit>
// add necessary includes here

class TestReward : public QObject
{
    Q_OBJECT

public:
    TestReward();
    ~TestReward();

private slots:
    void test_mainWindow();
    void test_database();
    void test_globalVariables();
    void test_login();
    void test_reward();
private:

    database dbase;
    login logIn;
    reward reward;
    MainWindow main;

};

TestReward::TestReward()
{

}

TestReward::~TestReward()
{

}

void TestReward::test_mainWindow()
{
    QVERIFY(main.get_wig_login() != nullptr);
    QVERIFY(main.get_wig_reward() != nullptr);

    QMainWindow window;
    window.setWindowIcon(QIcon(":/ICON_SKY"));
    //QCOMPARE(main.windowIcon(),window.windowIcon());          //couldn't test the windows ICON

    QCOMPARE(main.windowTitle(),QString("Rewards"));
}

void TestReward::test_database()
{
    QVERIFY(dbase.getSqlAccounts()->rowCount()>0);
    QVERIFY(dbase.getSqlChannelsRewards()->rowCount()>0);
}

void TestReward::test_globalVariables()
{
    QVERIFY(global_get_database());
}

void TestReward::test_login()
{
    //check if all views were constructed
    QVERIFY(logIn.get_graph_welcome()   != nullptr);
    QVERIFY(logIn.get_lbl_acc()         != nullptr);
    QVERIFY(logIn.get_ledit_acc()       != nullptr);
    QVERIFY(logIn.get_lbl_channel()     != nullptr);
    QVERIFY(logIn.get_cmb_chn()         != nullptr);
    QVERIFY(logIn.get_btn_login()       != nullptr);
    QVERIFY(logIn.get_btn_logout()      != nullptr);
    QVERIFY(logIn.get_lbl_message()     != nullptr);

    //check if the account number can be entered
    QTest::keyClicks(logIn.get_ledit_acc(), "111");
    QCOMPARE(logIn.get_ledit_acc()->text(),QString("111"));


    //check if combobox is showing correct current item
    QByteArray byte = dbase.getSqlChannelsRewards()->record(0).value(2).toByteArray();
    QPixmap pix;
    pix.loadFromData(byte);

    QCOMPARE(qvariant_cast<QPixmap>(logIn.get_cmb_chn()->currentData(Qt::UserRole)),pix );

    //check if combobox has all items
    int rowCount = dbase.getSqlChannelsRewards()->rowCount();
    QCOMPARE(logIn.get_cmb_chn()->count(),rowCount);

    //check if correct signal and channelID are emitted when the correct account number and subscription match
    QSignalSpy spy_reward(&logIn, &login::signal_matchingIDs);

    logIn.get_ledit_acc()->clear();
    QTest::keyClicks(logIn.get_ledit_acc(), "111");
    QTest::mouseClick(logIn.get_btn_login(), Qt::LeftButton);
    QCOMPARE(spy_reward.count(), 1);

    QList<QVariant> channelID= spy_reward.takeFirst();
    QCOMPARE(channelID.at(0).toInt(), 1);

    //check if the message for the match is correct
    QCOMPARE(logIn.get_lbl_message()->text(),QString("Welcome user 111"));

    //check if correct signal and channelID are emitted when the correct account number and subscription don't match
    logIn.get_ledit_acc()->clear();
    QTest::keyClicks(logIn.get_ledit_acc(), "112");
    QTest::mouseClick(logIn.get_btn_login(), Qt::LeftButton);
    QCOMPARE(spy_reward.count(), 1);

    QList<QVariant> channelID2= spy_reward.takeFirst();
    QCOMPARE(channelID2.at(0).toInt(), -1);

    //check if the message for mismatch is correct
    QCOMPARE(logIn.get_lbl_message()->text(),QString("Welcome user 112"));

    //check the message for incorrect account number
    logIn.get_ledit_acc()->clear();
    QTest::keyClicks(logIn.get_ledit_acc(), "1111");
    QTest::mouseClick(logIn.get_btn_login(), Qt::LeftButton);
    QCOMPARE(logIn.get_lbl_message()->text(),QString("Invalid Account Number"));
    QCOMPARE(logIn.get_lbl_message()->styleSheet(),QString("QLabel {background-color: transparent; color: red;}"));

    //check if the correct signal is emitted with the invalid account number
    QSignalSpy spy_reset(&logIn, &login::signal_reset);
    QTest::mouseClick(logIn.get_btn_logout(), Qt::LeftButton);
    QCOMPARE(spy_reset.count(), 1);

}

void TestReward::test_reward()
{

    //check if all views were constructed
    QVERIFY(reward.get_wig_reward() != nullptr);


    //check if correct text and image are showen when the correct account number and subscription match
    main.get_wig_login()->get_ledit_acc()->clear();
    main.get_wig_login()->get_ledit_acc()->setText("111");
    QTest::mouseClick(main.get_wig_login()->get_btn_login(), Qt::LeftButton);

    QByteArray byte = dbase.getSqlChannelsRewards()->record(0).value(5).toByteArray();
    QPixmap pix_raw;
    pix_raw.loadFromData(byte);
    QPixmap pix = pix_raw.scaledToWidth(main.get_wig_reward()->get_wig_reward()->width(),Qt::SmoothTransformation);

    //check for correct reward image
    QCOMPARE(main.get_wig_reward()->get_wig_reward()->get_pixmap(),pix );

    //check for correct reward text
    QString text = dbase.getSqlChannelsRewards()->record(0).value(3).toString();
    QCOMPARE( main.get_wig_reward()->get_wig_reward()->get_text(),text);

}


QTEST_MAIN(TestReward)

#include "tst_testreward.moc"
