@echo off
rm *.exe
gcc -std=c99 -Wall -Werror -o app.exe app.c
for %%i in (1 2 3 4 5 6 7 8 9 10 11 12 13 14) do call test.bat %%i