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
	int int_val;
	bool bool_var;
	float float_val;
	char char_val;
	char *str_val;
	node *no;
	node_list *nl;
}

%token PROG ALG FUNC IN_STREAM OUT_STREAM INOUT_STREAM DEV PROC END IN OUT INOUT CONSTS TYPES VARS START END OF
%token PRINT READ IF ELSE IS_NULL ENDIF WHILE ENDWHILE FROM TO ENDFROMTO ID IS_NULL

%token <int_val>	INT_VAL
%token <bool_var>	BOOL_VAL
%token <float_val>	FLOAT_VAL
%token <char_val>	CHAR_VAL
%token <str_val>	STR_VAL

%type <no>			program prog_header algorithm function procedure alg_header func_header
%type <no>			proc_header interface_block in_var_dcl out_var_dcl inout_var_dcl 
%type <no>			declarations_block consts_block const_dcl types_block vars_block 
%type <no>			sentence_list_block sentence if_statement output_statement input_statement
%type <no>			while_loop fromto_loop function_call procedure_call expr expr_bool
%type <nl>			library proc_arg_list in_arg_list out_arg_list inout_arg_list id_list types_dcl
%type <nl>			str_list vars_dcl sentence_list elif_statement_list assign_statement 
%type <nl>			mult_assign_statement expr_list

%start program

%left '-' '+'
%left '*'  '/' '%'
%right '^'
%right ASSIGN
%right '=' GE_OP LE_OP '<' '>'
%left AND_OP OR_OP NOT_OP

%nonassoc NEG

%%

program:
	prog_header
	declarations_block
	sentence_list_block
	library
		{ $$ = decl_prog($1, $2, $3, $4); }
;

prog_header:
	PROG ID '\n'
		{ $$ = decl_prog_header($2); }
;

library: /* empty */
	| library algorithm
		{ $$ == library_pair($1, $2); }
	| library function
		{ $$ == library_pair($1, $2); }
	| library procedure
		{ $$ == library_pair($1, $2); }
;

algorithm:
	alg_header
	interface_block
	declarations_block
	sentence_list_block
		{ $$ = decl_alg($1, $2, $3, $4); }
;

function:
	func_header
	declarations_block
	sentence_list_block
		{ $$ = decl_func($1, $2, $3); }
;

procedure:
	proc_header
	declarations_block
	sentence_list_block
		{ $$ = decl_proc($1, $2, $3); }
;

alg_header:
	ALG ID '\n'
		{ $$ = decl_alg_header($2); }
;

func_header:
	FUNC ID '(' in_arg_list ')'  DEV '(' out_arg_list ')' '\n'
		{ $$ = decl_func_header($2, $4, $8); }
;

proc_header:
	PROC ID '(' proc_arg_list ')' '\n'
		{ $$ = decl_proc_header($2, $4); }
;

interface_block: /* empty */
	| IN in_arg_list '\n'
	interface_block
		{ $$ = interface_block_in_pair($2, $4); }
	| OUT out_arg_list '\n'
	interface_block
		{ $$ = interface_block_out_pair($2, $4); }
;

proc_arg_list: /* empty */
	| proc_arg_list
	IN in_arg_list ';'  
		{ $$ = proc_arg_list_in_pair($1, $3); }
	|proc_arg_list
	OUT out_arg_list ';' 
		{ $$ = proc_arg_list_out_pair($1, $3); }
	| proc_arg_list
	INOUT inout_arg_list ';' 
		{ $$ = proc_arg_list_inout_pair($1, $3); }
;

in_arg_list : /* empty */
	| in_arg_list ',' in_var_dcl
		{ $$ = in_arg_list_pair($1, $3); }
	| in_var_dcl
		{ $$ = in_arg_list_node($1); }
;

out_arg_list : /* empty */
	| out_arg_list ',' out_var_dcl
		{ $$ = out_arg_list_pair($1, $3); }
	| out_var_dcl
		{ $$ = out_arg_list_node($1); }
;

inout_arg_list : /* empty */
	| inout_arg_list ',' inout_var_dcl
		{ $$ = inout_arg_list_pair($1, $3); }
	| inout_var_dcl
		{ $$ = inout_arg_list_node($1); }
