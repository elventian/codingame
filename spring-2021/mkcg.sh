#!/bin/bash

RESULT=Answer.cpp
HEADERS="../grid2d/Hex.h Tree.h Cell.h Map.h Configuration.h Action.h State.h"
CXXFILES="../grid2d/Hex.cpp Map.cpp Cell.cpp State.cpp main.cpp"

rm $RESULT
cat $HEADERS $CXXFILES | sed '/include "/d' >> $RESULT

