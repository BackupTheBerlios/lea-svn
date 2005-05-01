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
	#include <stdio.h>
	#include "symbol-table.h"
	// Number of list elements in symbol tables. *Should* be prime
	#define PRIME 101
	
	/**
	 * \brief defines of (V)value type and their assigned values
	 * These are the possible values used in the variables "char *type;"
	 * used across the structures defined bellow
	 */
	#define Vint_val				1
	#define Vbool_val				2
	#define Vfloat_val				3
	#define Vchar_val				4
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
	
	#define OPnot					39
	#define OPand					40
	#define OPor					41
	#define OPeq					42
	#define OPless					43
	#define OPgreater				44
	#define OPle					45
	#define OPge					46
	#define OPne					47
	
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
	#define OPid_call				72
	#define OPmethod_call			73
	#define OPreserved_call			74
	#define OPreg_call				75
	
	#define Vreg_type_const_dcl		76
	#define Vreg_type_types_dcl		77
	#define Vreg_type_vars_dcl		78
	
	/****************************
	*     Types definitions     *
	****************************/
	
	/* HACK:
	 * These structures types are used the ones in the others
	 * and the compiler doesn't handle very well dependencies
	 * among them when structure types are declared directly,
	 * so to circumvent the problem we separate the type definitions
	 * and the structure definitions.
	 */
	typedef struct Tother_type Tother_type;
	typedef struct Tother_sym Tother_sym;
	typedef struct Treg_type Treg_type;
	typedef struct Treg_call Treg_call;
	typedef struct Treg_sym Treg_sym;
	typedef struct Texpr Texpr;
	typedef struct Texpr_list Texpr_list;
	typedef struct Texpr_bool_op Texpr_bool_op;
	typedef struct Tmethod_call Tmethod_call;
	typedef struct Tmethod_sym Tmethod_sym;
	typedef struct Tdeclarations_sym Tdeclarations_sym;
	typedef struct Tsentence_list Tsentence_list;
	typedef struct Tlibrary Tlibrary;
	typedef struct Tinterface_sym Tinterface_sym;
	typedef struct Tsentence Tsentence;
	typedef struct Tif_statement Tif_statement;
	typedef struct Tassign_statement Tassign_statement;
	typedef struct Tmult_assign_statement Tmult_assign_statement;
	typedef struct Twhile_loop Twhile_loop;
	typedef struct Tfromto_loop Tfromto_loop;
	typedef struct Treserved_call Treserved_call;
	
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
	#ifndef BOOL_TYPE
		#define BOOL_TYPE
		typedef enum {false, true} bool;
	#endif
	
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
	typedef struct {
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
	typedef struct Tid_list Tid_list;
	
	struct Tid_list {
		char *actual;
		Tid_list *next;
	};
	
	/**
	 * \brief Tvar_sym type definition
	 * Symbols are meant to be part of the symbol table
	 */
	typedef struct {
		char *name;
		Ttype *storage;
	} Tvar_sym;
	
	/**
	 * \brief Tvar_sym_list type definition
	 * Note that constants and vars are both called via this type list
	 */
	typedef struct Tvar_sym_list Tvar_sym_list;
	 
	struct Tvar_sym_list {
		Tvar_sym *actual;
		Tvar_sym_list *next;
	};
	
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
		char *type;
		union {
			Tvar_sym *var_call;
			int *int_val;
		} val;
	} Tint_id_val;
	
	/**
	 * \brief Tstr_list type definition
	 */
	typedef struct Tstr_list Tstr_list;
	
	struct Tstr_list {
		Tstr_val *actual;
		Tstr_list *next;
	};
	
	/**
	 * \brief Tint_id_val_list type definition
	 * This type is meant to be used when you need a list of integer values 
	 * that can be obtained either by an existing integer variable/constant
	 * or entered directly.
	 */
	typedef struct Tint_id_val_list Tint_id_val_list;
	
	struct Tint_id_val_list {
		Tint_id_val *value;
		Tint_id_val_list *next;
	};
	
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
	 * \brief Tarray_call type definition
	 * A call to an array need to store both the name of the indexes
	 */
	
	typedef struct {
		char *name;
		Texpr_list *indexes;
	} Tarray_call;
	
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
	struct Tother_type {
		char *name;
		union {
			Ttype *other;
			Tenum_type *enumerated;
			Tarray_type *array;
			Tfile_type *file;
			Treg_type *reg;
		} kind;
		char *type;
	};
	
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
	struct Tother_sym {
		char *name;
		union {
			Tvar_sym *other;
			Tenum_sym *enumerated;
			Tarray_sym *array;
			Tfile_sym *file;
			Treg_sym *reg;
		} symbol;
		char *type;
		Tother_type *type_type;
	};
	
	/**
	 * \brief Tother_type_list type definition
	 */
	typedef struct Tother_type_list Tother_type_list;
	
	struct Tother_type_list {
		Tother_type *actual;
		Tother_type_list *next;
	};
	
	/**
	 * \brief Tother_sym_list type definition
	 */
	typedef struct Tother_sym_list Tother_sym_list;
	
	struct Tother_sym_list {
		Tother_sym *actual;
		Tother_sym_list *next;
	};
	
	/**
	 * \brief Tsym_call type definition
	 * In this structure char *type can be:
	 *  -  OParray_call (for expr_bool.array_call)
	 *  -  OPid_call (for expr_bool.id_call)
	 *  -  OPreg_call (for expr_bool.reg_call)
	 */
	typedef struct {
		union {
			Tarray_call *array_call;
			char *id_call;
			Treg_call *reg_call;
		} call;
		char *type;
	} Tsym_call;
	
	/**
	 * \brief Tsym_call_list type definition
	 */
	typedef struct Tsym_call_list Tsym_call_list;
	
	struct Tsym_call_list {
		Tsym_call *actual;
		Tsym_call_list *next;
	};
	
	/**
	 * \brief Treg_type_sym type definition
	 */
	typedef struct {
		char *name;
		Treg_type *list;
	} Treg_type_sym;
	
	/**
	 * \brief Treg_sym type definition
	 */
	struct Treg_sym {
		char *name;
		Treg_type_sym *type;
		Tother_sym_list *store;
	};
	
	/**
	 * \brief Treg_call type definition
	 * Note that this will store only a ultimate call to
	 * a register; myRegister.intArrayNM[x, y] should be
	 * stored as a Tvar_sym (to an integer var) and not 
	 * as a Treg_call!
	 */
	
	struct Treg_call {
		Tsym_call *actual;
		Treg_call *next;
	};
	
	/**
	 * \brief expr_bool type definition
	 * In this structure char *type can be:
	 *  -  OPexpr_bool (for expr_bool.expr_bool)
	 *  -  OPvar_call (for expr_bool.var_call, note that this is used only to
	 *                 store a boolean internal var)
	 *  -  OParray_call (for expr_bool.array_call)
	 *  -  OPid_call (for expr_bool.id_call)
	 *  -  OPmethod_call (for expr_bool.method_call)
	 *  -  OPreg_call (for expr_bool.reg_call)
	 */
	typedef struct {
		union {
			Texpr_bool_op *expr_bool;
			Tvar_sym *var_call;
			Tarray_call *array_call;
			char *id_call;
			Tmethod_call *method_call;
			Treg_call *reg_call;
		} expr_bool;
		char *type;
	} Texpr_bool;
	
	/**
	 * \brief expr_bool_op type definition
	 * In this special case, we use a variable char *op; that implitily
	 * specifies which type will be used in left and right vars:
	 *  - OPnot (for right.expr_bool = NULL, left.expr_bool)
	 *  - OPeq/OPless/OPgreater/OPle/OPge/OPne (for right.expr, left.expr)
	 *  - OPand/OPor (for right.expr_bool, left.expr_bool)
	 */
	struct Texpr_bool_op {
		char *op;
		union{
			Texpr_bool *expr_bool;
			Texpr *expr;
		} left;
		union{
			Texpr_bool *expr_bool;
			Texpr *expr;
		} right;
	};
	
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
	 *  -  OPvar_call (for expr.var_call, note that this is used only to
	 *                 store a boolean internal var)
	 *  -  OParray_call (for expr.array_call)
	 *  -  OPid_call (for expr_bool.id_call)
	 *  -  OPmethod_call (for expr.method_call)
	 *  -  OPreg_call (for expr.reg_call)
	 */
	struct Texpr {
		char *type;
		union {
			Texpr_bool_op *expr_bool;
			Texpr_op *expr;
			Tvar_sym *var_call;
			Tarray_call *array_call;
			char *id_call;
			Tmethod_call *method_call;
			Treg_call *reg_call;
		} expr;
	};
	
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
	struct Tlibrary {
		Tlibrary *next;
		Tmethod_sym *actual;
	};
	
	/**
	 * \brief Tmethod_sym type definition
	 * In this structure char *type can be:
	 *  - OPalg/OPfunc/OPproc
	 */
	struct Tmethod_sym {
		char *name;
		Tinterface_sym *interface;
		Tdeclarations_sym *declarations;
		Tsentence_list *sentences;
		char *type;
	};
	
	/**
	 * \brief Tinterface_sym type definition
	 * If this is an interface for a function then args_io
	 * would be NULL and args_out would be a sole arg, etc..
	 */
	struct Tinterface_sym {
		Tother_sym_list *args_in, *args_out, *args_io;
	};
	 
	/**
	 * \brief Tdeclarations_sym type definition
	 */
	struct Tdeclarations_sym {
		Tother_sym_list *consts, *vars;
		Tother_type_list *types;
	};
	 
	/**
	 * \brief Tsentence_list type definition
	 */
	struct Tsentence_list {
		Tsentence *actual;
		Tsentence_list *next;
	};
	 
	/**
	 * \brief Tsentence type definition
	 * In this structure char *type can be:
	 *  -  Vif_statement (for sentence.if_statement)
	 *  -  Vassign_statement (for sentence.assign_statement)
	 *  -  Vmult_assign_statement (for sentence.mult_assign_statement)
	 *  -  Vwhile_loop (for sentence.while_loop)
	 *  -  Vfromto_loop (for sentence.fromto_loop)
	 *  -  Vmethod_call (for sentence.method_call)
	 *  -  Vreserved_call (for sentence.reserved_call)
	 */
	struct Tsentence {
		char *type;
		union {
			Tif_statement *if_statement;
			Tassign_statement *assign_statement;
			Tmult_assign_statement *mult_assign_statement;
			Twhile_loop *while_loop;
			Tfromto_loop *fromto_loop;
			Tmethod_call *method_call;
			Treserved_call *reserved_call;
		} sentence;
	};
	
	/**
	 * \brief Telif_statement type definition
	 */
	typedef struct {
		Texpr_bool *cond;
		Tsentence_list *sentence_list;
	} Telif_statement;
	 
	/**
	 * \brief Telif_statement_list type definition
	 */
	typedef struct Telif_statement_list Telif_statement_list;
	
	struct Telif_statement_list {
		Telif_statement *actual;
		Telif_statement_list *next;
	};
	
	/**
	 * \brief Tif_statement type definition
	 */
	struct Tif_statement {
		Texpr_bool *cond;
		Telif_statement_list *elif_statement_list;
		Tsentence_list *sentence_list, *else_sentence_list;
	};
	 
	/**
	 * \brief Tassign_statement type definition
	 */
	struct Tassign_statement {
		Tsym_call_list *sym_list;
		Texpr *expr;
	};
	 
	/**
	 * \brief Texpr_list type definition
	 */
	
	struct Texpr_list {
		Texpr *actual;
		Texpr_list *next;
	};
	
	/**
	 * \brief Texpr_list_nested type definition
	 * Used in mult_assign_statement/mult_assign_statement_list
	 */
	typedef struct Texpr_list_nested Texpr_list_nested;
	
	struct Texpr_list_nested {
		Texpr_list *actual;
		Texpr_list_nested *next;
	};
	 
	/**
	 * \brief Tmult_assign_statement type definition
	 */
	struct Tmult_assign_statement {
		Tsym_call_list *sym_list;
		Texpr_list *expr_list;
	};
	
	/**
	 * \brief Twhile_loop type definition
	 */
	struct Twhile_loop {
		Texpr_bool *cond;
		Tsentence_list *sentence_list;
	};
	 
	/**
	 * \brief Tfromto_loop type definition
	 */
	struct Tfromto_loop {
		Tassign_statement *assign_statement;
		int *int_val;
		Tsentence_list *sentence_list;
	};
	 
	/**
	 * \brief Tmethod_call type definition
	 */
	struct Tmethod_call {
		Texpr_list *arg_list;
		union {
			char *name;
			Tmethod_sym *symbol;
		} function;
	};
	 
	/**
	 * \brief Treserved_call type definition
	 */
	struct Treserved_call {
		Texpr_list *arg_list;
		union {
			char *name;
			void *(*function_ptr)();
		} function;
	};
	
	/*
	 * List types to keep an eye in for sorting the list of its elements
	 * in order to apply optimizstion techniques (B trees, binary trees,
	 * hash tables, linked lists..):
	 *  - Tother_type_list
	 *  - Tother_sym_list
	 *  - Tlibrary
	 * And also the structures that directly use them:
	 *  - Treg_type_sym
	 *  - Tprogram
	 *  - Tinterface_sym
	 *  - Tdeclarations_sym
	 */
	 
	/****************************
	*    Global declarations    *
	****************************/
	/**
	 * \brief Main program tree
	 */
	
	Tprogram *program;
	
	/**
	 * \brief Symbols table
	 * This is where symbols like variables (both local and global
	 * ones) or methods are stored so that they ca be easily and
	 * quickly retrieved.
	 * 
	 * The naming convention for each kind of symbol is:
	 * 		- Global variables:			":global_var:<var_name>"
	 * 		- Local variables:			":local_var:<method_name>@<var_name>"
	 * 		- Global types:				":global_type:<type_name>"
	 * 		- Local types:				":local_type:<method_name>@<type_name>"
	 * 		- Methods:					":method:<method_name>"
	 * 		- Vars inside registers:	":reg_var:<reg_name>@<var_name>"
	 */
	Tsym_table *sym_table;
	
	/**
	 * \brief Temporal pointer to actual method (if any)
	 * HACK: Sometimes the Lea translator needs to know exactly to which
	 * method symbol does a local variable, or an call argument belong to.
	 *
	 * The solution provided by this hack is to create a temporal external
	 * pointer that points to the method symbol while it's being constructed,
	 * and thus Lea translation calls can store there the calling args,
	 * get the method name in order to store a var in the symbol table (see
	 * above), etc.
	 *
	 * It's set to NULL when Lea Translator is not inside a method (by default).
	 */
	
 	Tmethod_sym *tmp_method_sym;
	
	/**
	 * \brief Name of actual register (if any)
	 * HACK: Lea Translator needs to know the name(s) of a register when
	 * declaring the vars inside of it, and it's inside tmp_reg_names where
	 * it's stored in that case (temporally).
	 *
	 * It's set to NULL when we're not inside a register.
	 */
	Tid_list *tmp_reg_names;
	
	/**
	 * \brief Kind of actual register (if any)
	 * HACK: Lea Translator needs to know whether we're declaring a new register
	 * type or a new register var directly
	 *
	 * It's set to NULL when we're not inside a register. Otherwise, it can
	 * be set to:
	 * 		- Vreg_type_const_dcl
	 * 		- Vreg_type_types_dcl
	 * 		- Vreg_type_vars_dcl
	 */
	char *tmp_reg_type;
	
	/****************************
	*    Function prototypes    *
	****************************/
	/**
	 * \Brief Prototypes of the (TR)translator functions
	 */
	// program: 
	void TRprogram(Tsentence_list *); 
	// prog_header: 
	void TRprog_header(char *); 
	// alg_header: 
	void TRalg_header(char *); 
	// func_header: 
	void TRfunc_header(char *); 
	// proc_header: 
	void TRproc_header(char *);
	// in_var_dcl: 
