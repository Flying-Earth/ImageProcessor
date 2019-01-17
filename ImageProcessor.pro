#-------------------------------------------------
#
# Project created by QtCreator 2018-06-05T20:46:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ImageProcessor
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    matrix.cpp \
    mypismap.cpp \
    imageprocessor.cpp \
    dialoglog.cpp \
    dialogcontrast.cpp \
    dialoglinear.cpp \
    dialogcrop.cpp \
    dialoggauss.cpp \
    dialogbilateral.cpp \
    dialogmid.cpp \
    dialogerode.cpp \
    dialogdilate.cpp \
    fft.cpp \
    dialogaffine.cpp \
    dialoglowpass.cpp \
    dialoghighpass.cpp

HEADERS += \
        mainwindow.h \
    matrix.h \
    mypismap.h \
    imageprocessor.h \
    dialoglog.h \
    dialogcontrast.h \
    dialoglinear.h \
    dialogcrop.h \
    dialoggauss.h \
    dialogbilateral.h \
    dialogmid.h \
    dialogerode.h \
    dialogdilate.h \
    fft.h \
    dialogaffine.h \
    dialoglowpass.h \
    dialoghighpass.h

FORMS += \
        mainwindow.ui \
    dialoglog.ui \
    dialogcontrast.ui \
    dialoglinear.ui \
    dialogcrop.ui \
    dialoggauss.ui \
    dialogbilateral.ui \
    dialogmid.ui \
    dialogerode.ui \
    dialogdilate.ui \
    dialogaffine.ui \
    dialoglowpass.ui \
    dialoghighpass.ui
