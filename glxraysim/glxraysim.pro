# -------------------------------------------------
# Project created by QtCreator 2009-04-23T15:14:34
# -------------------------------------------------
QT += opengl
TARGET = glxraysim
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    xrayglwidget.cpp \
    gldialog.cpp \
    graphicsdialog.cpp \
    configurelightdialog.cpp \
    alphatestdialog.cpp
HEADERS += mainwindow.h \
    xrayglwidget.h \
    gldialog.h \
    graphicsdialog.h \
    configurelightdialog.h \
    alphatestdialog.h
FORMS += mainwindow.ui \
    gldialog.ui \
    graphicsdialog.ui \
    configurelightdialog.ui \
    alphatestdialog.ui
QMAKE_CXXFLAGS -= -O2
QMAKE_CXXFLAGS += -O3 -march=core2