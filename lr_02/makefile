CC := gcc
PARAMS := -std=c99 -Wall -Werror -pedantic

input.o: input.c *.h
	$(CC) $(PARAMS) -c input.c

app.o: app.c *.h
	$(CC) $(PARAMS) -c app.c

app.exe: app.o input.o
	$(CC) -o app.exe $^

make clean:
	rm *.exe *.o