OBJECTS = lexer.o parser.o

default: mycalc

lexer.o: lexer.c
	gcc -c lexer.c -o lexer.o

parser.o: parser.c
	gcc -c parser.c -o parser.o

mycalc: $(OBJECTS)
	gcc lexer.o parser.o -o mycalc

clean:
	-rm -f lexer.o
	-rm -f parser.o
	-rm -f mycalc