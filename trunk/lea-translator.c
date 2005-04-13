/**
 * \file lea-translator.c
 * \brief Translator to Abstract Tree functions
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
 
 #include "lea-translator.h"

/**
 * \brief Automagical skeleton function creation from header's func. prototypes
 * These skeleton functions were automagically created executing the command:
 *
 * $ ACTION=print_skeleton_functions ./handy.awk lea-translator.h >> lea-translator.c
 *
 * This way they're created from the function prototypes of lea-translator.h
 */

/**
 * \brief 
 * 
 * \param		
 * \return	 
 */
Tprogram *TRprogram(char *name, Tdeclarations_sym *declarations, Tsentence_list *sentences, Tmethod_sym *methods)
{
	Tprogram *ret;

	return ret;
}

/**
 * \brief 
 * 
 * \param		
 * \return	 
 */
Tmethod_sym *TRlibrary(Tmethod_sym *previous_list, Tmethod_sym *actual)
{
	Tmethod_sym *ret;

	return ret;
}

/**
 * \brief 
 * 
 * \param		
 * \return	 
 */
Tmethod_sym *TRalgorithm(char *name, Tinterface_sym *interface, Tdeclarations_sym *declarations, Tsentence_list *sentences)
{
	Tmethod_sym *ret;

	return ret;
}

/**
 * \brief 
 * 
 * \param		
 * \return	 
 */
Tmethod_sym *TRfunction(Tmethod_sym *interface, Tdeclarations_sym *declarations, Tsentence_list *sentences)
{
	Tmethod_sym *ret;

	return ret;
}

/**
 * \brief 
 * 
 * \param		
 * \return	 
 */
Tmethod_sym *TRprocedure(Tmethod_sym *interface, Tdeclarations_sym *declarations, Tsentence_list *sentences)
{
	Tmethod_sym *ret;

	return ret;
}

/**
 * \brief 
 * 
 * \param		
 * \return	 
 */
Tmethod_sym *TRfunc_header(char *name, Tother_sym_list *args_in, Tother_sym *arg_out)
{
	Tmethod_sym *ret;

	return ret;
}

/**
 * \brief 
 * 
 * \param		
 * \return	 
 */
Tmethod_sym *TRproc_header(char *name, Tinterface_sym *args)
{
	Tmethod_sym *ret;

	return ret;
}

/**
 * \brief 
 * 
 * \param		
 * \return	 
 */
Tinterface_sym *TRinterface_block_in(Tother_sym_list *actual_in_args, Tinterface_sym *interface)
{
	Tinterface_sym *ret;

	return ret;
}

/**
 * \brief 
 * 
 * \param		
 * \return	 
 */
Tinterface_sym *TRinterface_block_out(Tother_sym_list *actual_out_args, Tinterface_sym *interface)
{
	Tinterface_sym *ret;

	return ret;
}

/**
 * \brief 
 * 
 * \param		
 * \return	 
 */
Tinterface_sym *TRproc_arg_in(Tother_sym_list *args)
{
	Tinterface_sym *ret;

	return ret;
}

/**
 * \brief 
 * 
 * \param		
 * \return	 
 */
Tinterface_sym *TRproc_arg_out(Tother_sym_list *args)
{
	Tinterface_sym *ret;

	return ret;
}

/**
 * \brief 
 * 
 * \param		
 * \return	 
 */
Tinterface_sym *TRproc_arg_inout(Tother_sym_list *args)
{
	Tinterface_sym *ret;

	return ret;
}

/**
 * \brief 
 * 
 * \param		
 * \return	 
 */
Tinterface_sym *TRproc_arg_list(Tinterface_sym *actual, Tinterface_sym *next_list)
{
	Tinterface_sym *ret;

	return ret;
}

/**
 * \brief 
 * 
 * \param		
 * \return	 
 */
Tother_sym_list *TRin_arg_list(Tother_sym *actual, Tother_sym_list *next_list)
{
	Tother_sym_list *ret;

	return ret;
}

/**
 * \brief 
 * 
 * \param		
 * \return	 
 */
Tother_sym_list *TRout_arg_list(Tother_sym *actual, Tother_sym_list *next_list)
{
	Tother_sym_list *ret;

	return ret;
}

/**
 * \brief 
 * 
 * \param		
 * \return	 
 */
Tother_sym_list *TRinout_arg_list(Tother_sym *actual, Tother_sym_list *next_list)
{
	Tother_sym_list *ret;

	return ret;
}

