TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

DEFINES += INPUT_FILE

SOURCES += \
    main.cpp \
    State.cpp \
    ../grid2d/Hex.cpp \
    Map.cpp \
    Cell.cpp

HEADERS += \
    State.h \
    ../grid2d/Hex.h \
    Map.h \
    Cell.h \
    Tree.h \
    Action.h

INCLUDEPATH += ../grid2d/
