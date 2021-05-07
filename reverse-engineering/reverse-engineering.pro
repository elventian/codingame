TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

DEFINES += INPUT_FILE

SOURCES += \
        main.cpp \
    State.cpp \
    Solver.cpp \
    Unit.cpp \
    ../grid2d/Coord2.cpp \
    ../grid2d/Map.cpp \
    ../grid2d/Field.cpp \
    ../grid2d/Direction.cpp \
    ../grid2d/Contour.cpp

HEADERS += \
    Unit.h \
    State.h \
    Solver.h \
    ../grid2d/Coord2.h \
    ../grid2d/Map.h \
    ../grid2d/Field.h \
    ../grid2d/Cell.h \
    ../grid2d/Direction.h \
    ../grid2d/Contour.h \
    Action.h

INCLUDEPATH += ../grid2d/
