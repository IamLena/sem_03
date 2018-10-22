CC := gcc
PARAMS := -std=c99 -Wall -Werror -pedantic -ggdb

ifeq ($(mode), debug)
	PARAMS += -g3
endif

%.o: %.c *.h
	$(CC) $(PARAMS) -c $<

app.exe: app.o input.o add.o output.o delete.o file.o sort.o
	$(CC) -o app.exe $^

make clean:
	rm *.exe *.o
