@echo off
g++ ../new_src/*.cpp -o Game.exe -O2 -I ../include/ -L ../lib/ -lraylib -lgdi32 -lwinmm
pause