// 	void TRin_var_dcl(Tid_list *, char *, NULL, NULL); 
// 	void TRin_var_dcl(Tid_list *, char *, char *, NULL); 
	void TRin_var_dcl(Tid_list *, char *, char *, char); 
	void TRin_var_dcl_array(Tid_list *, Tint_id_val_list *, char *); 
	// out_var_dcl: 
// 	void TRout_var_dcl(Tid_list *, char *, NULL, NULL); 
// 	void TRout_var_dcl(Tid_list *, char *, char *, NULL); 
	void TRout_var_dcl(Tid_list *, char *, char *, char); 
	void TRout_var_dcl_array(Tid_list *, Tint_id_val_list *, char *); 
	// inout_var_dcl: 
// 	void TRinout_var_dcl(Tid_list *, char *, NULL, NULL); 
// 	void TRinout_var_dcl(Tid_list *, char *, char *, NULL); 
	void TRinout_var_dcl(Tid_list *, char *, char *, char); 
	void TRinout_var_dcl_array(Tid_list *, Tint_id_val_list *, char *); 
	// id_list: 
	Tid_list *TRid_list(char *, Tid_list *); 
// 	Tid_list *TRid_list(NULL, char *); 
	// int_val_list: 
	Tint_id_val_list *TRint_val_list(Tint_id_val *, Tint_id_val_list *); 
