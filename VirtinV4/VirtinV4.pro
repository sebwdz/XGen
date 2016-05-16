#-------------------------------------------------
#
# Project created by QtCreator 2015-03-14T00:30:19
#
#-------------------------------------------------

TARGET = VirtinV4
TEMPLATE = lib
CONFIG += staticlib

LIBS += -lpthread -L /usr/lib/x86_64-linux-gnu/libboost_thread.so
LIBS += -L /usr/lib/x86_64-linux-gnu/libboost_system.so


SOURCES += \
    Genetic/GenticalNode.cpp \
    Genetic/Generate.cpp \
    ObjClass.cpp \
    Genetic/GeneticObj.cpp \
    Genetic/Individu.cpp \
    Genetic/GeneticalAorithm.cpp \
    ../GenLib/Decriptor/Chanel.cpp

INCLUDEPATH += include
INCLUDEPATH += include/Genetic
INCLUDEPATH += ../GenLib/include/

HEADERS += \
    include/obj.hpp \
    include/Genetic/GeneticObj.hpp \
    include/Genetic/GeneticalNode.hpp \
    include/Genetic/Serialize.hpp \
    include/Genetic/GeneticalAorithm.hpp \
    include/Genetic/Individu.hpp

QMAKE_CXXFLAGS_RELEASE -= -O
QMAKE_CXXFLAGS_RELEASE -= -O1
QMAKE_CXXFLAGS_RELEASE -= -O2

QMAKE_CXXFLAGS_RELEASE += -O3
