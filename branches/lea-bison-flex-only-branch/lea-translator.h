/**
 * \file lea-translator.h
 * \brief Translator to Abstract Tree header
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

#ifndef LEA_TRANSLATOR_H
	#define LEA_TRANSLATOR_H
	
	#include <stdlib.h>
	#include <string.h>
	
	/**
	 * \brief defines of (V)value type and their assigned values
	 * These are the possible values used in the variables "char *type;"
	 * used across the structures defined bellow
	 */
	#define Vint_val				0
	#define Vbool_val				1
	#define Vfloat_val				2
	#define Vchar_val				3
	#define Vstr_val				4
	#define Vstr_val				5
	#define Vfile_val				6
	#define Vconst_int_val			7
	#define Vconst_bool_val			8
	#define Vconst_float_val		9
	#define Vconst_char_val			10
	#define Vconst_str_val			11
	#define Vconst_file_val			12
	#define Vintern_int_val			13
	#define Vintern_bool_val		14
	#define Vintern_float_val		15
	#define Vintern_char_val		16
	#define Vintern_str_val			17
	#define Vintern_file_val		18
	
	#define Vvar_call				19
	#define Varray_call				20
	#define Vstruct_call			21
	
	#define Vstream					22
	#define Vinput_stream			23
	#define Voutput_stream			24
	#define Vio_stream				25
	#define Vfile					26
	#define Vinput_file				27
	#define Voutput_file			28
	#define Vio_file				29
	
	#define Venum_type				30
	#define Varray_type				31
	#define Vvar_type				32
	#define Vreg_type				33
	#define Vintern_other_type		34
	#define Vintern_enum_type		35
	#define Vintern_array_type		36
	#define Vintern_var_type		37
	#define Vintern_reg_type		38
	#define Vintern_other_type		39
	
	#define OPnot					40
	#define OPand					41
	#define OPor					42
	#define OPeq					43
	#define OPless					44
	#define OPgreater				45
	#define OPle					46
	#define OPge					47
	
	#define OPsum					48
	#define OPsub					49
	#define OPmult					50
	#define OPdiv					51
	#define OPmod					52
	#define OPexp					53
	
	#define Valg					54
	#define Vfunc					55
	#define Vproc					56
	
	#define Vif_statement			57
	#define Vassign_statement		58
	#define Vmult_assign_statement	59
	#define Vwhile_loop				60
	#define Vfromto_loop			61
	#define Vmethod_call			62
	#define Vreserved_call			63
	
	#define Valgorithm				64
	#define Vfunction				65
	#define Vprocedure				66
	
	#define OPexpr					67
	#define OPexpr_bool				68
	#define OPop					69
	#define OPvar_call				70
	#define OParray_call			71
	#define OPmethod_call			72
	#define OPreserved_call			73
	
	/****************************
	*     Types definitions     *
	****************************/
	/**
	 * \brief Definition of all the (T)types used in the translator
	 *
	 * General notes:
	 *
	 *  - Linked lists end when the *next pointer is set to NULL
	 *
	 *  - If there are a fixed number of elements in an array, then
	 *    we use a dynamic pointer to store all the elements and a
	 *    pointer to the last element to check array limits easily.
	 *
	 *  - An internal type is a custom type used internally or
	 *    used by the user but not declared implicitly
	 *
	 *  - Internal types never have a name (ie. char*name=NULL;)
	 *
	 *  - There's some redundancy in these types. But it's benign ;-)
	 */
	
	/**
	 * \brief bool type definition
	 */
	typedef enum {false, true} bool;
	
	/**
	 * \brief Ttype type definition
	 * It contains all the essential types of information
	 *
	 * In this structure char *type can be:
	 *  -  V(|const_|intern_)int_val (for storage.int_val)
	 *  -  V(|const_|intern_)bool_val (for storage.bool_val)
	 *  -  V(|const_|intern_)float_val (for storage.float_val)
	 *  -  V(|const_|intern_)str_val (for storage.str_val)
	 *  -  V(|const_|intern_)file_val (for storage.file)
	 */
	typedef struct
		union {
			int *int_val;
			bool *bool_val;
			float *float_val;
			char *char_val;
			char *str_val;
			FILE *file;
		} storage;
		char *type;
	} Ttype;
	
	/**
	 * \brief Tstr_val type definition
	 * This type is essentially a char pointer but it also indicates the length
	 * of the string (this practice sometimes makes faster the use strings)
	 */
	typedef struct {
		unsigned int *length;
		char *val;
	} Tstr_val;
	
	/**
	 * \brief Tid_list type definition
	 */
	typedef struct {
		char *actual;
		Tid_list *next;
	} Tid_list;
	
	/**
	 * \brief Tint_id_val type definition
	 * This type is meant to be used when you need an integer value that can be
	 * obtained either by an existing integer variable/constant or entered directly.
	 *
	 * The best example of its usefulness is Tarray_dimensions, which it was
	 * developed for.
	 *
	 * In this structure char *type can be:
	 *  -  Vvar_call (for val.var_call)
	 *  -  Vint_val (for val.int_val)
	 */
	typedef struct {
		union {
			Tvar_call *var_call;
			int *int_val;
		} val;
		char *type;
	} Tint_id_val;
	
	/**
	 * \brief Tstr_list type definition
	 */
	typedef struct {
		Tstr_val *actual;
		Tstr_list *next;
	} Tstr_list;
	
	/**
	 * \brief Tint_id_val_list type definition
	 * This type is meant to be used when you need a list of integer values 
	 * that can be obtained either by an existing integer variable/constant
	 * or entered directly.
	 */
	typedef struct {
		Tint_id_val *value;
		Tint_id_val_list *next;
	} Tint_id_val_list;
	
	/**
	 * \brief Tvar_call type definition
	 * Note that constants and vars are both called via this type
	 */
	typedef Tvar_sym Tvar_call;
	
	/**
	 * \brief Tvar_call_list type definition
	 * Note that constants and vars are both called via this type list
	 */
	typedef struct {
		Tvar_call *actual;
		Tvar_call_list *next;
	} Tvar_call_list;
	
	/**
	 * \brief Tarray_call type definition
	 */
	typedef Tarray_sym Tarray_call;
	
	/**
	 * \brief Tvar_sym type definition
	 * Symbols are meant to be part of the symbol table
	 */
	typedef struct {
		char *name;
		Ttype *storage;
	} Tvar_sym;
	
	/**
	 * \brief Tenum_element type definition
	 * Used in Tenum_type to identify enum elements with an integer value
	 * used only internaly to speed up the enumerated type
	 */
	typedef struct {
		char *name;
		char *int_val;
	} Tenum_element;
	
	/**
	 * \brief Tenum_type type definition
	 * Note that as the elements of an enumerated type doesn't ever change
	 * we've defined *storage as a "dynamic" array instead of as a linked list  
	 */
	typedef struct {
		char *name;
		Tenum_element *elements, *last_element;
	} Tenum_type;
	
	/**
	 * \brief Tenum_sym type definition
	 * Symbols are meant to be part of the symbol table
	 */
	typedef struct {
		char *name;
		Tenum_element *element;
		Tenum_type *type_sym;
	} Tenum_sym;
	
	/**
	 * \brief Tarray_type type definition
	 */
	typedef struct {
		char *name;
		unsigned int *dimensions;
		Tother_type *type_sym;
	} Tarray_type;
	
	/**
	 * \brief Tarray_sym type definition
	 * Symbols are meant to be part of the symbol table
	 * Note that whenever we have fixed number of elements, we stop using linked lists
	 * and use pointers (that can be properly used as "dynamic" arrays), like in
	 * Tother_sym *elements;.
	 */
	typedef struct {
		char *name; 
		// Array of pointers  (containing as many elements as the first dimension
		// does) to sub-arrays or other types:
		Tarray_type *type_sym; 
		 //this is a bit redundant 'cause this info also is at every element of *elements in Tarray_sym:
		Tother_sym *elements, *last_element;
	} Tarray_sym;
	
	/**
	 * \brief Tfile_type type definition
	 * Note that files and streams are used internally in this
	 * implementation indistinctively
	 */
	typedef struct {
		char *name;
		Tother_type *type_sym;
	} Tfile_type;
	
	/**
	 * \brief Tfile_sym type definition
	 * Symbols are meant to be part of the symbol table
	 * WARNING: Check that we don't have files of registers that
	 * contain files, for $DEITY's sake!
	 */
	typedef struct {
		char *name;
		FILE *file;
		Tfile_type *type_sym;
	} Tfile_sym;
	
	/**
	 * \brief Tother_type type definition
	 * In this structure char *type can be:
	 *  -  V(|intern_)other_type (for kind.other)
	 *  -  V(|intern_)enum_type (for kind.enumerated)
	 *  -  V(|intern_)array_type (for kind.array)
	 *  -  V(|intern_)file_type (for kind.file)
	 *  -  V(|intern_)reg_type (for kind.reg)
	 */
	typedef struct {
		char *name;
		union {
			Ttype *other;
			Tenum_type *enumerated;
			Tarray_type *array;
			Tfile_type *file;
			Treg_type *reg;
		} kind;
		char *type;
	} Tother_type;
	
	/**
	 * \brief Tother_sym type definition
	 * In this structure char *type can be:
	 *  -  Vother_type (for symbol.other)
	 *  -  Venum_type (for symbol.enumerated)
	 *  -  Varray_type (for symbol.array)
	 *  -  Vfile_type (for symbol.file)
	 *  -  Vreg_type (for symbol.reg)
	 *
	 * Note that efectively there's some kind of redundance:
	 * In TXXX_sym you already get the type, so Tother_type is
	 * (but only partially) redundant. But some redundancy
	 * some times make things less insane!
	 */
	typedef struct{
		char *name;
		union {
			Tvar_sym *other;
			Tenum_sym *enumerated;
			Tarray_sym *array;
			Tfile_sym *file;
			Treg_sym *reg;
		} symbol;
		char *type;
		Tother_type *type;
	}  Tother_sym; 
	
	/**
	 * \brief Tother_type_list type definition
	 */
	typedef struct {
		Tother_type *actual;
		Tother_type_list *next;
	} Tother_type_list;
	
	/**
	 * \brief Tother_sym_list type definition
	 */
	typedef struct {
		Tother_sym *actual;
		Tother_sym_list *next;
	} Tother_sym_list;
	
	/**
	 * \brief Treg_type_sym type definition
	 */
	typedef struct {
		char *name;
		Tother_type_list *list;
	} Treg_type_sym;
	
	/**
	 * \brief Treg_sym type definition
	 */
	typedef struct {
		char *name;
		Treg_type_sym *type;
		Tother_sym_list *store;
	} Treg_sym;
	
	/**
	 * \brief Treg_call type definition
	 * Note that this will store only a ultimate call to
	 * a register; myRegister.intArrayNM[x, y] should be
	 * stored as a Tvar_call (to an integer var) and not 
	 * as a Treg_call!
	 */
	typedef union {
		char *name;
		Treg_sym *symbol;
	} Treg_call;
	
	/**
	 * \brief expr_bool type definition
	 * In this structure char *type can be:
	 *  -  OPexpr_bool (for expr_bool.expr_bool)
	 *  -  OPvar_call (for expr_bool.var_call)
	 *  -  OParray_call (for expr_bool.array_call)
	 *  -  OPmethod_call (for expr_bool.method_call)
	 */
	typedef struct {
		union {
			Texpr_bool_op *expr_bool;
			Tvar_call *var_call;
			Tarray_call *array_call;
			Tmethod_call *method_call;
		} expr_bool;
		char *type;
	} Texpr_bool;
	
	/**
	 * \brief expr_bool_op type definition
	 * In this special case, we use a variable char *op; that implitily
	 * specifies which type will be used in left and right vars:
	 *  - OPnot (for right.expr_bool = NULL, left.expr_bool)
	 *  - OPeq/OPless/OPgreater/OPle/OPge (for right.expr, left.expr)
	 *  - OPand/OPor (for right.expr_bool, left.expr_bool)
	 */
	typedef struct {
		char *op;
		union{
			Texpr_bool *expr_bool;
			Texpr *expr;
		} left;
		union{
			Texpr_bool *expr_bool;
			Texpr *expr;
		} right;
	} Texpr_bool_op;
	
	/**
	 * \brief expr_op type definitionition
	 * In this struct char *op; can be:
	 *  - OPsum/Opsub/OPmult/OPdiv/OPmod/OPexp
	 */
	typedef struct {
		char *op;
		Texpr *left;
		Texpr *right;
	} Texpr_op;
	
	/**
	 * \brief expr type definition
	 * In this structure char *type can be:
	 *  -  OPexpr_bool (for expr.expr_bool)
	 *  -  OPexpr (for expr.expr)
	 *  -  OPvar_call (for expr.var_call)
	 *  -  OParray_call (for expr.array_call)
	 *  -  OPmethod_call (for expr.method_call)
	 */
	typedef struct {
		char *type;
		union {
			Texpr_bool_op *expr_bool;
			Texpr_op *expr;
			Tvar_call *var_call;
			Tarray_call *array_call;
			Tmethod_call *method_call;
		} expr;
	} Texpr;
	
	/**
	 * \brief Tprogram type definition
	 */
	typedef struct {
		char *name;
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
	 * In this structure char *type can be:
	 *  - OPalg/OPfunc/OPproc
	 */
	typedef struct {
		char *name;
		Tinterface_sym *interface;
		Tdeclarations_sym *declarations;
		Tsentence_list *sentences;
		char *type;
	} Tmethod_sym;
	
	/**
	 * \brief Tinterface_sym type definition
	 * If this is an interface for a function then args_io
	 * would be NULL and args_out would be a sole arg, etc..
	 */
	typedef struct {
		Tother_sym_list *args_in, *args_out, *args_io;
	} Tinterface_sym;
	 
	/**
	 * \brief Tdeclarations_sym type definition
	 */
	typedef struct {
		Tother_sym_list *consts, *vars;
		Tother_type_list *types;
	} Tdeclarations_sym;
	 
	/**
	 * \brief Tsentence_list type definition
	 */
	typedef struct {
		Tsentence *actual;
		Tsentence_list *next;
	} Tsentence_list;
	 
	/**
	 * \brief Tsentence type definition
	 * In this structure char *type can be:
	 *  -  Vif_statement (for sentence.if_statement)
	 *  -  Vassign_statement (for sentence.assign_statement)
	 *  -  Vmult_assign_statement (for sentence.mult_assign_statement)
	 *  -  Vwhile_loop (for sentence.while_loop)
	 *  -  Vfromto_loop (for sentence.fromto_loop)
	 *  -  Vmethod_call (for sentence.method_call)
	 *  -  Vreserved_call (for sentence.Treserved_call)
	 */
	typedef struct {
		char *type;
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
		Telif_statement_list *next;
	} Telif_statement_list;
	 
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
		Tother_sym_list *sym_list;
		Texpr *expr;
	} Tassign_statement;
	 
	/**
	 * \brief Texpr_list type definition
	 */
	typedef struct {
		Texpr *actual;
		Texpr_list *next;
	} Texpr_list;
	 
	/**
	 * \brief Tmult_assign_statement type definition
	 */
	typedef struct {
		Tother_sym_list *sym_list;
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
			char *name;
			Tmethod_sym *symbol;
		} function;
	} Tmethod_call;
	 
	/**
	 * \brief Treserved_call type definition
	 */
	typedef struct {
		Texpr_list *arg_list;
		union {
			char *name;
			void *(*function_ptr)();
		} function;
	} Treserved_call;
	
	/*
	 * List types to keep an eye in for sorting the list of its elements
	 * in order to apply optimizstion techniques (B trees, binary trees,
	 * hash tables, linked lists..):
	 *  - Tother_type_list
	 *  - Tother_sym_list
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
	Tprogram *TRprogram(char *, Tdeclarations_sym *, Tsentence_list *, Tmethod_sym *); 
	// library: 
	// 		NULL;  
	Tmethod_sym *TRlibrary(Tmethod_sym *, Tmethod_sym *); 
	// algorithm: 
	Tmethod_sym *TRalgorithm(char *, Tinterface_sym *, Tdeclarations_sym *, Tsentence_list *); 
	// function: 
	Tmethod_sym *TRfunction(Tinterface_sym *, Tdeclarations_sym *, Tsentence_list *); 
	// procedure: 
	Tmethod_sym *TRprocedure(Tinterface_sym *, Tdeclarations_sym *, Tsentence_list *); 
	// func_header: 
	Tmethod_sym *TRfunc_header(char *, Tother_sym_list *, Tother_sym *); 
	// proc_header: 
	Tmethod_sym *TRproc_header(char *, Tother_sym_list *); 
	// interface_block: 
	// 		NULL;  
	Tinterface_sym *TRinterface_block_in(Tother_sym_list *, Tinterface_sym *); 
	Tinterface_sym *TRinterface_block_out(Tother_sym_list *, Tinterface_sym *); 
	// proc_arg: 
	// 		NULL;  
	Tinterface_sym *TRproc_arg_in(Tother_sym_list *); 
	Tinterface_sym *TRproc_arg_out(Tother_sym_list *); 
	Tinterface_sym *TRproc_arg_inout(Tother_sym_list *); 
	// proc_arg_list: 
	Tinterface_sym *TRproc_arg_list(Tinterface_sym *, Tinterface_sym *);  
// 	Tinterface_sym *TRproc_arg_list(NULL, Tinterface_sym *); 
	// in_arg_list: 
	// 		NULL;  
	Tother_sym_list *TRin_arg_list(Tother_sym_list *, Tother_sym *); 
// 	Tother_sym_list *TRin_arg_list(NULL, Tother_sym *); 
	// out_arg_list: 
	// 		NULL;  
	Tother_sym_list *TRout_arg_list(Tother_sym_list *, Tother_sym *); 
// 	Tother_sym_list *TRout_arg_list(NULL, Tother_sym *); 
	// inout_arg_list: 
	// 		NULL;  
	Tother_sym_list *TRinout_arg_list(Tother_sym_list *, Tother_sym *); 
// 	Tother_sym_list *TRinout_arg_list(NULL, Tother_sym *); 
	// in_var_dcl: 
// 	Tother_sym *TRin_var_dcl(Tid_list *, char *, NULL, NULL); 
// 	Tother_sym *TRin_var_dcl(Tid_list *, char *, char *, NULL); 
	Tother_sym *TRin_var_dcl(Tid_list *, char *, char *, char *); 
	Tother_sym *TRin_var_dcl_array(Tid_list *, Tint_id_val_list *, char *); 
	// out_var_dcl: 
// 	Tother_sym *TRout_var_dcl(Tid_list *, char *, NULL, NULL); 
// 	Tother_sym *TRout_var_dcl(Tid_list *, char *, char *, NULL); 
	Tother_sym *TRout_var_dcl(Tid_list *, char *, char *, char *); 
	Tother_sym *TRout_var_dcl_array(Tid_list *, Tint_id_val_list *, char *); 
	// inout_var_dcl: 
// 	Tother_sym *TRinout_var_dcl(Tid_list *, char *, NULL, NULL); 
// 	Tother_sym *TRinout_var_dcl(Tid_list *, char *, char *, NULL); 
	Tother_sym *TRinout_var_dcl(Tid_list *, char *, char *, char *); 
	Tother_sym *TRinout_var_dcl_array(Tid_list *, Tint_id_val_list *, char *); 
	// id_list: 
	Tid_list *TRid_list(Tid_list *, char *); 
// 	Tid_list *TRid_list(NULL, char *); 
	// int_val_list: 
	Tint_id_val_list *TRint_val_list(Tint_id_val_list *, Tint_id_val *); 
// 	Tint_id_val_list *TRint_val_list(NULL, Tint_id_val *); 
	// int_id_val: 
	Tint_id_val *TRint_id_val_int(int *);
	Tint_id_val *TRint_id_val_id(char *); 
	// declarations_block: 
	Tdeclarations_sym *TRdeclarations_block(Tother_sym_list *, Tother_type_list *, Tother_sym_list *); 
	// consts_block: 
	// 		NULL;  
	// const_dcl_list: 
	// 		NULL;  
	Tother_sym_list *TRconst_dcl_list_bool(Tother_sym_list *, Tid_list *, bool *); 
	Tother_sym_list *TRconst_dcl_list_int(Tother_sym_list *, Tid_list *, int *); 
	Tother_sym_list *TRconst_dcl_list_float(Tother_sym_list *, Tid_list *, float *); 
	Tother_sym_list *TRconst_dcl_list_char(Tother_sym_list *, Tid_list *, char *); 
	Tother_sym_list *TRconst_dcl_list_str(Tother_sym_list *, Tid_list *, char *); 
	Tother_sym_list *TRconst_dcl_list_reg(Tother_sym_list *, Tid_list *, Tother_type *); 
	// types_block: 
	// 		NULL;  
	// types_dcl_list: 
	// 		NULL;  
	Tother_type_list *TRtypes_dcl_list_enum(Tother_type_list *, Tid_list *, Tstr_list *); 
// 	Tother_type_list *TRtypes_dcl_list_var(Tother_type_list *, Tid_list *, char *, NULL); 
	Tother_type_list *TRtypes_dcl_list_var(Tother_type_list *, Tid_list *, char *, char *); 
	Tother_type_list *TRtypes_dcl_list_array(Tother_type_list *, Tid_list *, Tint_id_val_list *, char *); 
	Tother_type_list *TRtypes_dcl_list_reg(Tother_type_list *, Tid_list *, Tother_type *); 
	// str_list: 
	Tstr_list *TRstr_list(Tstr_list *, char *); 
// 	Tstr_list *TRstr_list(NULL, char *); 
	// vars_block: 
	// 		NULL;  
	// vars_dcl: 
	// 		NULL;  
// 	Tother_sym_list *TRvars_dcl_var(Tother_sym_list *, Tid_list *, char *, NULL); 
	Tother_sym_list *TRvars_dcl_var(Tother_sym_list *, Tid_list *, char *, char *); 
	Tother_sym_list *TRvars_dcl_array(Tother_sym_list *, Tid_list *, Tint_id_val_list *, char *); 
	Tother_sym_list *TRvars_dcl_reg(Tother_sym_list *, Tid_list *, Tother_type *); 
	// register: 
// 	Tother_type *TRregister(Tother_sym_list *); 
	Tother_type *TRregister(Tother_sym_list *); 
	// sentence_list: 
	// 		NULL;  
	Tsentence_list *TRsentence_list(Tsentence_list *, Tsentence *); 
	// 		NULL;  
	// if_statement: 
	Tsentence *TRif_statement(Texpr_bool *, Tsentence_list *, Telif_statement_list *, Tsentence_list *); 
// 	Tsentence *TRif_statement(Texpr_bool *, Tsentence_list *, NULL, Tsentence_list *); 
	// elif_statement: 
	Telif_statement *TRelif_statement(Texpr_bool *, Tsentence_list *); 
	// elif_statement_list: 
	Telif_statement_list *TRelif_statement_list(Telif_statement_list *, Telif_statement *); 
// 	Telif_statement_list *TRelif_statement_list(NULL, Telif_statement *); 
	// assign_statement: 
	Tsentence *TRassign_statement_assign(Tsentence *, Tsentence *); 
	Tsentence *TRassign_statement_expr(Tsentence *, Texpr *); 
	/* TODO: Tsentence *TRassign_statement_mult($1, $3); 
	// mult_assign_list: 
			TRmult_assign_list($1, $3); 
			TRmult_assign_list_expr($1, $3); 
			TRmult_assign_list_expr($1, NULL); 
			TRmult_assign_list($1, NULL);  */
	// mult_assign_statement: 
	Tsentence *TRmult_assign_statement(Tvar_call_list *, Texpr_list *);
	// output_input_statement: 
	Tsentence *TRoutput_input_statement(char *, Texpr_list *); 
	// while_loop: 
	Tsentence *TRwhile_loop(Texpr_bool *, Tsentence_list *); 
	// fromto_assign_statement: 
	Tassign_statement *TRfromto_assign_statement(Tsentence *, Texpr *); 
	// fromto_loop: 
	Tsentence *TRfromto_loop(Tassign_statement *, Texpr *, Tsentence_list *); 
	// TODO: is it correct to set this as  Tsentence *? function_call: 
	Tsentence *TRfunction_call(char *, Texpr_list *); 
	// TODO: is it correct to set this as  Tsentence *? variable_call: 
	Tsentence *TRvariable_call(char *, Texpr_list *); 
