#include <stdio.h>
#include <stdlib.h>

/*
    use:

    pgn-extract pgnfile.pgn -Wxolalg --fencomments -C > input.txt

    to generete input file from some pgn file.

*/

int main()
{
    FILE *fp;
    char c;

    fp=fopen("input.txt","r");

    while(!feof(fp)) {
	c = fgetc(fp);
	if( c == '[' ) {
	 	do {
			putchar(c);
			c = fgetc(fp);
		} while (c != ']');
		putchar(c);
		putchar('\n');
	}
	if( c == '{' ) {
		putchar(c);
		c = fgetc(fp);
		if( c != ' ' ) 
		    putchar(' ');
	 	do {
			if( c != '\n')
				putchar(c);
			c = fgetc(fp);
		} while (c != '}');
		putchar(c);
		putchar('\n');
	}
    }

}
