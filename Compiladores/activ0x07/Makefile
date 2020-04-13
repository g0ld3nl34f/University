CC = gcc
CFLAGS = -g
OUTFILE = ya!
LIBS = -lm


all: parser.c lexer.c
	$(CC) $(CFLAGS) parser.c ya.c -o $(OUTFILE) $(LIBS)

parser.c: yaexclamationmark.y
	bison -y -d yaexclamationmark.y -o parser.c

lexer.c: yaexclamationmark.lex
	flex -o ya.c yaexclamationmark.lex

clean: 
	rm -rf parser.c parser.h ya.c
	rm -f *~
	rm -f *.o
