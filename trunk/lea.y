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
	#include "lea-translator.h"
	
	#define yyerror(s) printf("%s\n", s)
%}

%union {
	int						*int_val;
	bool					*bool_val;
	float					*float_val;
	char					*char_val;
	char					*str_val;
/*
 * The list above has been partially automagically generated executing:
 * $ ACTION=print_union_types ./handy.awk lea-translator.h
 */
	Tprogram				*Tprogram;
	Tmethod_sym				*Tmethod_sym;
	Tinterface_sym			*Tinterface_sym;
	Tother_sym				*Tother_sym;
	Tvar_sym_list			*Tvar_sym_list;
	Tother_sym_list			*Tother_sym_list;
	Tid_list				*Tid_list;
	Tint_id_val				*Tint_id_val;
	Tint_id_val_list		*Tint_id_val_list;
	Tdeclarations_sym		*Tdeclarations_sym;
	Tother_type_list		*Tother_type_list;
	Tstr_list				*Tstr_list;
	Tother_type				*Tother_type;
	Tsentence_list			*Tsentence_list;
	Telif_statement			*Telif_statement;
	Telif_statement_list	*Telif_statement_list;
	Tsentence 				*Tsentence;
	Tassign_statement		*Tassign_statement;
	Texpr_list				*Texpr_list;
	Texpr_list_nested		*Texpr_list_nested;
	Texpr_bool				*Texpr_bool;
	Texpr					*Texpr;
// \endlist
}

%token PROG ALG FUNC IN_STREAM OUT_STREAM INOUT_STREAM DEV PROC END IN OUT INOUT CONSTS TYPES VARS START OF
%token IF ELSE IS_NULL ENDIF WHILE ENDWHILE FROM TO ENDFROMTO IS_NULL ARRAY REG ENDREG PRINT READ

%token <int_val>	INT_VAL
%token <bool_val>	BOOL_VAL
%token <float_val>	FLOAT_VAL
%token <char_val>	CHAR_VAL
%token <str_val>	STR_VAL ID

/*
 * The list above has been partially automagically generated executing:
 * $ ACTION=print_rule_types ./handy.awk lea.y
 * NOTE: tabulation added manually
 */
%type <Tstr_list>				str_list
%type <Texpr>					expr expr_op expr_val
%type <Tid_list>				id_list
%type <Telif_statement>			elif_statement
%type <Tsentence>				if_statement assign_statement mult_assign_statement output_input_statement while_loop fromto_loop function_call variable_call struct_call procedure_call sentence input_statement output_statement
%type <Tint_id_val_list>		int_val_list array_dimensions
%type <Texpr_list>				expr_list expr_list_full
%type <Texpr_list_nested>		mult_assign mult_assign_list
%type <Tint_id_val>				int_id_val
%type <Tassign_statement>		fromto_assign_statement
%type <Texpr_bool>				expr_bool
%type <Tvar_sym_list>			variable_list
%type <Telif_statement_list>	elif_statement_list
%type <Tsentence_list>			sentence_list sentence_list_block
// \endlist

%start	program

%left	'-' '+'
%left	'*'  '/' '%'
%right	'^'
%right	ASSIGN
%right	'=' GE_OP LE_OP '<' '>' NOT_EQ
%left	AND_OP OR_OP NOT_OP

%nonassoc NEG

%%

program:
	prog_header
	declarations_block
	sentence_list_block
	library
		{ TRprogram($3); }
;

prog_header:
	PROG ID '\n'
		{ TRprog_header($2); }
;

library:
	EPSILON
	| library algorithm
	| library function
	| library procedure
;

algorithm:
	alg_header
	interface_block
	declarations_block
	sentence_list_block
;

function:
	func_header
	declarations_block
	sentence_list_block
;

procedure:
	proc_header
	declarations_block
	sentence_list_block
;

alg_header:
	ALG ID '\n'
		{ TRalg_header($2); }
;

func_header:
	FUNC ID 
		{ TRfunc_header($2); }
	'(' in_arg_list ')'  DEV '(' out_var_dcl ')' '\n'
;

proc_header:
	PROC ID 
		{ TRproc_header($2); }
		'(' proc_arg_list ')' '\n'
;

interface_block:
	EPSILON
	| IN in_arg_list '\n'
	interface_block
	| OUT out_arg_list '\n'
	interface_block
;

proc_arg:
	EPSILON
	| IN in_arg_list
	| OUT out_arg_list
	| INOUT inout_arg_list
;

proc_arg_list:
	proc_arg ';' proc_arg_list
	| proc_arg
;

