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
 * along with nbsmtp; if not, write to the Free Software
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
	 * \brief node_list type definition
	 */
	typedef struct str_node_list node_list;
	
	struct str_node_list {
		node *head;
		node_list *next;
	};
	 
	/**
	 * \brief boolean type definition
	 */
	typedef enum{false, true} bool;
	
	/**
	 * \brief kind type definition
	 * Defines all the types of information that can be stored (in a node/node_list)
	 */
	typedef enum{
		Const_bool,
		Const_int,
		Const_float,
		Bool_val,
		Int_val,
		Float_val,
		Id,
		Expr_bool_op,
		Expr_op,
		Output,
		Input,
		Assign,
		Conditional_if,
		Sentence,
		Sentence_list,
		Sentence_list_block,
		Const_dcl_list,
		Const_block,
		Dcl_block,
		Id_list,
		Prog_header,
		Program
	} kind;
	
#endif
