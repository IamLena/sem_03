CC := gcc
PARAMS := -std=c99 -Wall -Werror -g3 -pedantic -ggdb

app.o: app.c *.h
	$(CC) $(PARAMS) -c app.c

io.o: io.c *.h
	$(CC) $(PARAMS) -c io.c

file.o: file.c *.h
	$(CC) $(PARAMS) -c file.c

mult.o: mult.c *.h
	$(CC) $(PARAMS) -c mult.c

matrix_mem.o: matrix_mem.c *.h
	$(CC) $(PARAMS) -c matrix_mem.c

app.exe: app.o io.o mult.o file.o matrix_mem.o
	$(CC) -o app.exe app.o io.o mult.o file.o matrix_mem.o

clean:
	rm *.exe *.o