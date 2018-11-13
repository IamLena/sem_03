CC := gcc
PARAMS := -std=c99 -Wall -Werror -g3 -pedantic -ggdb

app.o: app.c *.h
	$(CC) $(PARAMS) -c app.c

io.o: io.c *.h
	$(CC) $(PARAMS) -c io.c

mult.o: mult.c *.h
	$(CC) $(PARAMS) -c mult.c

app.exe: app.o io.o mult.o
	$(CC) -o app.exe app.o io.o mult.o

clean:
	rm *.exe *.o