// 	Tint_id_val_list *TRint_val_list(NULL, Tint_id_val *); 
	// int_id_val: 
	Tint_id_val *TRint_id_val_int(int *);
	Tint_id_val *TRint_id_val_id(char *); 
	// const_dcl_list: 
	void TRconst_dcl_bool(Tid_list *, bool *); 
	void TRconst_dcl_int(Tid_list *, int *); 
	void TRconst_dcl_float(Tid_list *, float *); 
	void TRconst_dcl_char(Tid_list *, char *); 
	void TRconst_dcl_str(Tid_list *, char *); 
	void TRconst_dcl_reg(Tid_list *); 
	// types_dcl_list: 
	void TRtypes_dcl_enum(Tid_list *, Tstr_list *); 
// 	void TRtypes_dcl_var(Tother_type_list *, Tid_list *, char *, NULL); 
	void TRtypes_dcl_var(Tid_list *, char *, char *); 
	void TRtypes_dcl_array(Tid_list *, Tint_id_val_list *, char *); 
	void TRtypes_dcl_reg(Tid_list *); 
	// str_list: 
	Tstr_list *TRstr_list(char *,Tstr_list *); 
// 	Tstr_list *TRstr_list(NULL, char *); 
	// vars_dcl:
	void TRvars_dcl_reg(Tid_list *);
	// vars_reg_dcl: 
