#-------------------------------------------------
#
# Project created by QtCreator 2015-03-14T00:30:19
#
#-------------------------------------------------

TARGET = VirtinV4
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    Genetic/GenticalNode.cpp \
    Genetic/Generate.cpp \
    ObjClass.cpp \
    Genetic/GeneticObj.cpp

INCLUDEPATH += include
INCLUDEPATH += include/Genetic

HEADERS += \
    include/obj.hpp \
    include/Genetic/GeneticObj.hpp \
    include/Genetic/GeneticalNode.hpp