/**
 * \brief 
 * 
 * \param		
 * \return	 
 */
Tother_sym *TRin_var_dcl(Tid_list *id_list, char *type1, char *type2, char type3)
{
	Tother_sym *ret;

	return ret;
}

/**
 * \brief 
 * 
 * \param		
 * \return	 
 */
Tother_sym *TRin_var_dcl_array(Tid_list *id_list, Tint_id_val_list *dimensions, char *type)
{
	Tother_sym *ret;

	return ret;
}

/**
 * \brief 
 * 
 * \param		
 * \return	 
 */
Tother_sym *TRout_var_dcl(Tid_list *id_list, char *type1, char *type2, char type3)
{
	Tother_sym *ret;

	return ret;
}

/**
 * \brief 
 * 
 * \param		
 * \return	 
 */
Tother_sym *TRout_var_dcl_array(Tid_list *id_list, Tint_id_val_list *dimensions, char *type)
{
	Tother_sym *ret;

	return ret;
}

/**
 * \brief 
 * 
 * \param		
 * \return	 
 */
Tother_sym *TRinout_var_dcl(Tid_list *id_list, char *type1, char *type2, char type3)
{
	Tother_sym *ret;

	return ret;
}

/**
 * \brief 
 * 
 * \param		
 * \return	 
 */
Tother_sym *TRinout_var_dcl_array(Tid_list *id_list, Tint_id_val_list *dimensions, char *type)
{
	Tother_sym *ret;

	return ret;
}

/**
 * \brief Allocate memory for an identifier list
 * 
 * \param	actual			Actual identifier
 * \param	next_list		Next list of identifiers
 * \return					An identifier list 
 */
Tid_list *TRid_list(char *actual, Tid_list *next_list)
{
	// Returning value
	Tid_list *ret;
	
	// Allocate needed memory
	ret				=	malloc(sizeof(Tid_list));
	
	// Initialization
	
	ret->actual 	=	actual;
	ret->next		=	next_list;

	return ret;
}

/**
 * \brief 
 * 
 * \param		
 * \return	 
 */
Tint_id_val_list *TRint_val_list(Tint_id_val *actual, Tint_id_val_list *next_list)
{
	Tint_id_val_list *ret;

	return ret;
}

/**
 * \brief Allocate memory for an integer in a Tint_id_val struct
 * Tint_id_val structures are used when either an integer or a variable call can be needed
 * 
 * \param	value	Value to store
 * \return	A 		Tint_id_val struct
 */
Tint_id_val *TRint_id_val_int(int *value)
{
	Tint_id_val *ret;

	return ret;
}

/**
 * \brief 
 * 
 * \param		
 * \return	 
 */
Tint_id_val *TRint_id_val_id(char *identifier)
{
	Tint_id_val *ret;

	return ret;
}

/**
 * \brief 
 * 
 * \param		
 * \return	 
 */
Tdeclarations_sym *TRdeclarations_block(Tother_sym_list *consts_block, Tother_type_list *types_block, Tother_sym_list *vars_block)
{
	Tdeclarations_sym *ret;

	return ret;
}

/**
 * \brief 
 * 
 * \param		
 * \return	 
 */
Tother_sym_list *TRconst_dcl_list_bool(Tid_list *id_list, bool *value, Tother_sym_list *next_list)
{
	Tother_sym_list *ret;

	return ret;
}

/**
 * \brief 
 * 
 * \param		
 * \return	 
 */
Tother_sym_list *TRconst_dcl_list_int(Tid_list *id_list, int *value, Tother_sym_list *next_list)
{
	Tother_sym_list *ret;

	return ret;
}

/**
 * \brief 
 * 
 * \param		
 * \return	 
 */
Tother_sym_list *TRconst_dcl_list_float(Tid_list *id_list, float *value, Tother_sym_list *next_list)
{
	Tother_sym_list *ret;

	return ret;
}

/**
 * \brief 
 * 
 * \param		
 * \return	 
 */
Tother_sym_list *TRconst_dcl_list_char(Tid_list *id_list, char *value, Tother_sym_list *next_list)
{
	Tother_sym_list *ret;

	return ret;
}

/**
 * \brief 
 * 
 * \param		
 * \return	 
 */
Tother_sym_list *TRconst_dcl_list_str(Tid_list *id_list, char *value, Tother_sym_list *next_list)
{
	Tother_sym_list *ret;

	return ret;
}