// 	void TRvars_noreg_dcl(Tid_list *, char *, NULL); 
	void TRvars_noreg_dcl(Tid_list *, char *, char *); 
	void TRvars_noreg_dcl_array(Tid_list *, Tint_id_val_list *, char *); 
	// register: 
	void TRregister(); 
	// sentence_list: 
	// 		NULL;  
	Tsentence_list *TRsentence_list(Tsentence *, Tsentence_list *); 
	// 		NULL;  
	// if_statement: 
	Tsentence *TRif_statement(Texpr_bool *, Tsentence_list *, Telif_statement_list *, Tsentence_list *); 
// 	Tsentence *TRif_statement(Texpr_bool *, Tsentence_list *, NULL, Tsentence_list *); 
	// elif_statement: 
	Telif_statement *TRelif_statement(Texpr_bool *, Tsentence_list *); 
	// elif_statement_list: 
	Telif_statement_list *TRelif_statement_list(Telif_statement *, Telif_statement_list *); 
// 	Telif_statement_list *TRelif_statement_list(NULL, Telif_statement *); 
	// assign_statement: 
	Tsentence *TRassign_statement_assign(Tsentence *, Tsentence *); 
	Tsentence *TRassign_statement_expr(Tsentence *, Texpr *); 
	Tsentence *TRassign_statement_mult(Tsentence *, Texpr_list_nested *); 
	// mult_assign_list: 
	Texpr_list_nested *TRmult_assign_list(Texpr_list_nested *, Texpr_list_nested *); 
	Texpr_list_nested *TRmult_assign_list_expr(Texpr *, Texpr_list_nested *); 
