#-------------------------------------------------
#
# Project created by QtCreator 2015-03-14T00:30:19
#
#-------------------------------------------------

TARGET = VirtinV4
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    Genetic/MutationNode.cpp \
    Genetic/GenticalNode.cpp \
    Genetic/Generate.cpp \
    Genetic/CrossNode.cpp \
    GenticAlgo/GeneticSelection.cpp \
    GenticAlgo/GeneticalIndividu.cpp \
    GenticAlgo/GeneticAlgo.cpp \
    VirtualMachine/VirtualMachine.cpp \
    GenticAlgo/GeneticalPool.cpp \
    ObjClass.cpp \
    Genetic/GeneticObj.cpp \
    GenticAlgo/GenerateAlgo.cpp \
    GenticAlgo/execPool.cpp

INCLUDEPATH += include
INCLUDEPATH += include/Genetic

HEADERS += \
    include/VirtualMachine/VirtualMachine.hpp \
    include/obj.hpp \
    include/Genetic/GeneticObj.hpp \
    include/Genetic/GeneticalPool.hpp \
    include/Genetic/GeneticalNode.hpp \
    include/Genetic/GeneticalIndividual.hpp \
    include/Genetic/GeneticalAlgo.hpp