/**
 * \brief 
 * 
 * \param		
 * \return	 
 */
Tother_sym_list *TRconst_dcl_list_reg(Tid_list *id_list, Tother_type *reg, Tother_sym_list *next_list)
{
	Tother_sym_list *ret;

	return ret;
}

/**
 * \brief 
 * 
 * \param		
 * \return	 
 */
Tother_type_list *TRtypes_dcl_list_enum(Tid_list *id_list, Tstr_list *elements, Tother_type_list *next_list)
{
	Tother_type_list *ret;

	return ret;
}

/**
 * \brief 
 * 
 * \param		
 * \return	 
 */
Tother_type_list *TRtypes_dcl_list_var(Tid_list *id_list, char *type1, char *type2, Tother_type_list *next_list)
{
	Tother_type_list *ret;

	return ret;
}

/**
 * \brief 
 * 
 * \param		
 * \return	 
 */
Tother_type_list *TRtypes_dcl_list_array(Tid_list *id_list, Tint_id_val_list *dimensions, char *type, Tother_type_list *next_list)
{
	Tother_type_list *ret;

	return ret;
}

/**
 * \brief 
 * 
 * \param		
 * \return	 
 */
Tother_type_list *TRtypes_dcl_list_reg(Tid_list *id_list, Tother_type *reg, Tother_type_list *next_list)
{
	Tother_type_list *ret;

	return ret;
}

/**
 * \brief 
 * 
 * \param		
 * \return	 
 */
Tstr_list *TRstr_list(char *actual, Tstr_list *next_list)
{
	Tstr_list *ret;

	return ret;
}

/**
 * \brief 
 * 
 * \param		
 * \return	 
 */
Tother_sym_list *TRvars_dcl_var(Tid_list *id_list, char *type1, char *type2, Tother_sym_list *next_list)
{
	Tother_sym_list *ret;

	return ret;
}

/**
 * \brief 
 * 
 * \param		
 * \return	 
 */
Tother_sym_list *TRvars_dcl_array(Tid_list *id_list, Tint_id_val_list *dimensions, char *type, Tother_sym_list *next_list)
{
	Tother_sym_list *ret;

	return ret;
}

/**
 * \brief 
 * 
 * \param		
 * \return	 
 */
Tother_sym_list *TRvars_dcl_reg(Tid_list *id_list, Tother_type *type, Tother_sym_list *next_list)
{
	Tother_sym_list *ret;

	return ret;
}

/**
 * \brief 
 * 
 * \param		
 * \return	 
 */
Tother_type *TRregister(Tother_sym_list *vars_list)
{
	Tother_type *ret;

	return ret;
}

/**
 * \brief 
 * 
 * \param		
 * \return	 
 */
Tsentence_list *TRsentence_list(Tsentence *actual, Tsentence_list *next_list)
{
	Tsentence_list *ret;

	return ret;
}

/**
 * \brief 
 * 
 * \param		
 * \return	 
 */
Tsentence *TRif_statement(Texpr_bool *if_expr, Tsentence_list *if_sentence_list, Telif_statement_list *el_if_list, Tsentence_list *else_sentence_list)
{
	Tsentence *ret;

	return ret;
}

/**
 * \brief 
 * 
 * \param		
 * \return	 
 */
Telif_statement *TRelif_statement(Texpr_bool *elif_expr, Tsentence_list *elif_sentence_list)
{
	Telif_statement *ret;

	return ret;
}

/**
 * \brief 
 * 
 * \param		
 * \return	 
 */
Telif_statement_list *TRelif_statement_list(Telif_statement *actual, Telif_statement_list *next_list)
{
	Telif_statement_list *ret;

	return ret;
}

/**
 * \brief 
 * 
 * \param		
 * \return	 
 */
Tsentence *TRassign_statement_assign(Tsentence *var_call, Tsentence *assign_statement)
{
	Tsentence *ret;

	return ret;
}

/**
 * \brief 
 * 
 * \param		
 * \return	 
 */
Tsentence *TRassign_statement_expr(Tsentence *var_list, Texpr *expr)
{
	Tsentence *ret;

	return ret;
}

/**
 * \brief Creates a sentence for a multiple assignation statement
 * 
 * \param	var_list	List of variables to set
 * \param	expr_list	List of expressions to use for the assignations
 * \return				Return a multiple assgination statement sentence
 */
