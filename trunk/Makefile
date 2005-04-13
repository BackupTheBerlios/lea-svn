all: lea

TMPS=lex.yy.c lea.tab.c
OBJS=lea-translator.o symbol-table.o
LEX_SRC=lea.l
YACC_SRC=$(LEX_SRC:.l=.y)
OUT=$(LEX_SRC:.l=)

LEX=flex
YACC=bison

lea: $(OBJS)
	$(LEX) $(LEX_SRC)
	$(YACC) --verbose -d $(YACC_SRC)
	$(CC) -o $(OUT) $(TMPS) $(OBJS) -lfl -lm $(CFLAGS)

clean:
	$(RM) -f $(TMPS) $(OUT) *.o *~

prueba:
	$(CC) -o prueba prueba.c

install:
	cp lea /bin/