in_arg_list:
	EPSILON
	| in_var_dcl ',' in_arg_list
	| in_var_dcl
;

out_arg_list:
	EPSILON
	| out_var_dcl ',' out_arg_list
	| out_var_dcl
;

inout_arg_list:
	EPSILON
	| inout_var_dcl ',' inout_arg_list
	| inout_var_dcl
;

in_var_dcl:
	id_list   ':' ID
		{ TRin_var_dcl($1, $3, (char *)NULL, (char)NULL); }
	| id_list ':' ID OF ID
		{ TRin_var_dcl($1, $3, $5, (char)NULL); }
	| id_list ':' ID OF IN_STREAM ID
		{ TRin_var_dcl($1, $3, $6, 's'); }
	| id_list  ':' ARRAY array_dimensions OF ID
		{ TRin_var_dcl_array($1, $4, $6); }
;

out_var_dcl:
	id_list   ':' ID
		{ TRout_var_dcl($1, $3, (char *)NULL, (char)NULL); }
	| id_list ':' ID OF ID
		{ TRout_var_dcl($1, $3, $5, (char)NULL); }
	| id_list ':' ID OF OUT_STREAM ID
		{ TRout_var_dcl($1, $3, $6, 's'); }
	| id_list ':' ARRAY array_dimensions OF ID
		{ TRout_var_dcl_array($1, $4, $6); }
;

inout_var_dcl:
	id_list   ':' ID
		{ TRinout_var_dcl($1, $3, (char *)NULL, (char)NULL); }
	| id_list ':' ID OF ID
		{ TRinout_var_dcl($1, $3, $5, (char)NULL); }
	| id_list ':' ID OF INOUT_STREAM ID
		{ TRinout_var_dcl($1, $3, $6, 's'); }
	| id_list ':' ARRAY array_dimensions OF ID
		{ TRinout_var_dcl_array($1, $4, $6); }
;

id_list:
	ID ',' id_list
		{ $$ = TRid_list($1, $3); }
	| ID
		{ $$ = TRid_list($1, NULL); }
;

array_dimensions:
	'[' int_val_list ']'
		{ $$ = $2; }
;

int_val_list:
	int_id_val ',' int_val_list
		{ $$ = TRint_val_list($1, $3); }
	| int_id_val
		{ $$ = TRint_val_list($1, NULL); }
;

int_id_val:
	INT_VAL
		{ $$ = TRint_id_val_int($1); }
	| ID
		{ $$ = TRint_id_val_id($1); }
;

declarations_block:
	consts_block
	types_block
	vars_block
;

consts_block:
	EPSILON
	| CONSTS '\n'
		const_dcl_list
;

const_dcl_list:
	EPSILON
	| const_dcl const_dcl_list
;

const_dcl:
	id_list ':' BOOL_VAL '\n'
		{ TRconst_dcl_bool($1, $3); }
	| id_list ':' INT_VAL '\n'
		{ TRconst_dcl_int($1, $3); }
	| id_list ':' FLOAT_VAL '\n'
		{ TRconst_dcl_float($1, $3); }
	| id_list ':' CHAR_VAL '\n'
		{ TRconst_dcl_char($1, $3); }
	| id_list ':' STR_VAL '\n'
		{ TRconst_dcl_str($1, $3); }
	| id_list ':' reg_init 
		{ TRconst_dcl_reg($1); }
	register
;

types_block:
	EPSILON
	| TYPES '\n'
		types_dcl_list
;
types_dcl_list:
	EPSILON
	| types_dcl types_dcl_list
;

types_dcl:
	id_list ':' '(' str_list ')' '\n'
		{ TRtypes_dcl_enum($1, $4); }
	| id_list ':' ID '\n'
		{ TRtypes_dcl_var($1, $3, NULL); }
	| id_list ':' ID OF ID '\n'
		{ TRtypes_dcl_var($1, $3, $5); }
	| id_list ':' ARRAY array_dimensions OF ID '\n'
		{ TRtypes_dcl_array($1, $4, $6); }
	| id_list ':' reg_init 
		{ TRtypes_dcl_reg($1); }
	register
;

str_list:
	ID ',' str_list
		{ $$ = TRstr_list($1, $3); }
	| ID
		{ $$ = TRstr_list($1, NULL); }
;

vars_block:
	EPSILON
	| VARS '\n'
		vars_dcl
;

vars_dcl:
	EPSILON
	| vars_noreg_dcl vars_dcl
	| id_list':' reg_init
		{ TRvars_dcl_reg($1); }
	register  //TODO: !!!!!
	vars_dcl
;