Tsentence *TRmult_assign_statement(Tvar_sym_list *var_list, Texpr_list *expr_list)
{
	// Returning struct
	Tsentence				*ret;
	Tmult_assign_statement	*mult_assign_statement;
	
	// Allocate needed memory
	ret						=	malloc(sizeof(Tsentence));
	ret->type				=	malloc(sizeof(char));
	
	mult_assign_statement	=	malloc(sizeof(Tmult_assign_statement));

	// Initialization
//TODO: 	mult_assign_statement->sym_list	=	var_list;
	mult_assign_statement->expr_list	=	expr_list;
	
	*(ret->type)						=	Vmult_assign_statement;
	ret->sentence.mult_assign_statement	=	mult_assign_statement;
	
	return ret;
}

/**
 * \brief 
 * 
 * \param		
 * \return	 
 */
Tsentence *TRoutput_input_statement(char *name, Texpr_list *expr_list)
{
	Tsentence *ret;

	return ret;
}

/**
 * \brief Creates a sentence for a while loop
 * 
 * \param	expr_bool		Iteration condition
 * \param	sentence_list	List of sentences to execute inside the loop
 * \return					Return a while loop sentence
 */
Tsentence *TRwhile_loop(Texpr_bool *expr_bool, Tsentence_list *sentence_list)
{
	// Returning struct
	Tsentence	*ret;
	Twhile_loop	*while_loop;
	
	// Allocate needed memory
	ret			=	malloc(sizeof(Tsentence));
	ret->type	=	malloc(sizeof(char));
	
	while_loop	=	malloc(sizeof(Twhile_loop));
	
	// Initialization
	while_loop->cond			=	expr_bool;
	while_loop->sentence_list	=	sentence_list;
	
	*(ret->type)				=	Vwhile_loop;
	ret->sentence.while_loop	=	while_loop;
	
	return ret;
}

/**
 * \brief 
 * 
 * \param		
 * \return	 
 */
Tassign_statement *TRfromto_assign_statement(Tsentence *var_call, Texpr *expr)
{
	Tassign_statement *ret;

	return ret;
}

/**
 * \brief 
 * 
 * \param		
 * \return	 
 */
Tsentence *TRfromto_loop(Tassign_statement *fromto_statement, Texpr *expr, Tsentence_list *sentence_list)
{
	Tsentence *ret;

	return ret;
}

/**
 * \brief Allocates storage for a function call
 * 
 * \param	name		Function name
 * \param	expr_list	List of arguments passed to the function
 * \return	 			Pointer to the structure holding the function call
 */
Tsentence *TRfunction_call(char *name, Texpr_list *expr_list)
{
	// Returning struct
	Tsentence *ret;
	Tmethod_call *method_call;
	
	// Allocate needed memory
	ret			=	malloc(sizeof(Tsentence));
	ret->type	=	malloc(sizeof(char));
	method_call	=	malloc(sizeof(Tmethod_call));
	
	//Initialization
	// NOTE: arg_list can be a NULL pointer!
	method_call->arg_list		=	expr_list;
	method_call->function.name	=	name;
	
	*(ret->type)				=	Vmethod_call;
	ret->sentence.method_call	=	method_call;

	return ret;
}

/**
 * \brief 
 * 
 * \param		
 * \return	 
 */
Tsentence *TRvariable_call(char *name, Texpr_list *expr_list)
{
	Tsentence *ret;

	return ret;
}

/**
 * \brief 
 * 
 * \param		
 * \return	 
 */
Tsentence *TRvariable_call_node(char *name)
{
	Tsentence *ret;

	return ret;
}

/**
 * \brief 
 * 
 * \param		
 * \return	 
 */
Tsentence *TRstruct_call(Tsentence *actual, Tsentence *next_list)
{
	Tsentence *ret;

	return ret;
}

/**
 * \brief 
 * 
 * \param		
 * \return	 
 */
Tsentence *TRstruct_call_node(Tsentence *next_list)
{
	Tsentence *ret;

	return ret;
}

/**
 * \brief 
 * 
 * \param		
 * \return	 
 */
Tvar_sym_list *TRvariable_list(Tsentence *actual, Tvar_sym_list *next_list)
{
	Tvar_sym_list *ret;

	return ret;
}

/**
 * \brief 
 * 
 * \param		
 * \return	 
 */
