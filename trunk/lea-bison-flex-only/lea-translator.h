/**
 * \file lea-translator.h
 * \brief Translator to Abstract Tree header
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
 * along with Lea; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 * 
 * See COPYING for details.
 */

#ifndef LEA_TRANSLATOR_H
	#define LEA_TRANSLATOR_H
	
	#include <stdlib.h>
	#include <string.h>
	
	/**
	 * \brief defines of (V)value type and their assigned values
	 * This way we'll discriminate value types easily 
	 */
	#define Vint_val				0
	#define Vbool_val				1
	#define Vfloat_val				2
	#define Vchar_val				3
	#define Vstr_val				4
	#define Vconst_int_val			5
	#define Vconst_bool_val			6
	#define Vconst_float_val		7
	#define Vconst_char_val			8
	#define Vconst_str_val			9
	
	#define Vvar_call				10
	#define Varray_call				11
	#define Vstruct_call			12
	
	#define Vstream					13
	#define Vinput_stream			14
	#define Voutput_stream			15
	#define Vio_stream				16
	#define Vfile					17
	#define Vinput_file				18
	#define Voutput_file			19
	#define Vio_file				20
	
	#define Venum_type				21
	#define Varray_type				22
	#define Vvar_type				23
	#define Vreg_type				24
	
	#define OPnot					25
	#define OPand					26
	#define OPor					27
	#define OPeq					28
	#define OPless					29
	#define OPgreater				30
	#define OPle					31
	#define OPge					32
	
	#define OPplus					33
	#define OPsub					34
	#define OPmult					35
	#define OPdiv					36
	#define OPrest					37
	#define OPraise					38
	
	#define Valg					39
	#define Vfunc					40
	#define Vproc					41
	
	#define Vif_statement			42
	#define Vassign_statement		43
	#define Vmult_assign_statement	44
	#define Vwhile_loop				45
	#define Vfromto_loop			46
	#define Vmethod_call			47
	#define Vreserved_call			48
	
	#define Valgorithm				49
	#define Vfunction				50
	#define Vprocedure				51
	
	#define OPop					52
	#define OPvar_call				53
	#define OParray_call			54
	#define OPmethod_call			55
	
	/****************************
	*     Types definitions     *
	****************************/
	/**
	 * \brief Definition of all the (T)types used in the translator
	 */
	
	/**
	 * \brief bool type definition
	 */
	typedef enum {false, true} bool;
	
	/**
	 * \brief Ttype type definition
	 * It contains all the essential types of information
	 */
	typedef union {
		int *int_val;
		bool *bool_val;
		float *float_val;
		char *char_val;
		FILE *file;
	} Ttype;
	
	/**
	 * \brief Tstr_val type definition
	 */
	typedef struct {
		long *length;
		char *val;
	} Tstr_val;
	
	/**
	 * \brief Tid type definition
	 */
	typedef Tstr_val Tid;
	
	/**
	 * \brief Tid_list type definition
	 */
	typedef struct {
		Tid *id;
		Tid_list *next;
	} Tid_list;
	
	/**
	 * \brief Tint_id_val type definition
	 */
	typedef union {
		Tvar_call *var;
		int *val;
	} Tint_id_val;
	
	/**
	 * \brief Tstr_list type definition
	 */
	typedef Tid_list Tstr_list;
	
	/**
	 * \brief Tarray_dimensions type definition
	 */
	typedef Tid_list Tarray_dimensions;
	
	/**
	 * \brief Tint_val_list type definition
	 */
	typedef struct {
		Tint_id_val *value;
		Tint_val_list *next;
	} Tint_val_list;
	
	/**
	 * \brief Tvar_call type definition
	 * Note that constants and vars are both called this way
	 */
	typedef union {
		Tid *name;
		Tvar_sym *symbol;
	} Tvar_call;
	
	/**
	 * \brief Tarray_call_by_name type definition
	 */
	typedef struct {
		Tid *name;
		Tarray_dimensions *index_list;
	} Tarray_call_by_name;
	
	/**
	 * \brief Tarray_call type definition
	 */
	typedef union {
		Tarray_call_by_name *by_name;
		Tarray_sym *symbol;
	} Tarray_call;
	
	/**
	 * \brief Tvar_sym type definition
	 */
	typedef struct {
		Tid *name;
		int *type;
		Ttype *storage;
	} Tvar_sym;
	
	/**
	 * \brief Tenum_type type definition
	 */
	typedef struct {
		Tid *name;
		Tid_list *storage;
	} Tenum_type;
	
	/**
	 * \brief Tenum_sym type definition
	 */
	typedef struct {
		Tid *name;
		enum {
			Tid *name;
			Tenum_type *type_sym;
		} type;
		Tid *storage;
	} Tenum_sym;
	
	/**
	 * \brief Tarray_type type definition
	 */
	typedef struct {
		Tid *name;
		Tarray_dimensions *dimensions;
		Ttype_sym *type_sym;
	} Tarray_type;
	
	/**
	 * \brief Tarray_sym type definition
	 */
	typedef struct {
		Tid *name;
		union {
			Tarray_type *array_type_sym;
			Ttype_sym type_sym;
		} *type_sym;
		Ttype_sym_val_list *storage;
	} Tarray_sym;
	
	/**
	 * \brief Tfile_type type definition
	 * Note that files and streams are used internally in this
	 * implementation the same way
	 */
	typedef struct {
		Tid *name;
		Ttype_sym *type_sym;
	} Tfile_type;
	
	/**
	 * \brief Tfile_sym type definition
	 * WARNING: Check that we don't have files of registers that
	 * contain files, for $DEITY's sake!
	 */
	typedef struct {
		FILE *file;
		Tfile_type *type_sym;
	} Tfile_sym;
	
	/**
	 * \brief Ttype_sym type definition
	 */
	typedef struct{
		union {
			Ttype *normal;
			Tenum_type *enumerated;
			Tarray_type *array;
			Tfile_type *file;
			Treg_type *reg;
		} type_sym;
		int *type;
	} Ttype_sym;
	
	/**
	 * \brief Ttype_sym_val type definition
	 * Note that efectively there's some kind of redundance:
	 * In TXXX_sym you already get the type, so Ttype_sym is
	 * (but only partially) redundant. But some redundancy
	 * some times make things less insane!
	 */
	typedef struct{
		union {
			Tvar_sym *normal;
			Tenum_sym *enumerated;
			Tarray_sym *array;
			Tfile_sym *file;
			Treg_sym *reg;
		} type_sym;
		Ttype_sym *type;
	}  Ttype_sym_val;
	
	/**
	 * \brief Tstruct_sym type definition
	 * A struct will be a complex var type
	 */
	typedef struct {
		Tid *name;
		Ttype_sym *type;
	} Tstruct_sym;
	
	/**
	 * \brief Tstruct_sym_val type definition
	 * A struct will be a complex var
	 */
	typedef struct {
		Tid *name;
		Ttype_sym_val *type;
	} Tstruct_sym;
	
	/**
	 * \brief Tstruct_sym_list type definition
	 */
	typedef struct {
		Tstruct_sym *actual;
		Tstruct_sym *next;
	} Tstruct_sym_list;
	
	/**
	 * \brief Tstruct_sym_val_list type definition
	 */
	typedef struct {
		Tstruct_sym_val *actual;
		Tstruct_sym_val *next;
	} Tstruct_sym_val_list;
	
	/**
	 * \brief Treg_type_sym type definition
	 */
	typedef struct {
		Tid *name;
		Tstruct_sym_list *list;
	} Treg_type_sym;
	
	/**
	 * \brief Treg_sym type definition
	 */
	typedef struct {
		Tid *name;
		Treg_type_sym *type;
		Tstruct_sym_val_list *store;
	} Treg_sym;
	
	/**
	 * \brief Treg_call type definition
	 * Note that this will store only a ultimate call to
	 * a register; myRegister.intArrayNM[x, y] should be
	 * stored as a Tvar_call (to an integer var) and not 
	 * as a Treg_call!
	 */
	typedef union {
		Tid *name;
		Treg_sym *symbol;
	} Treg_call;
	
	/**
	 * \brief expr_bool type definition
	 */
	typedef struct {
		union {
			Texpr_bool *expr_bool;
			Tvar_call *var_call;
			Tarray_call *array_call;
			Tmethod_call *method_call;
		} expr_bool;
		int *type;
	} Texpr_bool;
	
	/**
	 * \brief expr_bool_op type definition
	 */
	typedef struct {
		int *op;
		union{
			Texpr_bool *boolean;
			Texpr *left_expr;
		} left;
		union{
			Texpr_bool *boolean;
			Texpr *expr;
		} right;
	} Texpr_bool_op;
	
	/**
	 * \brief expr_op type definition
	 */
	typedef struct {
		int *op;
		Texpr *left;
		Texpr *right;
	} Texpr_op;
	
	/**
	 * \brief expr type definition
	 */
	typedef struct {
		int *type;
		union {
			Texpr *expr;
			Tvar_call *var_call;
			Tarray_call *array_call;
			Tmethod_call *method_call;
		} expr;
	} Texpr;
	
	/**
	 * \brief Tprogram type definition
	 */
	typedef struct {
		Tid *name;
		Tdeclarations_sym *declarations;
		Tsentence_list *sentences;
		Tlibrary *library;
	} Tprogram;
	 
	/**
	 * \brief Tlibrary type definition
	 */
	typedef struct {
		Tmethod_sym *actual;
		Tmethod_sym *next;
	} Tlibrary;
	
	/**
	 * \brief Tmethod_sym type definition
	 */
	typedef struct {
		Tid *name;
		Tinterface_sym *interface;
		Tdeclarations_sym *declarations;
		Tsentence_list *sentences;
		int *type;
	} Tmethod_sym;
	
	/**
	 * \brief Tinterface_sym type definition
	 * If this is an interface for a function then args_io
	 * would be NULL and args_out would be a sole arg, etc..
	 */
	typedef struct {
		Tstruct_sym_val_list *args_in, *args_out, *args_io;
	} Tinterface_sym;
	 
	/**
	 * \brief Tdeclarations_sym type definition
	 */
	typedef struct {
		Tstruct_sym_val_list *consts, *vars;
		Tstruct_sym_list *types;
	} Tdeclarations_sym;
	 
	/**
	 * \brief Tsentence_list type definition
	 */
	typedef struct {
		Tsentence *actual;
		Tsentence *next;
	} Tsentence_list;
	 
	/**
	 * \brief Tsentence type definition
	 */
	typedef struct {
		int *type;
		union {
			Tif_statement *if_statement;
			Tassign_statement *assign_statement;
			Tmult_assign_statement *mult_assign_statement;
			Twhile_loop *while_loop;
			Tfromto_loop *fromto_loop;
			Tmethod_call *method_call;
			Treserved_call *Treserved_call;
		} sentence;
	} Tsentence_list;
	 
	/**
	 * \brief Tif_statement type definition
	 */
	typedef struct {
		Texpr_bool *cond;
		Telif_statement_list *elif_statement_list;
		Tsentence_list *sentence_list, *else_sentence_list;
	} Tif_statement;
	 
	/**
	 * \brief Telif_statement_list type definition
	 */
	typedef struct {
		Telif_statement *actual;
		Telif_statement *next;
	} Telif_statement_list;
	 
	/**
	 * \brief Telif_statement type definition
	 */
	typedef struct {
		Texpr_bool *cond;
		Tsentence_list *sentence_list;
	} Telif_statement;
	 
	/**
	 * \brief Telif_statement type definition
	 */
	typedef struct {
		Texpr_bool *cond;
		Tsentence_list *sentence_list;
	} Telif_statement;
	 
	/**
	 * \brief Tassign_statement type definition
	 */
	typedef struct {
		Tstruct_sym_list *sym_list;
		Texpr *expr;
	} Tassign_statement;
	 
	/**
	 * \brief Texpr_list type definition
	 */
	typedef struct {
		Texpr *actual;
		Texpr *next;
	} Texpr_list;
	 
	/**
	 * \brief Tmult_assign_statement type definition
	 */
	typedef struct {
		Tstruct_sym_list *sym_list;
		Texpr_list *expr_list;
	} Tmult_assign_statement;
	
	/**
	 * \brief Twhile_loop type definition
	 */
	typedef struct {
		Texpr_bool *cond;
		Tsentence_list *sentence_list;
	} Twhile_loop;
	 
	/**
	 * \brief Tfromto_loop type definition
	 */
	typedef struct {
		Tassign_statement *assign_statement;
		int *int_val;
		Tsentence_list *sentence_list;
	} Tfromto_loop;
	 
	/**
	 * \brief Tmethod_call type definition
	 */
	typedef struct {
		Texpr_list *arg_list;
		union {
			Tid *name;
			Tmethod_sym *symbol;
		} function;
	} Tmethod_call;
	 
	/**
	 * \brief Treserved_call type definition
	 */
	typedef struct {
		Texpr_list *arg_list;
		union {
			Tid *name;
			void *(*function_ptr)();
		} function;
	} Treserved_call;
	
	/*
	 * List types to keep an eye in for sorting the list of its elements
	 * in order to apply quicksort and then binary search:
	 *  - Tstruct_sym_list
	 *  - Tstruct_sym_val_list
	 *  - Tlibrary
	 * And also the structures that directly use them:
	 *  - Treg_type_sym
	 *  - Treg_sym
	 *  - Tprogram
	 *  - Tinterface_sym
	 *  - Tdeclarations_sym
	 */
	 
	/****************************
	*     Vars declarations     *
	****************************/
	/**
	* \brief Abstract Tree
	*/
	
	Tprogram abstract_tree;
	
	/****************************
	*    Function prototypes    *
	****************************/
	/**
	 * \Brief Prototypes of the (TR)translator functions
	 */
	// program: 
	Tprogram *TRprogram(Tid *, Tdeclarations_sym *, Tsentence_list *, Tmethod_sym *); 
	// prog_header: 
	Tid *TRprog_header(char *);
	// library: 
	// 		NULL;  
	Tmethod_sym *TRlibrary(Tmethod_sym *, Tmethod_sym *); 
	// algorithm: 
	Tmethod_sym *TRalgorithm(Tid *, Tinterface_sym *, Tdeclarations_sym *, Tsentence_list *); 
	// function: 
	Tmethod_sym *TRfunction(Tinterface_sym *, Tdeclarations_sym *, Tsentence_list *); 
	// procedure: 
	Tmethod_sym *TRprocedure(Tinterface_sym *, Tdeclarations_sym *, Tsentence_list *); 
	// alg_header: 
	Tid *TRalg_header(char *);
	// func_header: 
	Tmethod_sym *TRfunc_header(char *, Tstruct_sym_val_list *, Tstruct_sym_val *); 
	// proc_header: 
	Tmethod_sym *TRproc_header(char *, Tstruct_sym_val_list *); 
	// interface_block: 
	// 		NULL;  
	Tinterface_sym *TRinterface_block_in(Tstruct_sym_val_list *, Tinterface_sym *); 
	Tinterface_sym *TRinterface_block_out(Tstruct_sym_val_list *, Tinterface_sym *); 
	// proc_arg: 
	// 		NULL;  
	Tinterface_sym *TRproc_arg_in(Tstruct_sym_val_list *); 
	Tinterface_sym *TRproc_arg_out(Tstruct_sym_val_list *); 
	Tinterface_sym *TRproc_arg_inout(Tstruct_sym_val_list *); 
	// proc_arg_list: 
	Tinterface_sym *TRproc_arg_list(Tinterface_sym *, Tinterface_sym *);  
