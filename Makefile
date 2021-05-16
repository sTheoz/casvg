BIN= casvg
OBJ=  $(BIN).tab.o automate.o lex.yy.o drawSVG.o
but:=bin
#	$(CC) -c lex.yy.c -o lex.yy.o
#	$(CC) -c $(BIN).tab.c -o $(BIN).tab.o

bin: yacc lex $(OBJ)
	$(CC) -o $(BIN).bin $(OBJ) -ll -lm

lex: $(BIN).l
	flex -dTv $(BIN).l
	$(CC) -c lex.yy.c -o lex.yy.o

yacc: $(BIN).y
	bison -d -g -v $(BIN).y
	dot -Tpng $(BIN).dot -o $(BIN).png

%.o : %.c lex %.h
	$(CC) -c $< -o $@

clean:
	rm -fv $(BIN).bin lex.yy.c lex.yy.o *~ $(OBJ) lol.svg