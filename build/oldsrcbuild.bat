@echo off
g++ ../src/*.cpp ../src/pieces/*.cpp -o Game.exe -O2 -I ../include/ -L ../lib/ -lraylib -lgdi32 -lwinmm
pause