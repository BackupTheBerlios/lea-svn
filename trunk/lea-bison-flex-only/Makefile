all: lea

LEX_SRC=lea.l
YACC_SRC=$(LEX_SRC:.l=.y)
OUT=$(LEX_SRC:.l=)

LEX=flex
YACC=yacc

CFLAGS+=-lm
#-g -Wall

lea: $(LEX_SRC) $(YACC_SRC)
	 $(LEX) $(LEX_SRC)
	 $(YACC) --verbose -d $(YACC_SRC)
	 $(CC) $(CFLAGS) -o $(OUT) lex.yy.c y.tab.c -ly -lfl $(CFLAGS)
	 
clean:
	$(RM) -f lex.yy.c y.tab.c y.tab.h $(OUT)

prueba:
	$(CC) -o prueba prueba.c

install:
	cp lea /bin/
