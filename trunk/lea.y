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
	ids   ':' ID
		{ $$ = declare_var($1, $3); }
	| ids ':' ID IN_STREAM ID
		{ $$ = declare_var($1, $3, $5); }
	| ids  ':' ARRAY array_dimensions OF ID
		{ $$ = declare_var($1, $3, $4, $6); }
;

out_var_dcl:
	ids   ':' ID
		{ $$ = declare_var($1, $3); }
	| ids ':' ID OUT_STREAM ID
		{ $$ = declare_var($1, $3, $5); }
	| ids ':' ARRAY array_dimensions OF ID
		{ $$ = declare_var($1, $3, $4, $6); }
;

inout_var_dcl:
	ids   ':' ID
		{ $$ = declare_var($1, $3); }
	| ids ':' ID INOUT_STREAM ID
		{ $$ = declare_var($1, $3, $5); }
	| ids ':' ARRAY array_dimensions OF ID
		{ $$ = declare_var($1, $3, $4, $6); }
;

ids:
	ID ',' ids
		{ $$ = add_linked_id_node($1, $3); }
	ID
		{ $$ = add_linked_id_node($1); }
;

declarations_block:
	consts_block
	types_block
	vars_block
		{ $$ = add_declarations_block($1, $2, $3); }
;

consts_block: /* empty */
	| CONSTS '\n'
		const_dcl
		{ $$ = add_consts_block($3); }
;

const_dcl:
	ids   ':' BOOL_VAL '\n'
		{ $$ = declare_const($1, $3); }
	| ids ':' FLOAT_VAL '\n'
		{ $$ = declare_const($1, $3); }
	| ids ':' CHAR_VAL '\n'
		{ $$ = declare_const($1, $3); }
	| ids ':' STR_VAL '\n'
		{ $$ = declare_const($1, $3); }
;

types_block: /* empty */
	| TYPES '\n'
		type_dcl
		{ $$ = add_types_block($3); }
;
types_dcl: /* empty */
	| ids ':' '(' strs ')' '\n'
	types_dcl
		{ $$ = add_linked_type_node($1, $4); }
;

strs:
	ID ',' strs
		{ $$ = add_linked_str_node($1, $3); }
;

vars_block: /* empty */
	| VARS '\n'
		vars_dcl
		{ $$ = add_vars_block($1, $3); }
;

vars_dcl: /* empty */
	| ids ':' ID '\n'
	var_dcl
		{ $$ = declare_var($1, $3); }
;

sentences_block: /* empty */
	START '\n'
		sentences
	END '\n'
;

sentences: /* empty */
	| sentence sentences
;

sentence:
	| conditional_statement
	| assign_statement
	| input_statement
	| output_statement
	| while_loop
	| fromto_loop
	| function_call
	| procedure_call
;

if_statement:
	IF expr_bool
		sentences
	elif_statements
	ELSE
		expr
	ENDIF
		{ $$ = if_node($2, $3, $4, $6); }
;

elif_statements:
	'|' expr_bool
		sentences
		{ $$ = elif_node($2, $3); }
	'|' expr_bool
		sentences
	elif_statements
		{ $$ = elif_node($2, $3, $4); }
;

assign_statement:
	| ID ASSIGN expr
		{ $$ = assign_node($1, $3); }
;

output_statement:
	PRINT expr
		{ $$ = print($2); }
;

input_statement:
	READ expr
		{ $$ = read($2); }
;

while_loop:
	WHILE expr_bool
		sentences
	ENDWHILE
		{ $$ = while_node($2, $3); }
;

fromto_loop:
	FROM expr TO expr_bool
		sentences
	ENDFROMTO
		{ $$ = fromto_node($2, $4, $5); }
;

function_call:
	ID '(' arg_list ')' '\n'
		{ $$ = func_call($1, $3); }
;


procedure_call:
	ID '(' arg_list ')' '\n'
		{ $$ = proc_call($1, $3); }
;

expr:
	INT_VAL
		{ $$ = integer_val($1); }
	| BOOL_VAL
		{ $$ = boolean_val($1); }
	| FLOAT_VAL
		{ $$ = float_val($1); }
	| CHAR_VAL
		{ $$ = char_val($1); }
	| STR_VAL
		{ $$ = string_val($1); }
	| ID
		{ $$ = get_identifier($1); }
	| expr '+' expr
		{ $$ = binary_node('+',$1, $3); }
	| expr '-' expr
		{ $$ = binary_node('-', $1, $3); }
	| expr '*' expr
		{ $$ = binary_node('*', $1, $3); }
	| expr '/' expr
		{ $$ = binary_node('/', $1, $3); }
	| expr '%' expr
		{ $$ = binary_node('%', $1, $3); }
	| expr '^' expr
		{ $$ = binary_node('^', $1, $3); }
	| '-' expr %prec NEG
		{ $$ = binary_node('-', $1); }
	| '(' expr ')'
		{ $$ = $1; }
;

expr_bool:
	BOOL_VAL
		{ $$ = boolean_val($1); }
	| ID
		{ $$ = get_identifier($1); }
	| NOT_OP expr_bool
		{ $$ = bool_node('!', $1); }
	| expr_bool AND_OP expr_bool
		{ $$ = bool_node('^', $1, $3); }
	| expr_bool OR_OP expr_bool
		{ $$ = bool_node('´', $1, $3); }
	| expr_bool '=' expr_bool
		{ $$ = bool_node('=', $1, $3); }
	| expr_bool '<' expr_bool
		{ $$ = bool_node('<', $1, $3); }
	| expr_bool '>' expr_bool
		{ $$ = bool_node('>', $1, $3); }
	| expr_bool LE_OP expr_bool
		{ $$ = bool_node('{', $1, $3); }
	| expr_bool GE_OP expr_bool
		{ $$ = bool_node('}', $1, $3); }
	| expr_bool NOT_EQ expr_bool
		{ $$ = bool_node('¨', $1, $3); }
	'(' expr_bool ')'
;

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
