QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../controller/controller.cc \
    ../model/calculation.cc \
    ../model/model.cc \
    ../model/polish_notation.cc \
    ../model/utils.cc \
    ../model/validation.cc \
    ../main.cc \
    graphlib/qcustomplot.cpp \
    mainwindow/view.cc

HEADERS += \
    ../controller/controller.h \
    ../model/calculation.h \
    ../model/model.h \
    ../model/polish_notation.h \
    ../model/utils.h \
    ../model/validation.h \
    graphlib/qcustomplot.h \
    mainwindow/view.h

FORMS += \
    mainwindow/view.ui

INCLUDEPATH += "."
INCLUDEPATH += "mainwindow"
INCLUDEPATH += "graphlib"

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