// 	Tsentence *TRvariable_call($1, Texpr_list *); 
	// TODO: is it correct to set this as  Tsentence *? struct_call: 
	Tsentence *TRstruct_call(Tsentence *, Tsentence *); 
// 	Tsentence *TRstruct_call(NULL, Tsentence *); 
	// variable_list: 
	Tvar_call_list *TRvariable_list(Tvar_call_list *, Tvar_call *); 
// 	Tvar_call_list *TRvariable_list(NULL, Tvar_call *); 
	// procedure_call: 
	Tsentence *TRprocedure_call(char *, Texpr_list *); 
	// expr_list: 
	// 		NULL;  
	Texpr_list *TRexpr_list(Texpr_list *, Texpr *); 
// 	Texpr_list *TRexpr_list(NULL, Texpr *); 
	// expr_bool: 
	Texpr_bool *TRexpr_bool_val(bool *); 
	Texpr_bool *TRexpr_bool_struct(Tsentence *); 
// 	Texpr_bool *TRexpr_bool(char, Texpr_bool *, NULL); 
	Texpr_bool *TRexpr_bool(char, Texpr_bool *, Texpr_bool *); 
// 	Texpr_bool *TRexpr_bool(char, Texpr_bool *, Texpr_bool *); 
// 	Texpr_bool *TRexpr_bool(char, Texpr_bool *, Texpr_bool *); 
// 	Texpr_bool *TRexpr_bool(char, Texpr_bool *, Texpr_bool *); 
// 	Texpr_bool *TRexpr_bool(char, Texpr_bool *, Texpr_bool *); 
// 	Texpr_bool *TRexpr_bool(char, Texpr_bool *, Texpr_bool *); 
// 	Texpr_bool *TRexpr_bool(char, Texpr_bool *, Texpr_bool *); 
// 	Texpr_bool *TRexpr_bool(char, Texpr_bool *, Texpr_bool *); 
	Texpr_bool *TRexpr_bool_fcall(Tsentence *); 
	// expr: 
	Texpr *TRexpr_int(int *); 
	Texpr *TRexpr_expr_bool(bool *); 
	Texpr *TRexpr_float(float *); 
	Texpr *TRexpr_str(char *); 
	Texpr *TRexpr_struct(Tsentence *); 
	Texpr *TRexpr(char, Texpr *, Texpr *); 
// 	Texpr *TRexpr(char, Texpr *, Texpr *); 
// 	Texpr *TRexpr(char, Texpr *, Texpr *); 
// 	Texpr *TRexpr(char, Texpr *, Texpr *); 
// 	Texpr *TRexpr(char, Texpr *, Texpr *); 
// 	Texpr *TRexpr(char, Texpr *, Texpr *); 
// 	Texpr *TRexpr(char, Texpr *, NULL); 
	Texpr *TRexpr_fcall(Tsentence *); 
	#endif