Tvar_sym_list *TRvariable_list_node(Tsentence *next_list)
{
	
	Tvar_sym_list *ret;

	return ret;
}

/**
 * \brief 
 * 
 * \param		
 * \return	 
 */
Tsentence *TRprocedure_call(char *name, Texpr_list *arg_list)
{
	Tsentence *ret;

	return ret;
}

/**
 * \brief Adds an element to a linked list of expressions
 * 
 * \param	next_list	Existing linked list of expressions
 * \param	actual		Expresion element to add to the list
 * \return				New linked list containing all the previous \
 * expressions and the new one
 */
Texpr_list *TRexpr_list(Texpr *actual, Texpr_list *next_list)
{
	// Returning struct
	Texpr_list *ret;
	
	// Allocate needed memory
	ret	=	malloc(sizeof(Texpr_list));
	
	//Initialization
	ret->next	=	next_list;
	ret->actual	=	actual;

	return ret;
}

/**
 * \brief Allocates storage for a boolean expression value
 * 
 * \param	bool_val	Value to preserve
 * \return				Pointer to the expression holding the given value
 */
Texpr_bool *TRexpr_bool_val(bool *val)
{
	// Returning struct
	Texpr_bool *ret;
	// Internal intermediate variable symbol:
	Tvar_sym	*internal_sym;
	// Fundamental storage structure:
	Ttype		*storage;
	
	// Allocate needed memory
	ret							=	malloc(sizeof(Texpr_bool));
	ret->type					=	malloc(sizeof(char));
	
	internal_sym				=	malloc(sizeof(Tvar_sym));
	
	storage						=	malloc(sizeof(Ttype));
	storage->type				=	malloc(sizeof(char));
	
	// Initialization
	*(storage->type)			=	Vintern_bool_val;
	storage->storage.bool_val	=	val;
	
	// Note that internal vars don't have names:
	internal_sym->name			=	(char *)NULL;
	internal_sym->storage		=	storage;
	
	*(ret->type) 				=	OPvar_call;
	ret->expr_bool.var_call		=	internal_sym;
	
	return ret;
}

/**
 * \brief 
 * 
 * \param		
 * \return	 
 */
Texpr_bool *TRexpr_bool_struct(Tsentence *struct_call)
{
	Texpr_bool *ret;

	return ret;
}

/**
 * \brief Negates a boolean expression
 * 
 * \param	expr_bool	Boolean expression to negate
 * \return				Returns a boolean expression negating the given one
 */
Texpr_bool *TRexpr_bool_not(Texpr_bool *expr_bool)
{
	// Returning value
	Texpr_bool		*ret;
	// Internal intermediate struct
	Texpr_bool_op	*expr_bool_op;
	
	// Allocate needed memory
	ret					=	malloc(sizeof(Texpr_bool));
	ret->type			=	malloc(sizeof(char));
	
	expr_bool_op		=	malloc(sizeof(Texpr_bool_op));
	expr_bool_op->op	=	malloc(sizeof(char));
	
	//Initialization
	*(expr_bool_op->op)				=	OPnot;
	expr_bool_op->left.expr_bool	=	expr_bool;
	expr_bool_op->right.expr_bool	=	(Texpr_bool *)NULL;
	
	*(ret->type)					=	OPexpr_bool;
	ret->expr_bool.expr_bool		=	expr_bool_op;
	
	return ret;
}

/**
 * \brief Allocates storage for a boolean operation with two boolean operands
 *
 * \param	type		Operation
 * \param	left_expr	Left boolean expression in the operation
 * \param	right_expr	Right boolean expression in the operation
 * \return				Pointer to the structure holding the boolean operation
 */
Texpr_bool *TRexpr_bool_log(char type, Texpr_bool *left_expr, Texpr_bool *right_expr)
{
	// Returning struct
	Texpr_bool		*ret;
	// Internal intermediate storage struct:
	Texpr_bool_op	*expr_bool_op;
	
	// Allocate needed memory
	ret					=	malloc(sizeof(Texpr_bool));
	ret->type			=	malloc(sizeof(char));
	
	expr_bool_op		=	malloc(sizeof(Texpr_bool_op));
	expr_bool_op->op	=	malloc(sizeof(char));
	
	// Initialization
	switch (type)
	{
		case '&':
			*(expr_bool_op->op)	=	OPand;
			break;
		case '|':
			*(expr_bool_op->op)	=	OPor;
			break;
	}
	expr_bool_op->left.expr_bool	=	left_expr;
	expr_bool_op->right.expr_bool	=	right_expr;
	
	*(ret->type)					=	OPexpr_bool;
	ret->expr_bool.expr_bool		=	expr_bool_op;
	
	return ret;
}

