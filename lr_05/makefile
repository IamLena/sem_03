PARAMS := -std=c99 -Wall -Werror -pedantic -g3 -ggdb

app.exe: app.o func.o queue.o
	gcc -o app.exe app.p func.o queue.o

app.o: app.c *.h
	gcc $(PARAMS) -c app.c

func.o: func.c *.h
	gcc $(PARAMS) -c func.c

queue.o: queue.c *.h
	gcc $(PARAMS) -c queue.c

clean:
	rm *.exe *.o