@echo off

app.exe < .\tests\in_%1.txt > .\tests\out.txt
fc .\tests\out.txt .\tests\out_%1.txt
pause