CC = gcc
CFLAGS = -g
OUTFILE = ya
LIBS = -lm


all: parser.c lexer.c parser.h yatypes.o latex.o
	$(CC) $(CFLAGS) parser.c lexer.c yatypes.o latex.o -o $(OUTFILE) $(LIBS)

parser.c: yaexclamationmark.y
	bison -y -d yaexclamationmark.y -o parser.c

lexer.c: yaexclamationmark.lex
	flex -o lexer.c yaexclamationmark.lex

yatypes.o: yatypes.h yatypes.c
	gcc $(CFLAGS) -c yatypes.c

latex.o: latex.h latex.c
	gcc $(CFLAGS) -c latex.c

clean: 
	rm -rf parser.c lexer.c parser.h
	rm -f *~
	rm -f *.o
	rm -f ya