vars_noreg_dcl_list:
	EPSILON
	| vars_noreg_dcl vars_noreg_dcl_list
;

vars_noreg_dcl:
	id_list ':' ID '\n'
		{ TRvars_noreg_dcl($1, $3, NULL); }
	| id_list ':' ID OF ID '\n'
		{ TRvars_noreg_dcl($1, $3, $5); }
	| id_list ':' ARRAY array_dimensions OF ID '\n'
		{ TRvars_noreg_dcl_array($1, $4, $6); }
;

reg_init:
	REG '\n'
	| '\n' REG '\n'
;

register:
		vars_noreg_dcl_list
	ENDREG '\n'
		{ TRregister(); }
;

sentence_list_block:
	START '\n'
		sentence_list
	END '\n'
		{ $$ = $3; }
	| START '\n'
		sentence_list
	END
		  { $$ = $3; }
;

sentence_list:
	EPSILON
		{ $$ = NULL; }
	| sentence sentence_list
		{ $$ = TRsentence_list($1, $2); }
	| IS_NULL '\n'
		{ $$ = NULL; }
;

sentence:
	if_statement
		{ $$ = $1; }
	| assign_statement '\n'
		{ $$ = $1; }
	| mult_assign_statement
		{ $$ = $1; }
	| output_input_statement
		{ $$ = $1; }
	| while_loop
		{ $$ = $1; }
	| fromto_loop
		{ $$ = $1; }
	| procedure_call
		{ $$ = $1; }
;

if_statement:
	IF expr_bool cond_start
		sentence_list
	elif_statement_list
	'|' ELSE cond_start
		sentence_list
	ENDIF '\n'
		{ $$ = TRif_statement($2, $4, $5, $9); }
	| IF expr_bool cond_start
		sentence_list
	'|' ELSE cond_start
		sentence_list
	ENDIF '\n'
		{ $$ = TRif_statement($2, $4, NULL, $8); }
;

cond_start:
	':' '\n'
	| ':'
;

elif_statement:
	'|' expr_bool cond_start
		sentence_list
		{ $$ = TRelif_statement($2, $4); }
;

elif_statement_list:
	elif_statement_list elif_statement
		{ $$ = TRelif_statement_list($2, $1); }
	| elif_statement
		{ $$ = TRelif_statement_list($1, NULL); }
;

assign_statement:
	struct_call ASSIGN assign_statement
		{ $$ = TRassign_statement_assign($1, $3); }
	| struct_call ASSIGN expr
		{ $$ = TRassign_statement_expr($1, $3); }
	| struct_call ASSIGN mult_assign
		{ $$ = TRassign_statement_mult($1, $3); }
;

mult_assign:
	'{' mult_assign_list '}'
		{ $$ = $2; }
;

mult_assign_list:
	mult_assign ',' mult_assign_list
		{ $$ = TRmult_assign_list($1, $3); }
	| expr ',' mult_assign_list
		{ $$ = TRmult_assign_list_expr($1, $3); }
	| expr
		{ $$ = TRmult_assign_list_expr($1, NULL); }
	| mult_assign
		{ $$ = TRmult_assign_list($1, NULL); }
;

mult_assign_statement:
	variable_call ',' variable_list ASSIGN expr_list_full '\n'
		{ $$ = TRmult_assign_statement(TRvariable_list($1, $3), $5); }
;

output_input_statement:
	output_statement
		{ $$ = $1; }
	| input_statement
		{ $$ = $1; }
;

input_statement:
	READ expr_list_full '\n'
		{ $$ = TRoutput_input_statement('i', $2); }
	| READ '(' expr_list_full ')' '\n'
		{ $$ = TRoutput_input_statement('i', $3); }
;

output_statement:
	PRINT expr_list_full '\n'
		{ $$ = TRoutput_input_statement('o', $2); }
	| PRINT '(' expr_list_full ')' '\n'
		{ $$ = TRoutput_input_statement('o', $3); }
;

while_loop:
	WHILE expr_bool '\n'
		sentence_list
	ENDWHILE '\n'
		{ $$ = TRwhile_loop($2, $4); }
;

fromto_assign_statement:
	struct_call ASSIGN expr
		{ $$ = TRfromto_assign_statement($1, $3); }
	| '(' fromto_assign_statement ')'
		{ $$ = $2; }
;

fromto_loop:
	FROM fromto_assign_statement TO expr '\n'
		sentence_list
	ENDFROMTO '\n'
		{ $$ = TRfromto_loop($2, $4, $6); }
;

function_call:
	ID '(' expr_list ')'
		{ $$ = TRfunction_call($1, $3); }
