all: lea

TMP=lex.yy.c y.tab.c y.tab.h
SRCS=lea-translator.c lex.yy.c y.tab.c
OBJS=$(SRCS:.c=.o)
LEX_SRC=lea.l
YACC_SRC=$(LEX_SRC:.l=.y)
OUT=$(LEX_SRC:.l=)

LEX=flex
YACC=yacc

CFLAGS+=-lm -lfl
#-g -Wall

lea: $(LEX_SRC) $(YACC_SRC) $(OBJS)
	 $(LEX) $(LEX_SRC)
	 $(YACC) --verbose -d $(YACC_SRC)
	 $(CC) -o $(OUT) $(OBJS) $(CFLAGS)
	 
clean:
	$(RM) -f $(TMP) $(OUT)

prueba:
	$(CC) -o prueba prueba.c

install:
	cp lea /bin/
