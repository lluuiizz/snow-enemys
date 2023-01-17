#!/bin/bash

g++ Main.cpp Player.cpp -o Game.o -lSDL2 -lSDL2_image && ./Game.o