// 	Tinterface_sym *TRproc_arg_list(NULL, Tinterface_sym *); 
	// in_arg_list: 
	// 		NULL;  
	Tstruct_sym_val_list *TRin_arg_list(Tstruct_sym_val_list *, Tstruct_sym_val *); 
// 	Tstruct_sym_val_list *TRin_arg_list(NULL, Tstruct_sym_val *); 
	// out_arg_list: 
	// 		NULL;  
	Tstruct_sym_val_list *TRout_arg_list(Tstruct_sym_val_list *, Tstruct_sym_val *); 
// 	Tstruct_sym_val_list *TRout_arg_list(NULL, Tstruct_sym_val *); 
	// inout_arg_list: 
	// 		NULL;  
	Tstruct_sym_val_list *TRinout_arg_list(Tstruct_sym_val_list *, Tstruct_sym_val *); 
// 	Tstruct_sym_val_list *TRinout_arg_list(NULL, Tstruct_sym_val *); 
	// in_var_dcl: 
// 	Tstruct_sym_val *TRin_var_dcl(Tid_list *, char *, NULL, NULL); 
// 	Tstruct_sym_val *TRin_var_dcl(Tid_list *, char *, char *, NULL); 
	Tstruct_sym_val *TRin_var_dcl(Tid_list *, char *, char *, char *); 
	Tstruct_sym_val *TRin_var_dcl_array(Tid_list *, Tint_val_list *, char *); 
	// out_var_dcl: 