// 	Tmult_assign *TRmult_assign_list_expr($1, NULL); 
// 	Tmult_assign *TRmult_assign_list($1, NULL); 
	// mult_assign_statement: 
	Tsentence *TRmult_assign_statement(Tvar_sym_list *, Texpr_list *);
	// output_input_statement: 
	Tsentence *TRoutput_input_statement(char, Texpr_list *); 
	// while_loop: 
	Tsentence *TRwhile_loop(Texpr_bool *, Tsentence_list *); 
	// fromto_assign_statement: 
	Tassign_statement *TRfromto_assign_statement(Tsentence *, Texpr *); 
	// fromto_loop: 
	Tsentence *TRfromto_loop(Tassign_statement *, Texpr *, Tsentence_list *); 
	Tsentence *TRfunction_call(char *, Texpr_list *); 
	Tsentence *TRvariable_call(char *, Texpr_list *); 
	Tsentence *TRvariable_call_node(char *); 
	Tsentence *TRstruct_call(Tsentence *, Tsentence *);
	Tsentence *TRstruct_call_node(Tsentence *);
	// variable_list: 
	Tvar_sym_list *TRvariable_list(Tsentence *, Tvar_sym_list *); 
	Tvar_sym_list *TRvariable_list_node(Tsentence *); 
	// procedure_call: 
	Tsentence *TRprocedure_call(char *, Texpr_list *); 
	// expr_list: 
	// 		NULL;  
	Texpr_list *TRexpr_list_full(Texpr *, Texpr_list *); 
