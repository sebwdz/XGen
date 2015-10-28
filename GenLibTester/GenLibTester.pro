INCLUDEPATH += ../VirtinV4/include
INCLUDEPATH += ../GenLib/include/

LIBS += ../build-GenLib-Desktop-Debug/libGenLib.a
LIBS += ../build-VirtinV4-Desktop-Debug/libVirtinV4.a
LIBS += -lsfml-graphics -lsfml-window -lsfml-system

SOURCES += \
    main.cpp \
    BrainView.cpp

HEADERS += \
    include/BrainView.hpp
