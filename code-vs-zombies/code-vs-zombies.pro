TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

DEFINES += INPUT_FILE

SOURCES += \
        main.cpp \
    Coord2.cpp \
    State.cpp \
    Solver.cpp

HEADERS += \
    Coord2.h \
    Unit.h \
    State.h \
    Solver.h
