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
	//#include "lea.h"
	
	#define yyerror(s) printf("%s\n", s)
%}

/*%union {
	int int_val;
	bool bool_var;
	float float_val;
	char char_val;
	char *str_val;
	node *no;
	node_list *nl;
}*/

%token PROG ALG FUNC IN_STREAM OUT_STREAM INOUT_STREAM DEV PROC END IN OUT INOUT CONSTS TYPES VARS START OF
%token IF ELSE IS_NULL ENDIF WHILE ENDWHILE FROM TO ENDFROMTO ID IS_NULL ARRAY REG ENDREG

%token INT_VAL
%token BOOL_VAL
%token FLOAT_VAL
%token CHAR_VAL
%token STR_VAL

/*%type <no>			program prog_header algorithm function procedure alg_header func_header 
%type <no>			proc_header interface_block in_var_dcl out_var_dcl inout_var_dcl 
%type <no>			declarations_block consts_block const_dcl_list types_block vars_block 
%type <no>			sentence_list_block sentence if_statement output_input_statement register
%type <no>			while_loop fromto_assign_statement fromto_loop function_call procedure_call expr expr_bool
%type <nl>			library proc_arg proc_arg_list in_arg_list out_arg_list inout_arg_list id_list
%type <nl>			array_dimensions int_val_list types_dcl str_list vars_dcl sentence_list elif_statement
%type <nl>			elif_statement_list assign_statement mult_assign_statement expr_list mult_assign mult_assign_list
*/
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
		{  }
;

prog_header:
	PROG ID '\n'
		{  }
;

library: /* empty */
	| library algorithm
		{  }
	| library function
		{  }
	| library procedure
		{  }
;

algorithm:
	alg_header
	interface_block
	declarations_block
	sentence_list_block
		{  }
;

function:
	func_header
	declarations_block
	sentence_list_block
		{  }
;

procedure:
	proc_header
	declarations_block
	sentence_list_block
		{  }
;

alg_header:
	ALG ID '\n'
		{  }
;

func_header:
	FUNC ID '(' in_arg_list ')'  DEV '(' out_var_dcl ')' '\n'
		{  }
;

proc_header:
	PROC ID '(' proc_arg_list ')' '\n'
		{  }
;

interface_block: /* empty */
	| IN in_arg_list '\n'
	interface_block
		{  }
	| OUT out_arg_list '\n'
	interface_block
		{  }
;

proc_arg: /* empty */
	| IN in_arg_list 
		{  }
	| OUT out_arg_list
		{  }
	| INOUT inout_arg_list
		{  }
;

proc_arg_list: /* empty */
	proc_arg_list ';' proc_arg
		{  }
	| proc_arg
		{  }
;

in_arg_list : /* empty */
	| in_arg_list ',' in_var_dcl
		{  }
	| in_var_dcl
		{  }
;

out_arg_list : /* empty */
	| out_arg_list ',' out_var_dcl
		{  }
	| out_var_dcl
		{  }
;

inout_arg_list : /* empty */
	| inout_arg_list ',' inout_var_dcl
		{  }
	| inout_var_dcl
		{  }
;

in_var_dcl:
	id_list   ':' ID
		{  }
	| id_list ':' ID OF ID
		{  }
	| id_list ':' ID OF IN_STREAM ID
		{  }
	| id_list  ':' ARRAY array_dimensions OF ID
		{  }
;

out_var_dcl:
	id_list   ':' ID
		{  }
	| id_list ':' ID OF ID
		{  }
	| id_list ':' ID OF OUT_STREAM ID
		{  }
	| id_list ':' ARRAY array_dimensions OF ID
		{  }
;

inout_var_dcl:
	id_list   ':' ID
		{  }
	| id_list ':' ID OF ID
		{  }
	| id_list ':' ID OF INOUT_STREAM ID
		{  }
	| id_list ':' ARRAY array_dimensions OF ID
		{  }
;

id_list:
	id_list ',' ID
		{  }
	| ID
		{  }
;

array_dimensions:
	'[' int_val_list ']'
		{  }
;

int_val_list:
	int_val_list ',' int_id_val
		{ }
	| int_id_val
		{ }
;

int_id_val:
	INT_VAL
		{ }
	| ID
		{ }
;

declarations_block:
	consts_block
	types_block
	vars_block
		{  }
;

consts_block: /* empty */
	| CONSTS '\n'
		const_dcl_list
		{  }
;

const_dcl_list: /* empty */
	| const_dcl_list
	id_list ':' BOOL_VAL '\n'
		{  }
	| const_dcl_list
	id_list ':' INT_VAL '\n'
		{  }
	| const_dcl_list
	id_list ':' FLOAT_VAL '\n'
		{  }
	| const_dcl_list
	id_list ':' CHAR_VAL '\n'
		{  }
	| const_dcl_list
	id_list ':' STR_VAL '\n'
		{  }
	| const_dcl_list
	id_list ':' register
		{  }
;

types_block: /* empty */
	| TYPES '\n'
		types_dcl_list
		{  }
