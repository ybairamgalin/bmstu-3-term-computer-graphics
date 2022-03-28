QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    arc.cpp \
    ellipse.cpp \
    figure.cpp \
    lab1solver.cpp \
    lab2dock.cpp \
    lab3dock.cpp \
    line.cpp \
    linedrawer.cpp \
    main.cpp \
    mainwindow.cpp \
    renderarea.cpp \
    triangle.cpp

HEADERS += \
    arc.h \
    ellipse.h \
    figure.h \
    lab1solver.h \
    lab2dock.h \
    lab3dock.h \
    line.h \
    linedrawer.h \
    mainwindow.h \
    renderarea.h \
    triangle.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
