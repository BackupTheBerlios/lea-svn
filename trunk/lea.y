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
 * The list above has been automagically genereted executing:
 * $ ACTION=print_rule_types ./handy.awk lea.y
 * NOTE: tabulation added manually
 */
	Tprogram				*Tprogram;
	Tmethod_sym				*Tmethod_sym;
	Tinterface_sym			*Tinterface_sym;
	Tother_sym_list			*Tother_sym_list;
	Tid_list				*Tid_list;
	Tint_id_val_list		*Tint_id_val_list;
	Tdeclarations_sym		*Tdeclarations_sym;
	Tother_sym_list			*Tother_sym_list;
	Tother_type_list		*Tother_type_list;
	Tstr_list				*Tstr_list;
	Tother_sym_list 		*Tother_sym_list;
	Tother_type				*Tother_type;
	Tsentence_list			*Tsentence_list;
	Telif_statement			*Telif_statement;
	Telif_statement_list	*Telif_statement_list;
	Tsentence 				*Tsentence;
	Tassign_statement		*Tassign_statement;
	Tsentence				*Tsentence;
	Tvar_call_list			*Tvar_call_list;
	Tsentence				*Tsentence;
	Texpr_list				*Texpr_list;
	Texpr_bool				*Texpr_bool;
// \endlist
}

%token PROG ALG FUNC IN_STREAM OUT_STREAM INOUT_STREAM DEV PROC END IN OUT INOUT CONSTS TYPES VARS START OF
%token IF ELSE IS_NULL ENDIF WHILE ENDWHILE FROM TO ENDFROMTO IS_NULL ARRAY REG ENDREG

%token <int_val>	INT_VAL
%token <bool_val>	BOOL_VAL
%token <float_val>	FLOAT_VAL
%token <char_val>	CHAR_VAL
%token <str_val>	STR_VAL ID

/*
 * The list above has been automagically genereted executing:
 * $ ACTION=print_rule_types ./handy.awk lea.y
 * NOTE: tabulation added manually
 */
%type <Tstr_list>				str_list
%type <Tvar_call_list>			variable_list
%type <Tother_type_list>		types_dcl_list
%type <Tid_list>				id_list
%type <Tprogram>				program
%type <Tsentence>				assign_statement fromto_loop procedure_call
%type <Telif_statement>			elif_statement
%type <Tint_id_val_list>		int_val_list
%type <Texpr_list>				expr_list
%type <Tdeclarations_sym>		declarations_block
%type <Tassign_statement>		fromto_assign_statement
%type <Texpr_bool>				expr_bool
%type <Tinterface_sym>			interface_block
%type <Tother_sym_list>			in_arg_list const_dcl_list vars_reg_dcl
%type <Tmethod_sym>				library
%type <Telif_statement_list>	elif_statement_list
%type <Tsentence_list>			sentence_list
%type <Tother_type>				register
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
		{ $$ = TRprogram($1, $2, $3, $4); }
;

prog_header:
	PROG ID '\n'
		{ $$ = $2; }
;

library:
	EPSILON
		{ $$ = NULL; }
	| library algorithm
		{ $$ = TRlibrary($1, $2); }
	| library function
		{ $$ = TRlibrary($1, $2); }
	| library procedure
		{ $$ = TRlibrary($1, $2); }
;

algorithm:
	alg_header
	interface_block
	declarations_block
	sentence_list_block
		{ $$ = TRalgorithm($1, $2, $3, $4); }
;

function:
	func_header
	declarations_block
	sentence_list_block
		{ $$ = TRfunction($1, $2, $3); }
;

procedure:
	proc_header
	declarations_block
	sentence_list_block
		{ $$ = TRprocedure($1, $2, $3); }
;

alg_header:
	ALG ID '\n'
		{ $$ = $2; }
;

func_header:
	FUNC ID '(' in_arg_list ')'  DEV '(' out_var_dcl ')' '\n'
		{ $$ = TRfunc_header($2, $4, $8); }