/**
 * \brief Allocates storage for a boolean operation with two operands
 *
 * \param	type		Operation
 * \param	left_expr	Left expression in the operation
 * \param	right_expr	Right expression in the operation
 * \return				Pointer to the structure holding the boolean operation
 */
Texpr_bool *TRexpr_bool(char type, Texpr *left_expr, Texpr *right_expr)
{
	// Returning struct:
	Texpr_bool		*ret;
	// Internal intermediate storage struct:
	Texpr_bool_op	*expr_bool_op;
	
	// Allocate needed memory
	ret			=	malloc(sizeof(Texpr_bool));
	ret->type	=	malloc(sizeof(char));
	
	expr_bool_op		=	malloc(sizeof(Texpr_bool_op));
	expr_bool_op->op	=	malloc(sizeof(char));
	
	// Initialization
	switch (type)
	{
		case '=':
			*(expr_bool_op->op)	=	OPeq;
			break;
		case '<':
			*(expr_bool_op->op)	=	OPless;
			break;
		case '>':
			*(expr_bool_op->op)	=	OPgreater;
			break;
		case 'l':
			*(expr_bool_op->op)	=	OPle;
			break;
		case 'g':
			*(expr_bool_op->op)	=	OPge;
			break;
		case 'n':
			*(expr_bool_op->op)	=	OPne;
			break;
	}
	expr_bool_op->left.expr		=	left_expr;
	expr_bool_op->right.expr	=	right_expr;
	
	*(ret->type)				=	OPexpr_bool;
	ret->expr_bool.expr_bool	=	expr_bool_op;
	
	return ret;
}

/**
 * \brief 
 * 
 * \param		
 * \return	 
 */
Texpr_bool *TRexpr_bool_fcall(Tsentence *function_call)
{
	Texpr_bool *ret;

	return ret;
}

/**
 * \brief Allocates storage for an integer expression value
 * 
 * \param	int_val	Value to preserve
 * \return			Pointer to the expression holding the given value
 */
Texpr *TRexpr_int(int *int_val)
{
	// Returning struct:
	Texpr		*ret;
	// Internal intermediate variable symbol:
	Tvar_sym	*internal_sym;
	// Fundamental storage structure:
	Ttype		*storage;
	
	// Allocate needed memory
	ret							=	malloc(sizeof(Texpr));
	ret->type					=	malloc(sizeof(char));
	
	internal_sym				=	malloc(sizeof(Tvar_sym));
	
	storage						=	malloc(sizeof(Ttype));
	storage->type				=	malloc(sizeof(char));
	
	// Initialization
	*(storage->type)			=	Vintern_int_val;
	storage->storage.int_val	=	int_val;
	
	// Note that internal vars don't have names:
	internal_sym->name			=	(char *)NULL;
	internal_sym->storage		=	storage;
	
	*(ret->type) 				=	OPvar_call;
	ret->expr.var_call			=	internal_sym;
	
	return ret;
}

/**
 * \brief Allocates storage for a boolean expression value
 *
 * \param	bool_val	Value to preserve
 * \return				Pointer to the expression holding the given value
 */
Texpr *TRexpr_expr_bool(bool *bool_val)
{
	// Returning struct:
	Texpr		*ret;
	// Internal intermediate variable symbol:
	Tvar_sym	*internal_sym;
	// Fundamental storage structure:
	Ttype		*storage;
	
	// Allocate needed memory
	ret							=	malloc(sizeof(Texpr));
	ret->type					=	malloc(sizeof(char));
	
	internal_sym				=	malloc(sizeof(Tvar_sym));
	
	storage						=	malloc(sizeof(Ttype));
	storage->type				=	malloc(sizeof(char));
	
	// Initialization
	*(storage->type)			=	Vintern_bool_val;
	storage->storage.bool_val	=	bool_val;
	
	// Note that internal vars don't have names:
	internal_sym->name			=	(char *)NULL;
	internal_sym->storage		=	storage;
	
	*(ret->type) 				=	OPvar_call;
	ret->expr.var_call			=	internal_sym;
	
	return ret;
}