// 	Texpr_list *TRexpr_list_full(NULL, Texpr *); 
	// expr_bool: 
	Texpr_bool *TRexpr_bool_val(bool *); 
	Texpr_bool *TRexpr_bool_struct(Tsentence *); 
// 	Texpr_bool *TRexpr_bool(char, Texpr_bool *, NULL); 
	Texpr_bool *TRexpr_bool_not(Texpr_bool *);  
	Texpr_bool *TRexpr_bool_log(char, Texpr_bool *, Texpr_bool *); 
	Texpr_bool *TRexpr_bool(char, Texpr *, Texpr *); 
// 	Texpr_bool *TRexpr_bool(char, Texpr*, Texpr *); 
// 	Texpr_bool *TRexpr_bool(char, Texpr*, Texpr *); 
// 	Texpr_bool *TRexpr_bool(char, Texpr*, Texpr *); 
// 	Texpr_bool *TRexpr_bool(char, Texpr*, Texpr *); 
// 	Texpr_bool *TRexpr_bool(char, Texpr*, Texpr *); 
// 	Texpr_bool *TRexpr_bool(char, Texpr*, Texpr *); 
// 	Texpr_bool *TRexpr_bool(char, Texpr*, Texpr *); 
	Texpr_bool *TRexpr_bool_fcall(Tsentence *); 
	// expr: 
	Texpr *TRexpr_int(int *); 
	Texpr *TRexpr_expr_bool(Texpr_bool *); 
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
