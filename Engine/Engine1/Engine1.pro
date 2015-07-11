#-------------------------------------------------
#
# Project created by QtCreator 2015-03-27T01:33:55
#
#-------------------------------------------------

TARGET = Engine1
TEMPLATE = lib

INCLUDEPATH += ../../VirtinV4/include/
INCLUDEPATH += include

CONFIG += plugin
CONFIG += DEBUG

SOURCES += engine1.cpp \
    TextEditor.cpp \
    ../../Virtin/Plugin.cpp \
    SyntaxHighlighter.cpp

LIBS    += ../../build-VirtinV4-Desktop-Debug/libVirtinV4.a

HEADERS += \
    include/EditWidget.hpp \
    include/engine1.hpp \
    include/SyntaxHightLighter.hpp