/**
 * \brief Allocates storage for a float expression value
 *
 * \param	float_val	Value to preserve
 * \return				Pointer to the expression holding the given value
 */
Texpr *TRexpr_float(float *float_val)
{
	// Returning struct:
	Texpr		*ret;
	// Internal intermediate variable symbol:
	Tvar_sym	*internal_sym;
	// Fundamental storage structure:
	Ttype		*storage;
	
	// Allocate needed memory
	ret							=	malloc(sizeof(Texpr));
	ret->type					=	malloc(sizeof(char));
	
	internal_sym				=	malloc(sizeof(Tvar_sym));
	
	storage						=	malloc(sizeof(Ttype));
	storage->type				=	malloc(sizeof(char));
	
	// Initialization
	*(storage->type)			=	Vintern_float_val;
	storage->storage.float_val	=	float_val;
	
	// Note that internal vars don't have names:
	internal_sym->name			=	(char *)NULL;
	internal_sym->storage		=	storage;
	
	*(ret->type) 				=	OPvar_call;
	ret->expr.var_call			=	internal_sym;
	
	return ret;
}

/**
 * \brief Allocates storage for a str expression value
 *
 * \param	str	Value to preserve
 * \return		Pointer to the expression holding the given value
 */
Texpr *TRexpr_str(char *str)
{
	// Returning struct:
	Texpr		*ret;
	// Internal intermediate variable symbol:
	Tvar_sym	*internal_sym;
	// Fundamental storage structure:
	Ttype		*storage;
	
	// Allocate needed memory
	ret							=	malloc(sizeof(Texpr));
	ret->type					=	malloc(sizeof(char));
	
	internal_sym				=	malloc(sizeof(Tvar_sym));
	
	storage						=	malloc(sizeof(Ttype));
	storage->type				=	malloc(sizeof(char));
	
	// Initialization
	*(storage->type)			=	Vintern_str_val;
	storage->storage.str_val	=	str;
	
	// Note that internal vars don't have names:
	internal_sym->name			=	(char *)NULL;
	internal_sym->storage		=	storage;
	
	*(ret->type) 				=	OPvar_call;
	ret->expr.var_call			=	internal_sym;
	
	return ret;
}

/**
 * \brief 
 * 
 * \param		
 * \return	 
 */
Texpr *TRexpr_struct(Tsentence *struct_call)
{
	Texpr *ret;

	return ret;
}

/**
 * \brief Allocates storage for an operation with two operands
 *
 * \param	type		Operation
 * \param	left_expr	Left expression in the operation
 * \param	right_expr	Right expression in the operation
 * \return				Pointer to the structure holding the operation
 */
Texpr *TRexpr(char type, Texpr *left_expr, Texpr *right_expr)
{
	// Returning struct:
	Texpr		*ret;
	// Internal intermediate storage struct:
	Texpr_op	*expr_op;
	
	// Allocate needed memory
	ret			=	malloc(sizeof(Texpr));
	ret->type	=	malloc(sizeof(char));
	
	expr_op		=	malloc(sizeof(Texpr_op));
	expr_op->op	=	malloc(sizeof(char));
	
	// Initialization
	switch (type)
	{
		case '+':
			*(expr_op->op)	=	OPsum;
			break;
		case '-':
			*(expr_op->op)	=	OPsub;
			break;
		case '*':
			*(expr_op->op)	=	OPmult;
			break;
		case '/':
			*(expr_op->op)	=	OPdiv;
			break;
		case '%':
			*(expr_op->op)	=	OPmod;
			break;
		case '^':
			*(expr_op->op)	=	OPexp;
			break;
	}
	expr_op->left	=	left_expr;
	expr_op->right	=	right_expr;
	
	*(ret->type)	=	OPexpr;
	ret->expr.expr	=	expr_op;
	
	return ret;
}

/**
 * \brief Allocates storage for a function call inside an expr
 *
 * \param	function_call	Function call
 * \return				Pointer to the structure holding the expr
 */
Texpr *TRexpr_fcall(Tsentence *function_call)
{
	// Returning struct:
	Texpr		*ret;
	
	// Allocate needed memory
	ret							=	malloc(sizeof(Texpr));
	ret->type					=	malloc(sizeof(char));
	
	// Initialization
	*(ret->type) 				=	OPmethod_call;
	ret->expr.method_call		=	function_call->sentence.method_call;
	
	// Free unneeded memory
	free(function_call->type);
	free(function_call);
	
	return ret;
}
