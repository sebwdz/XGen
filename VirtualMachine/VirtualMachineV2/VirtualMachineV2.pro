#-------------------------------------------------
#
# Project created by QtCreator 2015-04-03T18:34:27
#
#-------------------------------------------------

TARGET = Genetic
TEMPLATE = lib

QT += core qui

CONFIG += plugin

INCLUDEPATH += ../../VirtinV4/include
INCLUDEPATH += include/
INCLUDEPATH += ../../Virtin/include

LIBS += ../../build-VirtinV4-Desktop-Debug/libVirtinV4.a -lboost_thread /usr/lib64/libsfml-graphics.so

SOURCES += \
    Cell/Module.cpp \
    Cell/CellClass.cpp \
    Cell/Brain.cpp \
    Decriptor/Decriptor.cpp \
    Decriptor/DrecriptorManager.cpp \
    Decriptor/ExecDecriptor.cpp \
    Decriptor/LineDecriptor.cpp \
    Engine.cpp \
    ../../Virtin/Plugin.cpp \
    BrainMachine.cpp \
    Tester.cpp \
    BrainView.cpp \
    Cell/Skeleton.cpp \
    Object/SignalManager.cpp \
    Object/Object.cpp \
    Object/Movable.cpp \
    Environment.cpp \
    Decriptor/Chanel.cpp \
    Decriptor/ChanPropriety.cpp

HEADERS += \
    include/Cell/Module.hpp \
    include/Cell/CellClass.hpp \
    include/Decriptor/LineDecrip.hpp \
    include/Engine.hpp \
    include/Cell/Brain.hpp \
    include/Decriptor/Decriptor.hpp \
    include/Decriptor/DecriptorManager.hpp \
    include/Decriptor/Opt.hpp \
    include/Tester.hpp \
    include/BrainView.hpp \
    include/Cell/Skeleton.hpp \
    include/Object/Signal.hpp \
    include/Object/Object.hpp \
    include/BrainMachine.hpp \
    include/Object/Movable.hpp \
    include/Environment.hpp \
    include/Decriptor/chanel.hpp \
    include/Decriptor/ChanelPropriety.hpp
