all: lea

TMPS=lex.yy.c lea.tab.c
OBJS=lea-translator.o symbol-table.o
LEX_SRC=lea.l
YACC_SRC=$(LEX_SRC:.l=.y)
OUT=$(LEX_SRC:.l=)

ERASABLE=$(TMPS) lea.tab.h $(OUT) *.o *~
WRITTEN=*{.h,.c,.y,.awk,Makefile}

LEX=flex
YACC=bison

lea: $(OBJS)
	$(LEX) $(LEX_SRC)
	$(YACC) --verbose -d $(YACC_SRC)
	$(CC) -o $(OUT) $(TMPS) $(OBJS) -lfl -lm $(CFLAGS)

clean:
	$(RM) -f $(ERASABLE)

prueba:
	$(CC) -o prueba prueba.c

install:
	cp lea /bin/
	
wc:
	wc -l $(WRITTEN) | tail -n 1

