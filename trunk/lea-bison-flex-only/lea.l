%{
/**
 * \file lea.y
 * \brief Lea lexical analyzer
 *
 * \author Eduardo Robles Elvira <edulix@iespana.es>
 *
 * This is part of Lea. Lea is free software; 
 * you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * Lea is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with lea; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 * 
 * See COPYING for details.
 */
	#include <stdlib.h>
	#include <string.h>
	#include "y.tab.h"
	//#include "lea.lex.h"
	#define MAX_STR_CONST 1024
	#define lexical_error(a) printf("%s\n", a)
%}

%option always-interactive

%x comment str
%s proc

D			[0-9]
L			[a-zA-Z_]
H			[a-zA-Z0-9_]
ID			{L}+{H}*

%%
%{
	char string_buf[MAX_STR_CONST];
	char *string_buf_ptr;
%}


%{/*
   * Eat up all C-style comments
   */
%}
"/*"					{ printf("BEGIN(comment) "); BEGIN(comment);	}
<comment>([^*])+		{  }
<comment>"*"+[^*/\n]*	{  }
<comment>"*/"			{ printf("BEGIN(INITIAL) "); BEGIN(INITIAL);	}
<comment>"*/"\n			{ printf("BEGIN(INITIAL) \n"); BEGIN(INITIAL);	}
"//".*\n				{ printf("ONE-LINE COMMENT \n"); }

%{/*
   * This is for scripting  to work:
   * TODO: this should only apply when it's on the first line!
   * TODO: this should determine login_prompt var!
   */
%}
^"#!/"({ID}\/)*{ID}\n	{ printf("SCRIPT LINE \n"); }
^[ \t]*\n				{ printf("\nNULL LINE \n"); }
[ \t]+					{  }

prog					{ printf("PROG "); return PROG;		}
alg						{ printf("ALG "); return ALG;		}
func					{ printf("FUNC "); return FUNC;		}
entrada[ \t]+de[ \t]+	{ printf("IN_STREAM "); return IN_STREAM;	}
salida[ \t]+de[ \t]+	{ printf("OUT_STREAM "); return OUT_STREAM; }
entrada[ \t]+y[ \t]+salida[ \t]+de[ \t]+	{ printf("INOUT_STREAM "); return INOUT_STREAM; }
dev						{ printf("DEV "); return DEV;		}

proc					{
							BEGIN(proc);
							printf("PROC "); return PROC;
						}
<proc>;					{ printf("' "); return ';';		}
<proc>fin				{
							BEGIN(INITIAL);
							printf("END "); return END;
						}
ent[ \t]+				{ printf("IN "); return IN;		}
sal[ \t]+				{ printf("OUT "); return OUT;		}
entsal[ \t]+			{ printf("INOUT "); return INOUT;		}
ent\/sal[ \t]+			{ printf("INOUT "); return INOUT;		}

cons					{ printf("CONSTS "); return CONSTS;	}
tipos					{ printf("TYPES "); return TYPES;		}
tabla					{ printf("ARRAY "); return ARRAY;		}
reg						{ printf("REG "); return REG;			}
freg					{ printf("ENDREG "); return ENDREG;	}
var						{ printf("VARS "); return VARS;		}
prin					{ printf("START "); return START;		}
fin						{ printf("END\n"); return END;		}

[ \t]+de[ \t]+			{ printf("OF "); return OF;		}

si						{ printf("IF "); return IF;		}
otras					{ printf("ELSE "); return ELSE;		}
nula					{ printf("IS_NULL "); return IS_NULL;	}
fsi						{ printf("ENDIF "); return ENDIF;		}

mientras				{ printf("WHILE "); return WHILE;		}
fm						{ printf("ENDWHILE "); return ENDWHILE;	}

desde					{ printf("FROM "); return FROM;		}
hasta					{ printf("TO "); return TO;		}
fd						{ printf("ENDFROMTO "); return ENDFROMTO;	}

