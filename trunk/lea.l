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
 * along with nbsmtp; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 * 
 * See COPYING for details.
 */
	#include <stdlib.h>
	#include <string.h>
	#include "y.tab.h"
	#include "lea.lex.h"
	#define MAX_STR_CONST 1024
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
   * This is for scripting  to work:
   * TODO: this should only apply when it's on the first line!
   * TODO: this should determine login_prompt var!
   */
%}
^"#!/"({ID}\/)*{ID}$	{  }
[ \t]+					{  }

%{/*
   * Eat up all C-style comments
   */
%}
"/*"					{ BEGIN(comment);	}
<comment>([^*])+		{ }
<comment>"*"+[^*/\n]*	{ }
<comment>"*"+"/"		{ BEGIN(INITIAL);	}
"//".*$					{ }

prog					{ return PROG;		}
alg						{ return ALG;		}
func					{ return FUNC;		}
entrada[ \t]+de[ \t]+	{ return IN_STREAM;	}
salida[ \t]+de[ \t]+	{ return OUT_STREAM; }
entrada[ \t]+y[ \t]+salida[ \t]+de[ \t]+	{ return INOUT_STREAM; }
dev						{ return DEV;		}

proc					{
							BEGIN(proc);
							return PROC;
						}
<proc>;					{ return ';';		}
<proc>fin				{
							BEGIN(INITIAL);
							return END;
						}
ent[ \t]+				{ return IN;		}
sal[ \t]+				{ return OUT;		}
entsal[ \t]+			{ return INOUT;		}

cons					{ return CONSTS;	}
tipos					{ return TYPES;		}
var						{ return VARS;		}
prin					{ return START;		}
fin						{ return END;		}

[ \t]+de[ \t]+			{ return OF;		}

escribir				{ return PRINT;		}
leer					{ return READ;		}

si						{ return IF;		}
otras					{ return ELSE;		}
nula					{ return IS_NULL;	}
fsi						{ return ENDIF;		}

mientras				{ return WHILE;		}
fm						{ return ENDWHILE;	}

desde					{ return FROM;		}
hasta					{ return TO;		}
fd						{ return ENDFROMTO;	}

[+\-*/%^()<>:\[\]|=,\n]	{ return yytext[0];	}
;						{ return '\n';		}
"y"						{ return AND_OP;	}
"o"						{ return OR_OP;		}
"no"					{ return NOT_OP;	}
":=" 					{ return ASSIGN;	}
"<="					{ return LE_OP;		}
">="					{ return GE_OP;		}
"<>"					{ return NOT_EQ;	}

verdadero				{
							yylval.bool_val = true;
							return BOOL_VAL;
						}
falso					{
							yylval.bool_val = false;
							return BOOL_VAL;
						}

{D}+					{
							yylval.int_val = atoi(yytext);
							return INT_VAL;
}

{D}+.{D}*				{
							yylval.float_val = atof(yytext);
							return FLOAT_VAL;
}

\'[^\']\'				{
							yylval.char_val = strdup(yytext[1]);
							return CHAR_VAL;
}
\'\\[0-7]{1,3}\'		{
							int result;
							
							sscanf(yytext + 1, "%o", &result);
							
							if (result > 0xff)
								lexical_error("constant out of range");
							
							yylval.char_val = result;
							return CHAR_VAL;
}

\'\\[0-9]+\'			{
							lexical_error("erroneous escape sequence");
}

\'\\n\'					{
							yylval.char_val = '\n';
							return CHAR_VAL;
}

\\t						{
							yylval.char_val = '\t';
							return CHAR_VAL;
}
\\r						{
							yylval.char_val = '\r';
							return CHAR_VAL;
}
\\b						{
							yylval.char_val = '\b';
							return CHAR_VAL;
}
\\f						{
							yylval.char_val = '\f';
							return CHAR_VAL;
}

{ID}					{
							yylval.str_val = strdup(yytext);
							return ID;
}

\"						{
							string_buf_ptr = string_buf;
							BEGIN(str);
}

<str>\"					{
							BEGIN(INITIAL);
							*string_buf_ptr = '\0';
							yylval.str_val = string_buf_ptr;
							return STR_VAL;
}

<str>\n					{
							lexical_error("constant string without an end");
}

<str>\\[0-7]{1,3}		{
							int result;
							
							sscanf(yytext + 1, "%o", &result);
							
							if (result > 0xff)
								lexical_error("constant out of range");
							
							*string_buf_ptr++ = resultad;
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
