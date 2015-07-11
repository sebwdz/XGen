#-------------------------------------------------
#
# Project created by QtCreator 2015-03-23T21:33:54
#
#-------------------------------------------------

QT       += core

TARGET = Virtin

LIBS    += ../build-VirtinV4-Desktop-Debug/libVirtinV4.a -ldl -lboost_thread -lboost_system

INCLUDEPATH += ../VirtinV4/include

TEMPLATE = app

CONFIG += DEBUG

SOURCES += main.cpp \
    MainWindow.cpp \
    MenuBar.cpp \
    ListOpen.cpp \
    MainWidget.cpp \
    Manager/Manager.cpp \
    Manager/Folder.cpp \
    ModelListOpen.cpp \
    Manager/WorkSpace.cpp \
    OpenItem.cpp \
    Manager/OpenFile.cpp \
    ChooseElement.cpp \
    Plugin.cpp

HEADERS += \
    include/MainWindow.hpp \
    include/MenuBar.hpp \
    include/ListOpen.hpp \
    include/MainWidget.hpp \
    include/Manager/Manager.hpp \
    include/Manager/Folder.hpp \
    include/Manager/WorkSpace.hpp \
    include/ModelListOpen.hpp \
    include/Manager/OpenFile.hpp \
    include/ChooseElement.hpp \
    include/Plugin.hpp
