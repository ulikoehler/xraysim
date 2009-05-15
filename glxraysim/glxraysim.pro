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
    alphatestdialog.cpp \
    configurematerialdialog.cpp \
    togglefeaturesdialog.cpp \
    sobel.cpp
HEADERS += mainwindow.h \
    xrayglwidget.h \
    gldialog.h \
    graphicsdialog.h \
    configurelightdialog.h \
    alphatestdialog.h \
    configurematerialdialog.h \
    globaldef.h \
    togglefeaturesdialog.h \
    sobel.h
FORMS += mainwindow.ui \
    gldialog.ui \
    graphicsdialog.ui \
    configurelightdialog.ui \
    alphatestdialog.ui \
    configurematerialdialog.ui \
    togglefeaturesdialog.ui
QMAKE_CXXFLAGS -= -O2
QMAKE_CXXFLAGS += -O3 \
    -march=core2
OTHER_FILES += TODO.txt
