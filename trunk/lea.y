%{
/**
 * \file lea.y
 * \brief Lea gramatical parser
 *
 * \author Eduardo Robles Elvira <edulix@iespana.es>
 * \author Felix Robles Elvira <redeadlink@hotmail.com>
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
 * along with Lea; if not, write to the Free Software
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
}

%token PROG ALG FUNC IN_STREAM OUT_STREAM INOUT_STREAM DEV PROC END IN OUT INOUT CONSTS TYPES VARS START OF
%token IF ELSE IS_NULL ENDIF WHILE ENDWHILE FROM TO ENDFROMTO ID IS_NULL ARRAY REG ENDREG

%token <int_val>	INT_VAL
%token <bool_var>	BOOL_VAL
%token <float_val>	FLOAT_VAL
%token <char_val>	CHAR_VAL
%token <str_val>	STR_VAL

%type <no>			program prog_header algorithm function procedure alg_header func_header 
%type <no>			proc_header interface_block in_var_dcl out_var_dcl inout_var_dcl 
%type <no>			declarations_block consts_block const_dcl_list types_block vars_block 
%type <no>			sentence_list_block sentence if_statement output_input_statement register
%type <no>			while_loop fromto_assign_statement fromto_loop function_call procedure_call expr expr_bool
%type <no>			library proc_arg proc_arg_list in_arg_list out_arg_list inout_arg_list id_list
%type <no>			array_dimensions int_val_list types_dcl str_list vars_dcl sentence_list elif_statement
%type <no>			elif_statement_list assign_statement mult_assign_statement expr_list mult_assign mult_assign_list

%start program

%left '-' '+'
%left '*'  '/' '%'
%right '^'
%right ASSIGN
%right '=' GE_OP LE_OP '<' '>' NOT_EQ
%left AND_OP OR_OP NOT_OP

%nonassoc NEG

%%

program:
	prog_header
	declarations_block
	sentence_list_block
	library
		{ $$ = program_node($1, $2, $3, $4); }
;

prog_header:
	PROG ID '\n'
		{ $$ = prog_header_node($2); }
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
		{ $$ = algorithm_node($1, $2, $3, $4); }
;

function:
	func_header
	declarations_block
	sentence_list_block
		{ $$ = function_node($1, $2, $3); }
;

procedure:
	proc_header
	declarations_block
	sentence_list_block
		{ $$ = procedure_node($1, $2, $3); }
;

alg_header:
	ALG ID '\n'
		{ $$ = alg_header_node($2); }
;

func_header:
	FUNC ID '(' in_arg_list ')'  DEV '(' out_var_dcl ')' '\n'
		{ $$ = func_header_node($2, $4, $8); }
;

proc_header:
	PROC ID '(' proc_arg_list ')' '\n'
		{ $$ = proc_header_node($2, $4); }
;

interface_block: /* empty */
	| IN in_arg_list '\n'
	interface_block
		{ $$ = interface_block_pair($2, $4); }
	| OUT out_arg_list '\n'
	interface_block
		{ $$ = interface_block_pair($2, $4); }
;

proc_arg: /* empty */
	| IN in_arg_list 
		{ $$ = proc_arg_list_pair($1, $3); }
	| OUT out_arg_list
		{ $$ = proc_arg_list_pair($1, $3); }
	| INOUT inout_arg_list
		{ $$ = proc_arg_list_pair($1, $3); }
;

proc_arg_list: /* empty */
	proc_arg_list ';' proc_arg
		{ $$ = proc_arg_list_pair($1, $3); }
	| proc_arg
		{ $$ = proc_arg_list_node($1); }
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
		{ $$ = in_var_dcl_node('v', $1, $3); }
	| id_list ':' ID OF ID
		{ $$ = in_var_dcl_node('f', $1, $3, $4); }
	| id_list ':' ID OF IN_STREAM ID
		{ $$ = in_var_dcl_node('s', $1, $3, $5); }
	| id_list  ':' ARRAY array_dimensions OF ID
		{ $$ = in_var_dcl_node('a', $1, $3, $4, $6); }
;

out_var_dcl:
	id_list   ':' ID
		{ $$ = out_var_dcl_node('v', $1, $3); }
	| id_list ':' ID OF ID
		{ $$ = out_var_dcl_node('f', $1, $3, $4); }
	| id_list ':' ID OF OUT_STREAM ID
		{ $$ = out_var_dcl_node('s', $1, $3, $5); }
	| id_list ':' ARRAY array_dimensions OF 
		{ $$ = out_var_dcl_node('a', $1, $3, $4, $6); }
;

inout_var_dcl:
	id_list   ':' ID
		{ $$ = inout_var_dcl_node('v', $1, $3); }
	| id_list ':' ID OF ID
		{ $$ = inout_var_dcl_node('f', $1, $3, $4); }
	| id_list ':' ID OF INOUT_STREAM ID
		{ $$ = inout_var_dcl_node('s', $1, $3, $4, $6); }
	| id_list ':' ARRAY array_dimensions OF ID
		{ $$ = inout_var_dcl_node('a', $1, $3, $4, $6); }
;

id_list:
	id_list ',' ID
		{ $$ = id_list_pair($1, $3); }
	| ID
		{ $$ = id_list_node($1); }
;

array_dimensions:
	'[' int_val_list ']'
		{  $$ = $2; }
;

int_val_list:
	int_val_list ',' INT_VAL
		{ $$ = int_val_list_pair($1, $3); }
	| INT_VAL
		{ $$ = int_val_list_node($1); }
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
		{ $$ = const_dcl_list_pair('b', $1, $2, $4); }
	| const_dcl_list
	id_list ':' INT_VAL '\n'
		{ $$ = const_dcl_list_pair('i', $1, $2, $4); }
	| const_dcl_list
	id_list ':' FLOAT_VAL '\n'
		{ $$ = const_dcl_list_pair('f', $1, $2, $4); }
	| const_dcl_list
	id_list ':' CHAR_VAL '\n'
		{ $$ = const_dcl_list_pair('c', $1, $2, $4); }
	| const_dcl_list
	id_list ':' STR_VAL '\n'
		{ $$ = const_dcl_list_pair('s', $1, $2, $4); }
	| const_dcl_list
	id_list ':' register
		{ $$ = const_dcl_list_pair('r', $1, $2, $4); }
;

types_block: /* empty */
	| TYPES '\n'
		types_dcl_list
		{ $$ = types_block_node($3); }
;
types_dcl_list: /* empty */
	| types_dcl_list
	id_list ':' '(' str_list ')' '\n'
		{ $$ = types_dcl_list_pair('e', $1, $2, $5); }
	| types_dcl_list
	id_list ':' ID '\n'
		{ $$ = types_dcl_list_pair('v', $1, $2, $4); }
	| types_dcl_list
	id_list ':' ID OF ID '\n' //note that this can be either a file or a stream/"flux"
		{ $$ = types_dcl_list_pair('f', $1, $2, $4, $6); }
	| types_dcl_list
	id_list ':' ARRAY array_dimensions OF ID '\n'
		{ $$ = types_dcl_list_pair('a', $1, $2, $4, $5, $7); }
	| types_dcl_list
	id_list ':' register
		{ $$ = types_dcl_list_pair('r', $1, $2, $4); }
;

str_list:
	str_list ',' ID
		{ $$ = str_list_pair($1, $3); }
	| ID
		{ $$ = str_list_node($1); }
;

vars_block: /* empty */
	| VARS '\n'
		vars_dcl
		{ $$ = vars_block_node($3); }
;

vars_dcl: /* empty */
	| vars_dcl
	id_list ':' ID '\n'
		{ $$ = vars_dcl_pair('v', $1, $2, $4); }
	| vars_dcl
	id_list ':' ID OF ID '\n' //note that this can be either a file or a stream/"flux"
		{ $$ = vars_dcl_pair('f', $1, $2, $4, $6); }
	| vars_dcl
	id_list ':' ARRAY array_dimensions OF ID '\n'
		{ $$ = vars_dcl_pair('a', $1, $2, $4, $5, $7); }
	| vars_dcl
	id_list ':' register
		{ $$ = vars_dcl_pair('r', $1, $2, $4); }
;

register:
	REG '\n'
	vars_dcl
	ENDREG '\n'
		{ $$ = register_node($3); }
;

sentence_list_block:
	START '\n'
		sentence_list
	END '\n'
		{ $$ = sentence_list_block_node($3); }
	| START '\n'
		sentence_list
	END
		{ $$ = sentence_list_block_node($3); }
;

sentence_list: /* empty */
	| sentence_list sentence
		{ $$ = sentence_list_pair($1, $2); }
	| IS_NULL '\n'
		{ $$ = sentence_list_node(); }
;

sentence:
	if_statement
		{ $$ = sentence_node('i', $1); }
	| assign_statement '\n'
		{ $$ = sentence_node('a', $1); }
	| mult_assign_statement
		{ $$ = sentence_node('m', $1); }
	| output_input_statement
		{ $$ = sentence_node('o', $1); }
	| while_loop
		{ $$ = sentence_node('w', $1); }
	| fromto_loop
		{ $$ = sentence_node('t', $1); }
	| function_call '\n'
		{ $$ = sentence_node('f', $1); }
	| procedure_call
		{ $$ = sentence_node('p', $1); }
;

if_statement:
	IF expr_bool ':' '\n'
		sentence_list
	elif_statement_list
	'|' ELSE ':' '\n' 
		sentence_list
	ENDIF '\n'
		{ $$ = if_statement_node($2, $5, $6, $11); }
	| IF expr_bool ':' '\n'
		sentence_list
	'|' ELSE ':' '\n' 
		sentence_list
	ENDIF '\n'
		{ $$ = if_statement_node($2, $5, $10); }
;

elif_statement:
	'|' expr_bool ':' '\n'
		sentence_list
		{ $$ = elif_statement_node($2, $5); }
;

elif_statement_list:
	elif_statement
		{$$ = elif_statement_list_node($1); }
	| elif_statement_list elif_statement
		{$$ = elif_statement_list_pair($1, $2); }
;

assign_statement:
	ID ASSIGN assign_statement
		{$$ = assign_statement_pair($1, $3); }
	| ID ASSIGN expr
		{$$ = assign_statement_node('e', $1, $3); }
	| ID ASSIGN mult_assign
		{$$ = assign_statement_node('m', $1, $3); }
;

mult_assign:
	'{' mult_assign_list '}'
		{ $$ = $2; }
;

mult_assign_list:
	mult_assign ',' mult_assign_list
		{ $$ = mult_assign_list_list('m', $1, $3); }
	| expr ',' mult_assign_list
		{ $$ = mult_assign_list_list('e', $1, $3); }
	| expr
		{ $$ = mult_assign_list_node($1); }
	| mult_assign
		{ $$ = $1; }
;

mult_assign_statement:
	id_list ASSIGN expr_list '\n'
		{ $$ = mult_assign_statement_node($1, $3); }
;


output_input_statement:
	ID expr_list '\n' // We'll need course need to check that ID = (PRINT|READ)
		{ $$ = output_input_statement_node($1, $2); }
;

while_loop:
	WHILE expr_bool '\n'
		sentence_list
	ENDWHILE '\n'
		{ $$ = while_loop_node($2, $4); }
;

fromto_assign_statement:
	assign_statement
		{ $$ = $1; }
	| '(' fromto_assign_statement ')'
		{ $$ = $2; }
;

fromto_loop:
	FROM fromto_assign_statement TO expr '\n'
		sentence_list
	ENDFROMTO '\n'
		{ $$ = fromto_loop_node($2, $4, $6); }
;

function_call:
	ID '(' expr_list ')'
		{ $$ = function_call_node($1, $3); }
;


procedure_call:
	ID '(' expr_list ')' '\n'
		{ $$ = procedure_call_node($1, $3); }
;

expr:
	INT_VAL
		{ $$ = expr_node('i', $1); }
	| BOOL_VAL
		{ $$ = expr_node('b', $1); }
	| FLOAT_VAL
		{ $$ = expr_node('f', $1); }
	| STR_VAL
		{ $$ = expr_node('s', $1); }
	| ID
		{ $$ = expr_node('d', $1); }
	| expr '+' expr
		{ $$ = expr_pair('+', $1, $3); }
	| expr '-' expr
		{ $$ = expr_pair('-', $1, $3); }
	| expr '*' expr
		{ $$ = expr_pair('*', $1, $3); }
	| expr '/' expr
		{ $$ = expr_pair('/', $1, $3); }
	| expr '%' expr
		{ $$ = expr_pair('%', $1, $3); }
	| expr '^' expr
		{ $$ = expr_pair('^', $1, $3); }
	| '-' expr %prec NEG
		{ $$ = expr_node('n', $2); }
	| '(' expr ')'
		{ $$ = $2; }
	| function_call
		{ $$ = $1; }
;

expr_list: /* empty */
	| expr_list ',' expr
		{ $$ = expr_list_pair($1, $3); }
	| expr
		{ $$ = expr_list_node($1); }
;

expr_bool:
	BOOL_VAL
		{ $$ = expr_bool_node('b', $1); }
	| ID
		{ $$ = expr_bool_node('i', $1); }
	| NOT_OP expr_bool
		{ $$ = expr_bool_node('n', $1); }
	| expr_bool AND_OP expr_bool
		{ $$ = expr_bool_pair('^', $1, $3); }
	| expr_bool OR_OP expr_bool
		{ $$ = expr_bool_pair('o', $1, $3); }
	| expr '=' expr
		{ $$ = expr_bool_pair('=', $1, $3); }
	| expr '<' expr
		{ $$ = expr_bool_pair('<', $1, $3); }
	| expr '>' expr
		{ $$ = expr_bool_pair('>', $1, $3); }
	| expr LE_OP expr
		{ $$ = expr_bool_pair('l', $1, $3); }
	| expr GE_OP expr
		{ $$ = expr_bool_pair('g', $1, $3); }
	| expr NOT_EQ expr
		{ $$ = expr_bool_pair('!', $1, $3); }
	| '(' expr_bool ')'
		{ $$ = $2; }
	| function_call
		{ $$ = $1; }
;

%%

int main(int argc, char *argv[])
{
	extern FILE *yyin;
	
	
	if (argc > 1) {
		if (!(yyin = fopen(argv[1], "r"))) {
			fprintf(stderr, "\nUnable to open source file: %s\n", argv[1]);
			exit(1);
		}
	}
	
	yyparse();
	
	return 0;
}