;

proc_header:
	PROC ID '(' proc_arg_list ')' '\n'
		{ $$ = TRproc_header($2, $4); }
;

interface_block:
	EPSILON
		{ $$ = NULL; }
	| IN in_arg_list '\n'
	interface_block
		{ $$ = TRinterface_block_in($2, $4); }
	| OUT out_arg_list '\n'
	interface_block
		{ $$ = TRinterface_block_out($2, $4); }
;

proc_arg:
	EPSILON
		{ $$ = NULL; }
	| IN in_arg_list 
		{ $$ = TRproc_arg_in($2); }
	| OUT out_arg_list
		{ $$ = TRproc_arg_out($2); }
	| INOUT inout_arg_list
		{ $$ = TRproc_arg_inout($2); }
;

proc_arg_list:
	proc_arg_list ';' proc_arg
		{ $$ = TRproc_arg_list($1, $3);  }
	| proc_arg
		{ $$ = TRproc_arg_list(NULL, $1); }
;

in_arg_list:
	EPSILON
		{ $$ = NULL; }
	| in_arg_list ',' in_var_dcl
		{ $$ = TRin_arg_list($1, $3); }
	| in_var_dcl
		{ $$ = TRin_arg_list(NULL, $1); }
;

out_arg_list:
	EPSILON
		{ $$ = NULL; }
	| out_arg_list ',' out_var_dcl
		{ $$ = TRout_arg_list($1, $3); }
	| out_var_dcl
		{ $$ = TRout_arg_list(NULL, $1); }
;

inout_arg_list:
	EPSILON
		{ $$ = NULL; }
	| inout_arg_list ',' inout_var_dcl
		{ $$ = TRinout_arg_list($1, $3); }
	| inout_var_dcl
		{ $$ = TRinout_arg_list(NULL, $1); }
;

in_var_dcl:
	id_list   ':' ID
		{ $$ = TRin_var_dcl($1, $3, NULL, NULL); }
	| id_list ':' ID OF ID
		{ $$ = TRin_var_dcl($1, $3, $5, NULL); }
	| id_list ':' ID OF IN_STREAM ID
		{ $$ = TRin_var_dcl($1, $3, $6, $5); }
	| id_list  ':' ARRAY array_dimensions OF ID
		{ $$ = TRin_var_dcl_array($1, $4, $6); }
;

out_var_dcl:
	id_list   ':' ID
		{ $$ = TRout_var_dcl($1, $3, NULL, NULL); }
	| id_list ':' ID OF ID
		{ $$ = TRout_var_dcl($1, $3, $5, NULL); }
	| id_list ':' ID OF OUT_STREAM ID
		{ $$ = TRout_var_dcl($1, $3, $6, $5); }
	| id_list ':' ARRAY array_dimensions OF ID
		{ $$ = TRout_varl_dcl_array($1, $4, $6); }
;

inout_var_dcl:
	id_list   ':' ID
		{ $$ = TRinout_var_dcl($1, $3, NULL, NULL); }
	| id_list ':' ID OF ID
		{ $$ = TRinout_var_dcl($1, $3, $5, NULL); }
	| id_list ':' ID OF INOUT_STREAM ID
		{ $$ = TRinout_var_dcl($1, $3, $6, $5); }
	| id_list ':' ARRAY array_dimensions OF ID
		{ $$ = TRinout_var_dcl_array($1, $4, $6); }
;

id_list:
	id_list ',' ID
		{ $$ = TRid_list($1, $3); }
	| ID
		{ $$ = TRid_list(NULL, $1); }
;

array_dimensions:
	'[' int_val_list ']'
		{ $$ = $2; }
;

int_val_list:
	int_val_list ',' int_id_val
		{ $$ = TRint_val_list($1, $3); }
	| int_id_val
		{ $$ = TRint_val_list(NULL, $1); }
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
		{ $$ = TRdeclarations_block($1, $2, $3); }
;

