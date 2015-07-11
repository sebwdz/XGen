#-------------------------------------------------
#
# Project created by QtCreator 2015-03-23T21:40:08
#
#-------------------------------------------------

TARGET = VirintASM
TEMPLATE = lib

CONFIG  += plugin
CONFIG  += DEBUG

LIBS    += ../build-VirtinV4-Desktop-Debug/libVirtinV4.a

INCLUDEPATH += ../VirtinV4/include
INCLUDEPATH += ../Virtin/include
INCLUDEPATH += ../VirtualMachine/VirtualMachineV2/include

SOURCES += main.cpp \
    NodeData.cpp \
    Reader.cpp \
    Engine.cpp \
    Compilator.cpp \
    ../Virtin/Plugin.cpp \
    ../VirtualMachine/VirtualMachineV1/Decriptor/Chanel.cpp

HEADERS += \
    include/NodeMaker.hpp \
    include/Engine.hpp \
    include/Compilator.hpp
