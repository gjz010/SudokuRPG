#-------------------------------------------------
#
# Project created by QtCreator 2017-08-27T20:18:26
#
#-------------------------------------------------

QT       += core gui opengl multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SudokuRPG
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
        sudokuwindow.cpp \
    glmanager.cpp \
    scenes/scene.cpp \
    simpleinputmanager.cpp \
    scenes/scenemenu.cpp \
    scenes/sceneingame.cpp \
    scenes/sceneloading.cpp \
    DancingLinkSolver.cpp \
    SudokuSolver.cpp \
    imwidgets.cpp \
    scenes/shaderpacker.cpp

HEADERS += \
        sudokuwindow.h \
    glmanager.h \
    scenes/scene.h \
    simpleinputmanager.h \
    scenes/scenemenu.h \
    scenes/sceneingame.h \
    scenes/sceneloading.h \
    scenes/shaderpacker.h \
    DancingLinkSolver.h \
    SudokuSolver.h \
    imwidgets.h


RESOURCES += \
    sudoku.qrc