;
types_dcl_list: /* empty */
	| types_dcl_list
	id_list ':' '(' str_list ')' '\n'
		{  }
	| types_dcl_list
	id_list ':' ID '\n'
		{  }
	| types_dcl_list
	id_list ':' ID OF ID '\n'
		{  }
	| types_dcl_list
	id_list ':' ARRAY array_dimensions OF ID '\n'
		{  }
	| types_dcl_list
	id_list ':' register
		{  }
;

str_list:
	str_list ',' ID
		{  }
	| ID
		{  }
;

vars_block: /* empty */
	| VARS '\n'
		vars_dcl
		{  }
;

vars_dcl: /* empty */
	| vars_dcl
	id_list ':' ID '\n'
		{  }
	| vars_dcl
	id_list ':' ID OF ID '\n'
		{  }
	| vars_dcl
	id_list ':' ARRAY array_dimensions OF ID '\n'
		{  }
	| vars_dcl
	id_list ':' register
		{  }
;

register:
	REG '\n'
	vars_dcl
	ENDREG '\n'
		{  }
	| '\n' REG '\n'
	vars_dcl
	ENDREG '\n'
		{  }
;

sentence_list_block:
	START '\n'
		sentence_list
	END '\n'
	| START '\n'
		sentence_list
	END
;

sentence_list: /* empty */
	| sentence_list sentence
		{  }
	| IS_NULL '\n'
		{  }
;

sentence:
	if_statement
		{  }
	| assign_statement '\n'
		{  }
	| mult_assign_statement
		{  }
	| output_input_statement
		{  }
	| while_loop
		{  }
	| fromto_loop
		{  }
	| function_call '\n'
		{  }
	| procedure_call
		{  }
;

if_statement:
	IF expr_bool cond_start
		sentence_list
	elif_statement_list
	'|' ELSE cond_start
		sentence_list
	ENDIF '\n'
		{  }
	| IF expr_bool cond_start
		sentence_list
	'|' ELSE cond_start
		sentence_list
	ENDIF '\n'
		{  }
;

cond_start:
	':' '\n'
	| ':'
;

elif_statement:
	'|' expr_bool cond_start
		sentence_list
		{  }
;

elif_statement_list:
	elif_statement
	| elif_statement_list elif_statement
;

assign_statement:
	struct_call ASSIGN assign_statement
		{  }
	| struct_call ASSIGN expr
		{  }
	| struct_call ASSIGN mult_assign
		{  }
;

mult_assign:
	'{' mult_assign_list '}'
		{  }
;

mult_assign_list:
	mult_assign ',' mult_assign_list
		{  }
	| expr ',' mult_assign_list
		{  }
	| expr
		{  }
	| mult_assign
		{  }
;

mult_assign_statement:
	variable_list ASSIGN expr_list '\n'
		{  }
;

// We'll need course need to check that id = (PRINT|READ)
output_input_statement:
	ID expr_list '\n'
		{ }
;

while_loop:
	WHILE expr_bool '\n'
		sentence_list
	ENDWHILE '\n'
		{  }
;

fromto_assign_statement:
	assign_statement
		{  }
	| '(' fromto_assign_statement ')'
		{  }
;

fromto_loop:
	FROM fromto_assign_statement TO expr '\n'
		sentence_list
	ENDFROMTO '\n'
		{  }
;

function_call:
	ID '(' expr_list ')'
		{  }
;

variable_call:
	ID array_dimensions
		{  }
	| ID
		{  }
;

struct_call:
	struct_call '.' variable_call
		{  }
	| variable_call
		{  }
;

variable_list:
	variable_list ',' variable_call
		{  }
	| variable_call
		{  }
;

procedure_call:
	ID '(' expr_list ')' '\n'
		{  }
;

expr:
	INT_VAL
		{  }
	| BOOL_VAL
		{  }
	| FLOAT_VAL
		{  }
	| STR_VAL
		{  }
	| struct_call
		{  }
	| expr '+' expr
		{  }
	| expr '-' expr
		{  }
	| expr '*' expr
		{  }
	| expr '/' expr
		{  }
	| expr '%' expr
		{  }
	| expr '^' expr
		{  }
	| '-' expr %prec NEG
		{  }
	| '(' expr ')'
		{  }
	| function_call
		{  }
;

expr_list: /* empty */
	| expr_list ',' expr
		{  }
	| expr
		{  }
;

expr_bool:
	BOOL_VAL
		{  }
	| struct_call
		{  }
	// TODO: "(no <something>)" doesn't work !
	| NOT_OP expr_bool %prec NEG
		{  }
	| expr_bool AND_OP expr_bool
		{  }
	| expr_bool OR_OP expr_bool
		{  }
	| expr '=' expr
		{  }
	| expr '<' expr
		{  }
	| expr '>' expr
		{  }
	| expr LE_OP expr
		{  }
	| expr GE_OP expr
		{  }
	| expr NOT_EQ expr
		{  }
	| '(' expr_bool ')'
		{  }
	| function_call
		{  }
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