// 	Tstruct_sym_val *TRout_var_dcl(Tid_list *, char *, NULL, NULL); 
// 	Tstruct_sym_val *TRout_var_dcl(Tid_list *, char *, char *, NULL); 
	Tstruct_sym_val *TRout_var_dcl(Tid_list *, char *, char *, char *); 
	Tstruct_sym_val *TRout_varl_dcl_array(Tid_list *, Tint_val_list *, char *); 
	// inout_var_dcl: 
// 	Tstruct_sym_val *TRinout_var_dcl(Tid_list *, char *, NULL, NULL); 
// 	Tstruct_sym_val *TRinout_var_dcl(Tid_list *, char *, char *, NULL); 
	Tstruct_sym_val *TRinout_var_dcl(Tid_list *, char *, char *, char *); 
	Tstruct_sym_val *TRinout_var_dcl_array(Tid_list *, Tint_val_list *, char *); 
	// id_list: 
	Tid_list *TRid_list(Tid_list *, char *); 
// 	Tid_list *TRid_list(NULL, char *); 
	// int_val_list: 
	Tint_val_list *TRint_val_list(Tint_val_list *, Tint_id_val *); 
// 	Tint_val_list *TRint_val_list(NULL, Tint_id_val *); 
	// int_id_val: 
	Tint_id_val *TRint_id_val_int(char *);
	Tint_id_val *TRint_id_val_id(char *); 
	// declarations_block: 
	Tdeclarations_sym *TRdeclarations_block($1, $2, $3); 
	// consts_block: 
	// 		NULL;  
	// const_dcl_list: 
	// 		NULL;  
	Tstruct_sym_val_list *TRconst_dcl_list_bool($1, $2, $4); 
	Tstruct_sym_val_list *TRconst_dcl_list_int($1, $2, $4); 
	Tstruct_sym_val_list *TRconst_dcl_list_float($1, $2, $4); 
	Tstruct_sym_val_list *TRconst_dcl_list_char($1, $2, $4); 
	Tstruct_sym_val_list *TRconst_dcl_list_str($1, $2, $4); 
	Tstruct_sym_val_list *TRconst_dcl_list_reg($1, $2, $4); 
	// types_block: 
	// 		NULL;  
	// types_dcl_list: 
	// 		NULL;  
	Tstruct_sym_list *TRtypes_dcl_list_enum($1, $2, $5); 
	Tstruct_sym_list *TRtypes_dcl_list_var($1, $2, $4, NULL); 
	Tstruct_sym_list *TRtypes_dcl_list_var($1, $2, $4, $6); 
	Tstruct_sym_list *TRtypes_dcl_list_array($1, $2, $5, $7); 
	Tstruct_sym_list *TRtypes_dcl_list_reg($1, $2, $4); 
	// str_list: 
	Tstr_list *TRstr_list($1, $3); 
	Tstr_list *TRlist(NULL, $1); 
	// vars_block: 
	// 		NULL;  
	// vars_dcl: 
	// 		NULL;  
	Tstruct_sym_val_list *TRvars_dcl_var($1, $2, $4, NULL); 
	Tstruct_sym_val_list *TRvars_dcl_var($1, $2, $4, $6); 
	Tstruct_sym_val_list *TRvars_dcl_array($1, $2, $5, $7); 
	Tstruct_sym_val_list *TRvars_dcl_reg($1, $2, $4); 
	// register: 
	Ttype_sym *TRregister($3); 
	Ttype_sym *TRregister($4); 
	// sentence_list: 
	// 		NULL;  
	Tsentence_list *TRsentence_list($1); 
	// 		NULL;  
	// sentence: 
	Tsentence *TRsentence_if($1); 
	Tsentence *TRsentence_assign($1); 
	Tsentence *TRsentence_mult($1); 
	Tsentence *TRsentence_io($1); 
	Tsentence *TRsentence_while($1); 
	Tsentence *TRsentence_fromto($1); 
	Tsentence *TRsentence_func($1); 
	Tsentence *TRsentence_proc($1); 
	// if_statement: 
	Tsentence *TRif_statement($2, $4, $5, $9); 
	Tsentence *TRif_statement($2, $4, NULL, $8); 
	// elif_statement: 
	Telif_statement *TRelif_statement($2, $4); 
	// elif_statement_list: 
	Telif_statement_list *TRelif_statement_list($1, $2); 
	Telif_statement_list *TRelif_statement_list(NULL, $1); 
	// assign_statement: 
	Tsentence *TRassign_statement_assign($1, $3); 
	Tsentence *TRassign_statement_expr($1, $3); 
	/* TODO: Tsentence *TRassign_statement_mult($1, $3); 
	// mult_assign_list: 
			TRmult_assign_list($1, $3); 
			TRmult_assign_list_expr($1, $3); 
			TRmult_assign_list_expr($1, NULL); 
			TRmult_assign_list($1, NULL);  */
	// mult_assign_statement: 
	Tsentence *TRmult_assign_statement($1, $3);
	// output_input_statement: 
	Tsentence *TRoutput_input_statement($1, $2); 
	// while_loop: 
	Tsentence *TRwhile_loop($2, $4); 
	// fromto_assign_statement: 
	Tassign_statement *TRfromto_assign_statement($2, $4, $6); 
	// fromto_loop: 
	Tsentence *TRfromto_loop($2, $4, $6); 
	// function_call: 
	Tsentence *TRfunction_call($1, $3); 
	// variable_call: 
	Tsentence *TRvariable_call($1, $2); 
	Tsentence *TRvariable_call($1, NULL); 
	// struct_call: 
	Tsentence *TRstruct_call($1, $3); 
	Tsentence *TRstruct_call(NULL, $1); 
	// variable_list: 
	Tvar_call *TRvariable_list($1, $3); 
	Tvar_call *TRvariable_list(NULL, $1); 
	// procedure_call: 
	Tsentence *TRprocedure_call($1, $3); 
	// expr_list: 
	// 		NULL;  
	Texpr_list *TRexpr_list($1, $3); 
	Texpr_list *TRexpr_list(NULL, $1); 
	// expr_bool: 
	Texpr_bool *TRexpr_bool_val($1); 
	Texpr_bool *TRexpr_bool_struct($1); 
	Texpr_bool *TRexpr_bool($1, $2, NULL); 
	Texpr_bool *TRexpr_bool($2, $1, $3); 
	Texpr_bool *TRexpr_bool($2, $1, $3); 
	Texpr_bool *TRexpr_bool($2, $1, $3); 
	Texpr_bool *TRexpr_bool($2, $1, $3); 
	Texpr_bool *TRexpr_bool($2, $1, $3); 
	Texpr_bool *TRexpr_bool($2, $1, $3); 
	Texpr_bool *TRexpr_bool($2, $1, $3); 
	Texpr_bool *TRexpr_bool($2, $1, $3); 
	Texpr_bool *TRexpr_bool_fcall($1); 
	// expr: 
	Texpr *TRexpr_int($1); 
	Texpr *TRexpr_expr_bool($1); 
	Texpr *TRexpr_float($1); 
	Texpr *TRexpr_str($1); 
	Texpr *TRexpr_struct($1); 
	Texpr *TRexpr($2, $1, $3); 
	Texpr *TRexpr($2, $1, $3); 
	Texpr *TRexpr($2, $1, $3); 
	Texpr *TRexpr($2, $1, $3); 
	Texpr *TRexpr($2, $1, $3); 
	Texpr *TRexpr($2, $1, $3); 
	Texpr *TRexpr($1, $2, NULL); 
	Texpr *TRexpr_fcall($1); 
	#endif
