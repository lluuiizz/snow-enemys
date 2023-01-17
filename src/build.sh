#!/bin/bash

g++ Main.cpp Player.cpp GameObjs.cpp -o Game.o -lSDL2 -lSDL2_image && ./Game.o