consts_block:
	EPSILON
		{ $$ = NULL; }
	| CONSTS '\n'
		const_dcl_list
		{ $$ = $3; }
;

const_dcl_list:
	EPSILON
		{ $$ = NULL; }
	| const_dcl_list
	id_list ':' BOOL_VAL '\n'
		{ $$ = TRconst_dcl_list_bool($1, $2, $4); }
	| const_dcl_list
	id_list ':' INT_VAL '\n'
		{ $$ = TRconst_dcl_list_int($1, $2, $4); }
	| const_dcl_list
	id_list ':' FLOAT_VAL '\n'
		{ $$ = TRconst_dcl_list_float($1, $2, $4); }
	| const_dcl_list
	id_list ':' CHAR_VAL '\n'
		{ $$ = TRconst_dcl_list_char($1, $2, $4); }
	| const_dcl_list
	id_list ':' STR_VAL '\n'
		{ $$ = TRconst_dcl_list_str($1, $2, $4); }
	| const_dcl_list
	id_list ':' register
		{ $$ = TRconst_dcl_list_reg($1, $2, $4); }
;

types_block:
	EPSILON
		{ $$ = NULL; }
	| TYPES '\n'
		types_dcl_list
		{ $$ = $3; }
;
types_dcl_list:
	EPSILON
		{ $$ = NULL; }
	| types_dcl_list
	id_list ':' '(' str_list ')' '\n'
		{ $$ = TRtypes_dcl_list_enum($1, $2, $5); }
	| types_dcl_list
	id_list ':' ID '\n'
		{ $$ = TRtypes_dcl_list_var($1, $2, $4, NULL); }
	| types_dcl_list
	id_list ':' ID OF ID '\n'
		{ $$ = TRtypes_dcl_list_var($1, $2, $4, $6); }
	| types_dcl_list
	id_list ':' ARRAY array_dimensions OF ID '\n'
		{ $$ = TRtypes_dcl_list_array($1, $2, $5, $7); }
	| types_dcl_list
	id_list ':' register
		{ $$ = TRtypes_dcl_list_reg($1, $2, $4); }
;

str_list:
	str_list ',' ID
		{ $$ = TRstr_list($1, $3); }
	| ID
		{ $$ = TRstr_list(NULL, $1); }
;

vars_block:
	EPSILON
		{ $$ = NULL; }
	| VARS '\n'
		vars_dcl
		{ $$ = $3; }
;

vars_dcl:
	vars_reg_dcl
		{ $$ = $1; }
	| vars_dcl
	id_list ':' register  //TODO: !!!!!
		{ $$ = TRvars_dcl_reg($1, $2, $4); }
;
vars_reg_dcl:
	EPSILON
		{ $$ = NULL; }
	| vars_reg_dcl
	id_list ':' ID '\n'
		{ $$ = TRvars_dcl_var($1, $2, $4, NULL); }
	| vars_reg_dcl
	id_list ':' ID OF ID '\n'
		{ $$ = TRvars_dcl_var($1, $2, $4, $6); }
	| vars_reg_dcl
	id_list ':' ARRAY array_dimensions OF ID '\n'
		{ $$ = TRvars_dcl_array($1, $2, $5, $7); }
;

register:
	REG '\n'
		vars_reg_dcl
	ENDREG '\n'
		{ $$ = TRregister($3); }
	| '\n' REG '\n'
		vars_reg_dcl
	ENDREG '\n'
		{ $$ = TRregister($4); }
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
	| sentence_list sentence
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
	| function_call '\n'
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
		{ $$ = TRelif_statement_list($1, $2); }
	| elif_statement
		{ $$ = TRelif_statement_list(NULL, $1); }
;

assign_statement:
	struct_call ASSIGN assign_statement
		{ $$ = TRassign_statement_assign($1, $3); }
	| struct_call ASSIGN expr
		{ $$ = TRassign_statement_expr($1, $3); }
	/* TODO: | struct_call ASSIGN mult_assign
		{ $$ = TRassign_statement_mult($1, $3); }*/
