BIN= casvg
OBJ=  $(BIN).tab.o automate.o lex.yy.o drawSVG.o operation.o
but:=bin
CFLAGS=-Wall -Wextra -g 

bin: yacc lex $(OBJ)
	$(CC) $(CFLAGS) -o $(BIN).bin $(OBJ) -ll -lm

lex: $(BIN).l
	flex -dTv $(BIN).l
	$(CC) $(CFLAGS) -c lex.yy.c -o lex.yy.o

yacc: $(BIN).y
	bison -d -g -v $(BIN).y
	dot -Tpng $(BIN).dot -o $(BIN).png

%.o : %.c lex %.h
	$(CC) $(CFLAGS) -c $< -o $@ -lm

clean:
	rm -fv $(BIN).bin lex.yy.c lex.yy.o *~ $(OBJ) lol.svg