;

variable_call:
	ID '[' expr_list_full ']'
		{ $$ = TRvariable_call($1, $3); }
	| ID
		{  $$ = TRvariable_call_node($1); }
;

struct_call:
	variable_call '.' struct_call
		{ $$ = TRstruct_call($1, $3); }
	| variable_call
		{ $$ = TRstruct_call_node($1); }
;

variable_list:
	variable_call ',' variable_list
		{ $$ = TRvariable_list($1, $3); }
	| variable_call
		{ $$ = TRvariable_list_node($1); }
;

procedure_call:
	ID '(' expr_list ')' '\n'
		{ $$ = TRprocedure_call($1, $3); }
;

expr_list:
	EPSILON
		{ $$ = NULL; }
	| expr_list_full
		{ $$ = $1; }
;

expr_list_full:
	expr ',' expr_list_full
		{ $$ = TRexpr_list_full($1, $3); }
	| expr
		{ $$ = TRexpr_list_full($1, NULL); }
;

expr_bool:
	BOOL_VAL
		{ $$ = TRexpr_bool_val($1); }
	| function_call
		{ $$ = TRexpr_bool_fcall($1); }
	| struct_call
		{ $$ = TRexpr_bool_struct($1); }
	| '(' expr_bool ')'
		{ $$ = $2; }
	| NOT_OP expr_bool %prec NEG
		{ $$ = TRexpr_bool_not($2); }
	| expr_bool AND_OP expr_bool
		{ $$ = TRexpr_bool_log('&', $1, $3); }
	| expr_bool OR_OP expr_bool
		{ $$ = TRexpr_bool_log('|', $1, $3); }
	| expr '=' expr
		{ $$ = TRexpr_bool('=', $1, $3); }
	| expr '<' expr
		{ $$ = TRexpr_bool('<', $1, $3); }
	| expr '>' expr
		{ $$ = TRexpr_bool('>', $1, $3); }
	| expr LE_OP expr
		{ $$ = TRexpr_bool('l', $1, $3); }
	| expr GE_OP expr
		{ $$ = TRexpr_bool('g', $1, $3); }
	| expr NOT_EQ expr
		{ $$ = TRexpr_bool('n', $1, $3); }
;

expr_val:
	INT_VAL
		{ $$ = TRexpr_int($1); }
	| FLOAT_VAL
		{ $$ = TRexpr_float($1); }
	| STR_VAL
		{ $$ = TRexpr_str($1); }
	| function_call
		{ $$ = TRexpr_fcall($1); }
	| struct_call
		{ $$ = TRexpr_struct($1); }
;

expr_op:
	expr_val
		{ $$ = $1; }
	| expr_op '+' expr_op
		{ $$ = TRexpr('+', $1, $3); }
	| expr_op '-' expr_op
		{ $$ = TRexpr('-', $1, $3); }
	| expr_op '*' expr_op
		{ $$ = TRexpr('*', $1, $3); }
	| expr_op '/' expr_op
		{ $$ = TRexpr('/', $1, $3); }
	| expr_op '%' expr_op
		{ $$ = TRexpr('%', $1, $3); }
	| expr_op '^' expr_op
		{ $$ = TRexpr('^', $1, $3); }
	| '-' expr_op %prec NEG
		{ $$ = TRexpr('n', $2, NULL); }
	| '+' expr_op %prec NEG
		{ $$ = $2; }
	| '(' expr_op ')'
		{ $$ = $2; }
;

expr:
	expr_bool
		{ $$ = TRexpr_expr_bool($1); }
	| expr_op
		{ $$ = $1; }
;


EPSILON:
;

%%

int main(int argc, char *argv[])
{
	extern FILE *yyin;
	char *header;
	
	if (argc > 1) {
		if (!(yyin = fopen(argv[1], "r"))) {
			fprintf(stderr, "\nUnable to open source file: %s\n", argv[1]);
			exit(1);
		} else {
			header = calloc(255, sizeof(char));
			fgets(header,255, yyin);
			
			/*
			 * Detect whether header does contain a
			 * Linux scripting header or not. If not,
			 * reposition to the beguinning of the
			 * stream.
			 */
			
			if(header[0] != '#' || header[1] != '!')
			{
				printf("bingo: %s\n", header);
				fseek(yyin, 0, SEEK_SET);
			}
			free(header);
		}
	}
	
	//Initialization:
	sym_table		= initSymTable(PRIME);
	tmp_method_sym	= NULL;
	tmp_reg_names	= NULL;
	tmp_reg_type	= NULL;
	
	yyparse();
	
	return 0;
}
