#!/bin/bash

RESULT=Answer.cpp
HEADERS="Coord2.h Line2.h Unit.h State.h Solver.h"
CXXFILES="Coord2.cpp Line2.cpp Unit.cpp State.cpp Solver.cpp main.cpp"

rm $RESULT
cat $HEADERS $CXXFILES | sed '/include "/d' >> $RESULT

