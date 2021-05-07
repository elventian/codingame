#!/bin/bash

RESULT=Answer.cpp
HEADERS="../grid2d/Cell.h ../grid2d/Coord2.h ../grid2d/Direction.h ../grid2d/Field.h ../grid2d/Contour.h ../grid2d/Map.h Unit.h Action.h State.h Solver.h"
CXXFILES="../grid2d/Cell.cpp ../grid2d/Coord2.cpp ../grid2d/Direction.cpp ../grid2d/Field.cpp ../grid2d/Contour.cpp ../grid2d/Map.cpp  Unit.cpp State.cpp Solver.cpp main.cpp"

rm $RESULT
cat $HEADERS $CXXFILES | sed '/include "/d' >> $RESULT

