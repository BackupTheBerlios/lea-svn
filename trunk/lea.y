%{
/**
 * \file lea.y
 * \brief Lea gramatical parser
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
	#include <stdio.h>
	#include <stdlib.h>
	#include "lea.h"
	
	#define yyerror(s) printf("%s\n", s)
%}

%union {
	int integer_val;
	bool boolean_var;
	float float_val;
	char char_val;
	char *string_val;
	node *node_ptr;
	
}

%token <int_val>		INT_VAL
%token <bool_var>		BOOL_VAL
%token <float_val>		FLOAT_VAL
%token <char_val>		CHAR_VAL
%token <str_val>		STR_VAL
%token <node_ptr>		var_node

%start input

/*

(((-5) + 6) - (56^(5*8)))
*/

%left '-' '+'
%left '*'  '/' '%'
%right '^'
%right ASSIGN
%right '=' GE_OP LE_OP
%left AND_OP OR_OP NOT_OP

%nonassoc NEG

%%

input: /* empty */
	| input line;

line: '\n'					{ prompt();			}
	| int_exp '\n'			{
		printf("\t%d\n", $1);
		prompt();
	}
	| error '\n'			{ yyerrok;	 		}

int_exp: INT				{ $$ = $1;			}
	| INT_VAR				{ $$ = get_sym($1);	}
	| INT_VAR EQ int_exp	{ 
		$$ = $3;
		set_sym($1, $3);
	}
	| int_exp '+' int_exp	{
		$$ = $1 + $3;
	}
	| int_exp '-' int_exp	{ $$ = $1 - $3;		}
	| int_exp '*' int_exp	{ $$ = $1 * $3;		}
	| int_exp '/' int_exp	{ $$ = $1 / $3;		}
	| '(' int_exp ')'		{ $$ = $2;			}
	| '-' int_exp %prec NEG {$$ = -$2;			}

%%

int main(int argc, char *argv[])
{
	extern FILE *yyin;
	
	init_table();
	
	if (argc>1) {
		if (!(yyin = fopen(argv[1], "r"))) {
			fprintf(stderr, "\nUnable to open source file: %s\n", argv[1]);
			exit(1);
		} else
			user_prompt=F;
	} else
		user_prompt=T;
	
	prompt();
	yyparse();
	
	return 0;
}
