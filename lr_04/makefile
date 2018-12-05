app.exe: app.o io.o stack.o palindrom.o
	gcc -o app.exe app.o io.o stack.o palindrom.o

app.o: app.c *.h
	gcc -std=c99 -Wall -Werror -pedantic -g3 -ggdb -c app.c

io.o: io.c *.h
	gcc -std=c99 -Wall -Werror -pedantic -g3 -ggdb -c io.c

stack.o: stack.c *.h
	gcc -std=c99 -Wall -Werror -pedantic -g3 -ggdb -c stack.c

palindrom.o: palindrom.c *.h
	gcc -std=c99 -Wall -Werror -pedantic -g3 -ggdb -c palindrom.c

clean:
	rm *.exe *.o
