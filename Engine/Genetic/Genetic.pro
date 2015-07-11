#-------------------------------------------------
#
# Project created by QtCreator 2015-04-03T18:34:27
#
#-------------------------------------------------

TARGET = Genetic
TEMPLATE = lib

CONFIG += plugin

INCLUDEPATH += ../../VirtinV4/include

LIBS += ../../build-VirtinV4-Desktop-Debug/libVirtinV4.a /usr/lib64/libboost_thread.so

SOURCES += genetic.cpp \
    ../../Virtin/Plugin.cpp \
    GeneticWidget.cpp \
    ProprietyWidget.cpp \
    PoolPropriety.cpp \
    StateWidget.cpp \
    PopulationWidget.cpp \
    IndividuWidget.cpp \
    GeneratePopulation.cpp \
    EngineWidget.cpp

HEADERS += genetic.h \
    include/GeneticWidget.hpp \
    include/ProprietyWidget.hpp \
    include/PoolPropriety.hpp \
    include/StateWidget.hpp \
    include/PopulationWidget.hpp \
    include/InidividuWidget.hpp \
    include/GeneratePopulation.hpp \
    include/EngineWidget.hpp
