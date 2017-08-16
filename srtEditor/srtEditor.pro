#-------------------------------------------------
#
# Project created by QtCreator 2017-08-16T18:26:14
#
#-------------------------------------------------

QT       += core gui
QT += multimedia
QT += multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = srtEditor
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


SOURCES += main.cpp\
        mainwindow.cpp \
    media_controller/mediacontroller.cpp \
    media_player/player.cpp \
    media_player/videomediaplayerwidget.cpp \
    subs_editor/deligates/iddelegate.cpp \
    subs_editor/deligates/richtextdelegate.cpp \
    subs_editor/deligates/timedelegate.cpp \
    subs_editor/docksubtitleeditorwidget.cpp \
    subs_editor/widgetrichtextedit.cpp \
    utility/encodingname.cpp \
    utility/srtDialog.cpp \
    utility/texteditfont.cpp \
    utility/timeconverter.cpp \
    utility/timestringconverter.cpp \
    utility/utilitylistsrtdialogs.cpp

HEADERS  += mainwindow.h \
    media_controller/mediacontroller.h \
    media_player/player.h \
    media_player/videomediaplayerwidget.h \
    subs_editor/deligates/iddelegate.h \
    subs_editor/deligates/richtextdelegate.h \
    subs_editor/deligates/timedelegate.h \
    subs_editor/docksubtitleeditorwidget.h \
    subs_editor/widgetrichtextedit.h \
    utility/encodingname.h \
    utility/srtDialog.h \
    utility/texteditfont.h \
    utility/timeconverter.h \
    utility/timestringconverter.h \
    utility/utilitylistsrtdialogs.h

RESOURCES += \
    imageresources.qrc

DISTFILES += \
    assets/images/colorpicker.png \
    assets/images/edit-copy.png \
    assets/images/edit-cut.png \
    assets/images/edit-paste.png \
    assets/images/format-text-bold.png \
    assets/images/format-text-italic.png \
    assets/images/format-text-underline.png


INCLUDEPATH += $$PWD/media_controller \
                $$PWD/media_player \
                $$PWD/subs_editor \
                $$PWD/subs_editor/deligates \
                $$PWD/utility
