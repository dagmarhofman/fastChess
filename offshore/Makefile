all:
	pgn-extract eco.pgn -Wxolalg --fencomments -C > input.txt
	gcc -c strip.c
	gcc -o strip strip.o
	./strip | grep -v Event | grep -v Site | grep -v Date | grep -v Round | grep -v White | grep -v Black | grep -v Result > output.txt
