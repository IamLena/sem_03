CC := gcc
PARAMS := -std=c99 -Wall -Werror -pedantic

input.o: input.c *.h
	$(CC) $(PARAMS) -c input.c

output.o: output.c *.h
	$(CC) $(PARAMS) -c output.c

app.o: app.c *.h
	$(CC) $(PARAMS) -c app.c

action.o: action.c *.h
	$(CC) $(PARAMS) -c action.c

delete.o: delete.c *.h
	$(CC) $(PARAMS) -c delete.c

app.exe: app.o input.o action.o output.o delete.o
	$(CC) -o app.exe $^

make clean:
	rm *.exe *.o