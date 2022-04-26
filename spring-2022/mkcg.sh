#!/bin/bash

RESULT=Answer.cpp
HEADERS="../grid2d/Coord2.h Monster.h Action.h Unit.h State.h"
CXXFILES="../grid2d/Coord2.cpp Monster.cpp Unit.cpp State.cpp main.cpp"

rm $RESULT
cat $HEADERS $CXXFILES | sed '/include "/d' >> $RESULT