;

in_var_dcl:
	id_list   ':' ID
		{ $$ = dcl_in_var($1, $3); }
	| id_list ':' ID IN_STREAM ID
		{ $$ = dcl_in_var($1, $3, $5); }
	| id_list  ':' ARRAY array_dimensions OF ID
		{ $$ = dcl_in_var($1, $3, $4, $6); }
;

out_var_dcl:
	id_list   ':' ID
		{ $$ = dcl_out_var($1, $3); }
	| id_list ':' ID OUT_STREAM ID
		{ $$ = dcl_out_var($1, $3, $5); }
	| id_list ':' ARRAY array_dimensions OF ID
		{ $$ = dcl_out_var($1, $3, $4, $6); }
;

inout_var_dcl:
	id_list   ':' ID
		{ $$ = dcl_inout_var($1, $3); }
	| id_list ':' ID INOUT_STREAM ID
		{ $$ = dcl_inout_var($1, $3, $5); }
	| id_list ':' ARRAY array_dimensions OF ID
		{ $$ = dcl_inout_var($1, $3, $4, $6); }
;

id_list:
	id_list ',' ID
		{ $$ = id_list_pair($1, $3); }
	| ID
		{ $$ = id_list_node($1); }
;

declarations_block:
	consts_block
	types_block
	vars_block
		{ $$ = declarations_block_node($1, $2, $3); }
;

consts_block: /* empty */
	| CONSTS '\n'
		const_dcl_list
		{ $$ = consts_block_node($3); }
;

const_dcl_list: /* empty */
	| const_dcl_list
	id_list ':' BOOL_VAL '\n'
		{ $$ = dcl_bool_const($1, $2, $4); }
	| const_dcl_list
	id_list ':' INT_VAL '\n'
		{ $$ = dcl_int_const($1, $2, $4); }
	| const_dcl_list
	id_list ':' FLOAT_VAL '\n'
		{ $$ = dcl_float_const($1, $2, $4); }
	| const_dcl_list
	id_list ':' CHAR_VAL '\n'
		{ $$ = dcl_char_const($1, $2, $4); }
	| const_dcl_list
	id_list ':' STR_VAL '\n'
		{ $$ = dcl_str_const($1, $2, $4); }
;

types_block: /* empty */
	| TYPES '\n'
		type_dcl
		{ $$ = types_block_node($3); }
;
types_dcl: /* empty */
	| types_dcl
	id_list ':' '(' str_list ')' '\n'
		{ $$ = types_dcl_pair($1, $2, $5); }
	| types_dcl
	id_list ':' ID
		{ $$ = types_dcl_node($1, $2, $4); }
	| types_dcl
	id_list ':' ID IN_STREAM ID
		{ $$ = types_dcl_node($1, $2, $4, $6); }
	| types_dcl
	id_list ':' ARRAY array_dimensions OF ID
		{ $$ = types_dcl_node($1, $2, $4, $5, $7); }
;

str_list: /* empty */
	| str_list ',' ID
		{ $$ = str_list_pair($1, $3); }
;

vars_block: /* empty */
	| VARS '\n'
		vars_dcl
		{ $$ = vars_block_node($3); }
;

vars_dcl: /* empty */
	| var_dcl
	id_list ':' ID '\n'
		{ $$ = dcl_var_pair($1, $2, $4); }
;

sentence_list_block:
	START '\n'
		sentence_list
	END '\n'
;

sentence_list: /* empty */
	| sentence_list sentence
	{ $$ = sentence_list_pair($1, $2); }
;

sentence:
	if_statement
		{ $$ = $1; }
	| assign_statement
		{ $$ = $1; }
	| mult_assign
		{ $$ = $1; }
	| input_statement
		{ $$ = $1; }
	| output_statement
		{ $$ = $1; }
	| while_loop
		{ $$ = $1; }
	| fromto_loop
		{ $$ = $1; }
	| function_call '\n'
		{ $$ = $1; }
	| procedure_call
		{ $$ = $1; }
;

if_statement:
	IF expr_bool '\n'
		sentence_list
	elif_statement_list
	ELSE '\n' 
		sentence_list
	ENDIF '\n'
		{ $$ = if_statement_node($2, $4, $5, $8); }
