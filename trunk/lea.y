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
    node *no;
    node_block *nb;
    node_list *nl;
	
}

%token <int_val>	INT_VAL
%token <bool_var>	BOOL_VAL
%token <float_val>	FLOAT_VAL
%token <char_val>	CHAR_VAL
%token <str_val>	STR_VAL

%type <no>			algorithm
%type <nb>			
%type <nl>			

%start program

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

program:
	prog_header
	declarations_block
	sentences_block
	library
		{ $$ = declare_prog($1, $2, $3, $4); }
;

library: /* empty */
	| library algorithm
		{ $$ == add_alg($2);}
	| library function
		{ $$ == add_func($2); }
	| library procedure
		{ $$ == add_proc($2); }
;

algorithm:
	alg_header
	interface_block
	declarations_block
	sentences_block
		{ $$ = declare_alg($1, $2, $3, $4); }
;

function:
	func_header
	declarations_block
	sentences_block
		{ $$ = declare_func($1, $2, $3, $4); }
;

procedure:
	proc_header
	declarations_block
	sentences_block
		{ $$ = declare_proc($1, $2, $3, $4); }
;

alg_header:
	ALG ID '\n'
		{ $$ = ID; }
;

func_header:
	FUNC ID '(' linked_in_args ')'  DEV '(' linked_out_args ')' '\n'
		{ $$ = declare_func_header($2, $4, $8); }
;

proc_header:
	PROC ID '(' proc_arg_list ')' '\n'
		{ $$ = declare_proc_header($2, $4); }
;

interface_block: /* empty */
	| IN linked_in_args '\n' interface_block
		{ $$ = add_interface_linked_arg_node($2, $3); }
	| OUT linked_out_args '\n' interface_block
		{ $$ = add_interface_linked_arg_node($2, $3); }
;

proc_arg_list: /* empty */
	| IN linked_in_args ';' proc_arg_list 
		{ $$ = add_proc_linked_arg_node($2, $3); }
	| OUT linked_out_args ';' proc_arg_list
		{ $$ = add_proc_linked_arg_node($2, $3); }
	| INOUT linked_inout_args ';' proc_arg_list
		{ $$ = add_proc_linked_arg_node($2, $3); }
;

linked_in_args : NULL
	| in_var_dcl ',' linked_in_args
		{ $$ = add_func_linked_in_arg_node($1, $2); }
	| in_var_dcl
		{ $$ = add_func_linked_in_arg_node($1); }
;

linked_out_args : NULL
	| out_var_dcl ',' linked_out_args
		{ $$ = add_func_linked_out_arg_node($1, $2); }
	| out_var_dcl ','
		{ $$ = add_func_linked_out_arg_node($1); }
;

linked_inout_args : /* empty */
	| inout_var_dcl ',' linked_inout_args
		{ $$ = add_linked_inout_arg_node($1, $2); }
	| inout_var_dcl
		{ $$ = add_linked_inout_arg_node($1); }
;

in_var_dcl:
	ID   ':' ID
		{ $$ = declare_var($1, $3); }
	| ID ':' ID IN_STREAM ID
		{ $$ = declare_var($1, $3, $5); }
	| ID ':' ARRAY array_dimensions OF ID
		{ $$ = declare_var($1, $3, $4, $6); }
;

out_var_dcl:
	ID   ':' ID
		{ $$ = declare_var($1, $3); }
	| ID ':' ID OUT_STREAM ID
		{ $$ = declare_var($1, $3, $5); }
	| ID ':' ARRAY array_dimensions OF ID
		{ $$ = declare_var($1, $3, $4, $6); }
;

inout_var_dcl:
	ID   ':' ID
		{ $$ = declare_var($1, $3); }
	| ID ':' ID INOUT_STREAM ID
		{ $$ = declare_var($1, $3, $5); }
	| ID ':' ARRAY array_dimensions OF ID
		{ $$ = declare_var($1, $3, $4, $6); }
;
















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
