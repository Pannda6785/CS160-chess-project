@echo off
g++ ../new_src/*.cpp ../new_src/agents/*.cpp -o Game.exe -O2 -I ../include/ -L ../lib/ -lraylib -lgdi32 -lwinmm
pause