[+\-*/%^()<>:\[\]\.|=,{}]	{ printf("%c ", yytext[0]); return yytext[0];	}

\n						{ printf("\n"); return yytext[0];	}
;						{ printf("\n "); return '\n';		}
"y"						{ printf("AND_OP "); return AND_OP;	}
"o"						{ printf("OR_OP "); return OR_OP;		}
"no"					{ printf("NOT_OP "); return NOT_OP;	}
":=" 					{ printf("ASSIGN "); return ASSIGN;	}
"<="					{ printf("LE_OP "); return LE_OP;		}
">="					{ printf("GE_OP "); return GE_OP;		}
"<>"					{ printf("NOT_EQ "); return NOT_EQ;	}

verdadero				{
							//yylval.bool_val = true;
							printf("BOOL_VAL "); return BOOL_VAL;
						}
falso					{
							//yylval.bool_val = false;
							printf("BOOL_VAL "); return BOOL_VAL;
						}

{D}+					{
							//yylval.int_val = atoi(yytext);
							printf("INT_VAL "); return INT_VAL;
}

{D}+\.{D}*				{
							//yylval.float_val = atof(yytext);
							printf("FLOAT_VAL "); return FLOAT_VAL;
}

\'[^\']\'				{
							//yylval.char_val = strdup(yytext[1]);
							printf("CHAR_VAL "); return CHAR_VAL;
}
\'\\[0-7]{1,3}\'		{
							int result;
							
							sscanf(yytext + 1, "%o", &result);
							
							if (result > 0xff)
								lexical_error("constant out of range");
							
							//yylval.char_val = result;
							printf("CHAR_VAL "); return CHAR_VAL;
}

\'\\[0-9]+\'			{
							lexical_error("erroneous escape sequence");
}

\'\\n\'					{
							//yylval.char_val = '\n';
							printf("CHAR_VAL "); return CHAR_VAL;
}

\\t						{
							//yylval.char_val = '\t';
							printf("CHAR_VAL "); return CHAR_VAL;
}
\\r						{
							//yylval.char_val = '\r';
							printf("CHAR_VAL "); return CHAR_VAL;
}
\\b						{
							//yylval.char_val = '\b';
							printf("CHAR_VAL "); return CHAR_VAL;
}
\\f						{
							//yylval.char_val = '\f';
							printf("CHAR_VAL "); return CHAR_VAL;
}

{ID}					{
							//yylval.str_val = strdup(yytext);
							printf("ID "); return ID;
}

\"						{
							string_buf_ptr = string_buf;
							BEGIN(str);
}

<str>\"					{
							BEGIN(INITIAL);
							*string_buf_ptr = '\0';
							//yylval.str_val = string_buf_ptr;
							printf("STR_VAL "); return STR_VAL;
}

<str>\n					{
							lexical_error("constant string without an end");
}

<str>\\[0-7]{1,3}		{
							int result;
							
							sscanf(yytext + 1, "%o", &result);
							
							if (result > 0xff)
								lexical_error("constant out of range");
							
							*string_buf_ptr++ = result;
}

<str>\\[0-9]+			{
							lexical_error("erroneous escape sequence");
}

<str>\\n				{ *string_buf_ptr++ = '\n'; }
<str>\\t				{ *string_buf_ptr++ = '\t'; }
<str>\\r				{ *string_buf_ptr++ = '\r'; }
<str>\\b				{ *string_buf_ptr++ = '\b'; }
<str>\\f				{ *string_buf_ptr++ = '\f'; }

<str>\\(.|\n)			{ *string_buf_ptr++ = yytext[1]; }

<str>[^\\\n\"]+			{
							char *yptr = yytext;
							
							while (*yptr)
								*string_buf_ptr++ = *yptr++;
}

%{/*
   * Everything else is erroneous
   */
%}
.						{ lexical_error("unknown error");	}

%%
