QT += testlib
QT += gui core gui widgets sql
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

SOURCES +=  tst_testreward.cpp \
    custom_combobox.cpp \
    custom_graphicsview.cpp \
    database.cpp \
    delegate_combobox.cpp \
    globalvariables.cpp \
    login.cpp \
    mainwindow.cpp \
    reward.cpp

RESOURCES += \
    resource.qrc

FORMS += \
    login.ui \
    mainwindow.ui \
    reward.ui

HEADERS += \
    custom_combobox.h \
    custom_graphicsview.h \
    database.h \
    delegate_combobox.h \
    globalvariables.h \
    login.h \
    mainwindow.h \
    reward.h