;

elif_statement_list: /* empty */
	| '|' expr_bool '\n'
		sentence_list
	elif_statement_list
		{ $$ = elif_statement_list_pair($2, $4, $5); }
;

assign_statement:
	ID ASSIGN assign_statement
		{ $$ = assign_statement_pair($1, $3); }
	| ID ASSIGN expr '\n'
		{ $$ = assign_statement_node($1, $3); }
;


mult_assign_statement:
	| id_list ASSIGN expr_list '\n'
		{ $$ = mult_assign_statement_node($1, $3); }
;

output_statement:
	PRINT expr_list '\n'
		{ $$ = output_statement_node($2); }
;

input_statement:
	READ expr '\n'
		{ $$ = input_statement_node($2); }
;

while_loop:
	WHILE expr_bool '\n'
		sentence_list
	ENDWHILE '\n'
		{ $$ = while_loop_node($2, $4); }
;

fromto_loop:
	FROM expr TO expr_bool '\n'
		sentence_list
	ENDFROMTO '\n'
		{ $$ = fromto_loop_node($2, $4, $6); }
;

function_call:
	ID '(' arg_list ')'
		{ $$ = function_call_node($1, $3); }
;


procedure_call:
	ID '(' arg_list ')' '\n'
		{ $$ = procedure_call_node($1, $3); }
;

expr:
	INT_VAL
		{ $$ = expr_int_node($1); }
	| BOOL_VAL
		{ $$ = expr_bool_node($1); }
	| FLOAT_VAL
		{ $$ = expr_float_node($1); }
	| ID
		{ $$ = expr_get_id_node($1); }
	| expr '+' expr
		{ $$ = expr_op_node('+', $1, $3); }
	| expr '-' expr
		{ $$ = expr_op_node('-', $1, $3); }
	| expr '*' expr
		{ $$ = expr_op_node('*', $1, $3); }
	| expr '/' expr
		{ $$ = expr_op_node('/', $1, $3); }
	| expr '%' expr
		{ $$ = expr_op_node('%', $1, $3); }
	| expr '^' expr
		{ $$ = expr_op_node('^', $1, $3); }
	| '-' expr %prec NEG
		{ $$ = expr_op_node('-', $1); }
	| '(' expr ')'
		{ $$ = $2; }
	| function_call
		{ $$ = check_type_node($1); }
;

expr_list:
	| expr_list ',' expr
		{ $$ = expr_list_pair($1, $3); }
;

expr_bool:
	BOOL_VAL
		{ $$ = expr_bool_node($1); }
	| ID
		{ $$ = expr_bool_get_id_node($1); }
	| NOT_OP expr_bool
		{ $$ = expr_bool_op_node("NOT", $1); }
	| expr_bool AND_OP expr_bool
		{ $$ = expr_bool_op_node("AND", $1, $3); }
	| expr_bool OR_OP expr_bool
		{ $$ = expr_bool_op_node("OR", $1, $3); }
	| expr '=' expr
		{ $$ = expr_bool_op_node("EQ", $1, $3); }
	| expr '<' expr
		{ $$ = expr_bool_op_node("L", $1, $3); }
	| expr '>' expr
		{ $$ = expr_bool_op_node("G", $1, $3); }
	| expr LE_OP expr
		{ $$ = expr_bool_op_node("LE", $1, $3); }
	| expr GE_OP expr
		{ $$ = expr_bool_op_node("GE", $1, $3); }
	| expr NOT_EQ expr
		{ $$ = expr_bool_op_node("NOT_EQ", $1, $3); }
	'(' expr_bool ')'
		{ $$ = $2; }
	| function_call
		{ $$ = expr_bool_check_node($1); }
;

%%

int main(int argc, char *argv[])
{
	extern FILE *yyin;
	
	init_table();
	
	if (argc > 1) {
		if (!(yyin = fopen(argv[1], "r"))) {
			fprintf(stderr, "\nUnable to open source file: %s\n", argv[1]);
			exit(1);
		} else
			user_prompt=F;
	} else
		user_prompt=F;
	
	prompt();
	yyparse();
	
	return 0;
}
