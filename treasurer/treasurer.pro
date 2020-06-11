QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT += sql

TARGET = test # La cible de compilation, le résultat

CONFIG += c++11 console
CONFIG -= app_bundle

TEMPLATE = app # On veut une application, oui

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        ajoutercomptemodal.cpp \
        cloturemodal.cpp \
        compte.cpp \
        comptecontroller.cpp \
        comptesview.cpp \
        compteview.cpp \
        connexionview.cpp \
        databasemanager.cpp \
        main.cpp \
        operation.cpp \
        rapport.cpp \
        rapportsview.cpp \
        rapportview.cpp \
        rapprochercomptemodal.cpp \
        transaction.cpp \
        transactionview.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    ajoutercomptemodal.ui \
    ajoutertransactionmodal.ui \
    cloturemodal.ui \
    comptesview.ui \
    compteview.ui \
    connexionview.ui \
    rapportsview.ui \
    rapportview.ui \
    rapprochercomptemodal.ui \
    transactionview.ui

HEADERS += \
    ajoutercomptemodal.h \
    cloturemodal.h \
    compte.h \
    comptecontroller.h \
    comptesview.h \
    compteview.h \
    connexionview.h \
    databasemanager.h \
    operation.h \
    rapport.h \
    rapportsview.h \
    rapportview.h \
    rapprochercomptemodal.h \
    transaction.h \
    transactionview.h

RC_ICONS = ../ressources/logo.ico





