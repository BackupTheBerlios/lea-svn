/**
 * \file eval_operations.h
 * \brief Functions to execute to eval nodes/node_lists
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
#ifndef EVAL_OPERATIONS_H
	#define EVAL_OPERATIONS_H
	
	#include <stdlib.h>
	#include <string.h>
	
	/**
	 * \brief storage type definition
	 * It contains all the essential types of information
	 */
	typedef union {
			int *int_val;
			bool *bool_val;
			float *float_val;
			char *char_val;
			char **str_val;
			node **node_ptr;
		} storage;
	
	/**
	 * \brief node type definition
	 * A node just contains information. Everything else is built around
	 * and according to nodes structure!
	 */
	typedef struct str_node node;
	
	struct str_node {
		kind node_kind;
		storage node_storage;
		node* (*eval)();
		node* (*free)();
	};
	 
	/**
	 * \brief boolean type definition
	 */
	typedef enum {false, true} bool;
	
	/**
	 * \brief kind type definition
	 * Defines all the types of information that can be stored in a node
	 */
	typedef enum {
		Int_val,
		Bool_val,
		Float_val,
		Char_val,
		Str_val,
		Expr_bool,
		Expr_list,
		Expr,
		Procedure_call,
		Function_call,
		Fromto_loop,
		While_loop,
		Output_input_statement,
		Mult_assign_statement,
		Mult_assign_list,
		Assign_statement,
		Elif_statement_list,
		Elif_statement,
		If_statement,
		Sentence,
		Sentence_list,
		Sentence_list_block,
		Register,
		Vars_dcl,
		Vars_block,
		Str_list,
		Types_dcl_list,
		Types_block,
		Const_dcl_list,
		Const_block,
		Declarations_block,
		Int_val_list,
		Array_dimensions,
		Id_list,
		Inout_var_dcl,
		Out_var_dcl,
		In_var_dcl,
		Inout_arg_list,
		Out_arg_list,
		In_arg_list,
		Proc_arg_list,
		Proc_arg,
		Interface_block,
		Proc_header,
		Func_header,
		Alg_header,
		Procedure,
		Function,
		Algorithm,
		Library,
		Proc_header,
		Program
	} kind;
	
	/**
	 * \brief Expr_bool type definition
	 */
	typedef struct {
		// This will be an array of 1 or 2 elements of pointers to nodes
		Expr	**exprs;
		
		// This var will say what type of expr_bool will store each node
		// That is: b, i, n, ^, o, =, <, >, l, g, !.
		char	type;
		
		bool*	(*eval)();
		void	(*free)();
	} Expr_bool;
	
	/**
	 * \brief Expr_list type definition
	 */
	typedef struct {
		Expr	*actual, *next;
	} Expr_list;
	
	/**
	 * \brief expr_return_types type definition
	 */
	typedef union {
		bool	*b;, *bb[2];
		int		*i;, *ii[2];
		float	*f, *ff[2];
		char	*c, *cc[2], **s, **s[2];
	} expr_return_types;
	
	/**
	 * \brief Expr type definition
	 */
	typedef struct {
		
		// This var will say what type of expr will store each node
		// That is: i, b, f, s, d, +, -, *, /, %, ^, n.
		char				type;
		
		expr_return_types	(*eval)();
		void				(*free)();
	} Expr;
	
	/**
	 * \brief Procedure_call type definition
	 */
	typedef struct {
		Str_val		*id;
		Expr_list	*expr_list;
	} Procedure_call;
	
	/**
	 * \brief Fromto_loop type definition
	 */
	typedef struct {
		Assign_statement	*from;
		Expr				*to;
		Sentence_list		*sentence_list;
	} Fromto_loop;
	
	/**
	 * \brief While_loop type definition
	 */
	typedef struct {
		Expr_bool			*condition;
		Sentence_list		*sentence_list;
	} While_loop;
	
	/**
	 * \brief Output_input_statement type definition
	 */
	typedef struct {
		Expr_list	*expr_list;
	} Output_input_statement;
	
	/**
	 * \brief mult_assign_statement type definition
	 */
	typedef struct {
		Id_list		*id_list;
		Expr_list	*expr_list;
	} mult_assign_statement;
	
	/**
	 * \brief Mult_assign_list type definition
	 */
	typedef struct {
		union	list {
			*Expr,
			*Mult_assign_list
		};
	
		// This var will say what type of Mult_assign_list will store each node
		// That is: m, e, M, E.
		char	*type;
	} Mult_assign_list;
	
	/**
	 * \brief Assign_statement type definition
	 */
	typedef struct {
		Str_val		*id;
		
		union		list {
			*Expr,
			*Mult_assign_list,
			*Assign_statement
		};
	
		// This var will say what type of Assign_statement will store each node
		// That is: e, m, a
		char	*type;
	} Assign_statement;
	
	/**
	 * \brief Elif_statement_list type definition
	 */
	typedef struct {
		Elif_statement	**Elif_statements;
		bool			*pair_or_node;
	} Elif_statement_list;
	
	/**
	 * \brief Elif_statement type definition
	 */
	typedef struct {
		Expr_bool		*condition;
		Sentence_list	*sentence_list;
	} Elif_statement;
	
	/**
	 * \brief If_statement type definition
	 */
	typedef struct {
		Expr_bool				*condition;
		Sentence_list			*sentence_list;
		Elif_statement_list		*elif_statement_list;
		Sentence_list			*else_sentence_list;
	} If_statement;
	
	/**
	 * \brief Sentence type definition
	 */
	typedef struct {
		union 		sentence {
			*If_statement,
			*Assign_statement,
			*Mult_assign_statement,
			*Ouput_input_statement,
			*While_loop while_loop,
			*Fromto_loop,
			*Function_call,
			*Procedure_call
		};
	
		// This var will say what type of Sentence will store each node
		// That is: m, o, w, t, f, p.
		char		*type;
	} Sentence;
	
#endif