;
/* TODO:
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
		{ $$ = TRmult_assign_list($1, NULL); }*/
;

mult_assign_statement:
	variable_list ASSIGN expr_list '\n'
		{ $$ = TRmult_assign_statement($1, $3); }
;

// We'll need course need to check that id = (PRINT|READ)
output_input_statement:
	ID expr_list '\n'
		{ $$ = TRoutput_input_statement($1, $2); }
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
	ID '[' expr_list ']'
		{ $$ = TRvariable_call($1, $2); }
	| ID
		{  $$ = TRvariable_call($1, NULL); }
;

struct_call:
	struct_call '.' variable_call
		{ $$ = TRstruct_call($1, $3); }
	| variable_call
		{ $$ = TRstruct_call(NULL, $1); }
;

variable_list:
	variable_list ',' variable_call
		{ $$ = TRvariable_list($1, $3); }
	| variable_call
		{ $$ = TRvariable_list(NULL, $1); }
;

procedure_call:
	ID '(' expr_list ')' '\n'
		{ $$ = TRprocedure_call($1, $3); }
;

expr_list:
	EPSILON
		{ $$ = NULL; }
	| expr_list ',' expr
		{ $$ = TRexpr_list($1, $3); }
	| expr
		{ $$ = TRexpr_list(NULL, $1); }
;

expr_bool:
	BOOL_VAL
		{ $$ = TRexpr_bool_val($1); }
	| '(' expr_bool ')'
		{ $$ = $2; }
	| struct_call
		{ $$ = TRexpr_bool_struct($1); }
	| NOT_OP expr_bool %prec NEG
		{ $$ = TRexpr_bool('!', $2, NULL); }
	| expr_bool AND_OP expr_bool
		{ $$ = TRexpr_bool($2, $1, $3); }
	| expr_bool OR_OP expr_bool
		{ $$ = TRexpr_bool($2, $1, $3); }
	| expr '=' expr
		{ $$ = TRexpr_bool($2, $1, $3); }
	| expr '<' expr
		{ $$ = TRexpr_bool($2, $1, $3); }
	| expr '>' expr
		{ $$ = TRexpr_bool($2, $1, $3); }
	| expr LE_OP expr
		{ $$ = TRexpr_bool('l', $1, $3); }
	| expr GE_OP expr
		{ $$ = TRexpr_bool('g', $1, $3); }
	| expr NOT_EQ expr
		{ $$ = TRexpr_bool('n', $1, $3); }
	| function_call
		{ $$ = TRexpr_bool_fcall($1); }
;

expr:
	INT_VAL
		{ $$ = TRexpr_int($1); }
	// TODO: Sometimes a expr_bool can also be considered an expr,
	// usually when it reffers to a boolean variable, but if we
	// add here expr_bool 91 reduce/reduce problems appear!
	| BOOL_VAL
		{ $$ = TRexpr_expr_bool($1); }
	| FLOAT_VAL
		{ $$ = TRexpr_float($1); }
	| STR_VAL
		{ $$ = TRexpr_str($1); }
	| struct_call
		{ $$ = TRexpr_struct($1); }
	| expr '+' expr
		{ $$ = TRexpr($2, $1, $3); }
	| expr '-' expr
		{ $$ = TRexpr($2, $1, $3); }
	| expr '*' expr
		{ $$ = TRexpr($2, $1, $3); }
	| expr '/' expr
		{ $$ = TRexpr($2, $1, $3); }
	| expr '%' expr
		{ $$ = TRexpr($2, $1, $3); }
	| expr '^' expr
		{ $$ = TRexpr($2, $1, $3); }
	| '-' expr %prec NEG
		{ $$ = TRexpr('n', $2, NULL); }
	| '(' expr ')'
		{ $$ = $2; }
	| function_call
		{ $$ = TRexpr_fcall($1); }
;

EPSILON:
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
