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
 * These skeleton functions were atuomagically created executing the command:
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
Tinterface_sym *TRproc_arg_list(Tinterface_sym *actual_args, Tinterface_sym *interface)
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
Tother_sym_list *TRin_arg_list(Tother_sym_list *previous_list, Tother_sym *actual_arg)
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
Tother_sym_list *TRout_arg_list(Tother_sym_list *previous_list, Tother_sym *actual_arg)
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
Tother_sym_list *TRinout_arg_list(Tother_sym_list *previous_list, Tother_sym *actual_arg)
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
 * \brief 
 * 
 * \param		
 * \return	 
 */
Tid_list *TRid_list(Tid_list *previous_list, char *actual)
{
	Tid_list *ret;

	return ret;
}

/**
 * \brief 
 * 
 * \param		
 * \return	 
 */
Tint_id_val_list *TRint_val_list(Tint_id_val_list *previous_list, Tint_id_val *actual)
{
	Tint_id_val_list *ret;

	return ret;
}

/**
 * \brief 
 * 
 * \param		
 * \return	 
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
Tother_sym_list *TRconst_dcl_list_bool(Tother_sym_list *previous_list, Tid_list *id_list, bool *value)
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
Tother_sym_list *TRconst_dcl_list_int(Tother_sym_list *previous_list, Tid_list *id_list, int *value)
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
Tother_sym_list *TRconst_dcl_list_float(Tother_sym_list *previous_list, Tid_list *id_list, float *value)
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
Tother_sym_list *TRconst_dcl_list_char(Tother_sym_list *previous_list, Tid_list *id_list, char *value)
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
Tother_sym_list *TRconst_dcl_list_str(Tother_sym_list *previous_list, Tid_list *id_list, char *value)
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
Tother_sym_list *TRconst_dcl_list_reg(Tother_sym_list *previous_list, Tid_list *id_list, Tother_type *reg)
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
Tother_type_list *TRtypes_dcl_list_enum(Tother_type_list *previous_list, Tid_list *id_list, Tstr_list *elements)
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
Tother_type_list *TRtypes_dcl_list_var(Tother_type_list *previous_list, Tid_list *id_list, char *type1, char *type2)
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
Tother_type_list *TRtypes_dcl_list_array(Tother_type_list *previous_list, Tid_list *id_list, Tint_id_val_list *dimensions, char *type)
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
Tother_type_list *TRtypes_dcl_list_reg(Tother_type_list *previous_list, Tid_list *id_list, Tother_type *reg)
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
Tstr_list *TRstr_list(Tstr_list *previous_list, char *actual)
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
Tother_sym_list *TRvars_dcl_var(Tother_sym_list *previous_list, Tid_list *id_list, char *type1, char *type2)
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
Tother_sym_list *TRvars_dcl_array(Tother_sym_list *previous_list, Tid_list *id_list, Tint_id_val_list *dimensions, char *type)
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
Tother_sym_list *TRvars_dcl_reg(Tother_sym_list *previous_list, Tid_list *id_list, Tother_type *type)
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
Tsentence_list *TRsentence_list(Tsentence_list *previous_list, Tsentence *actual)
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
Telif_statement_list *TRelif_statement_list(Telif_statement_list *previous_list, Telif_statement *actual)
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
 * \brief 
 * 
 * \param		
 * \return	 
 */
Tsentence *TRmult_assign_statement(Tvar_sym_list *var_list, Texpr_list *expr_list)
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
Tsentence *TRoutput_input_statement(char *name, Texpr_list *expr_list)
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
Tsentence *TRwhile_loop(Texpr_bool *expr_bool, Tsentence_list *sentence_list)
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
 * \brief 
 * 
 * \param		
 * \return	 
 */
Tsentence *TRfunction_call(char *name, Texpr_list *expr_list)
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
Tsentence *TRstruct_call(Tsentence *previous_list, Tsentence *next_list)
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
Tvar_sym_list *TRvariable_list(Tvar_sym_list *previous_list, Tsentence *next_list)
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
 * \brief 
 * 
 * \param		
 * \return	 
 */
Texpr_list *TRexpr_list(Texpr_list *previous_list, Texpr *actual)
{
	Texpr_list *ret;

	return ret;
}

/**
 * \brief 
 * 
 * \param		
 * \return	 
 */
Texpr_bool *TRexpr_bool_val(bool *val)
{
	Texpr_bool *ret;

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
 * \brief 
 * 
 * \param		
 * \return	 
 */
Texpr_bool *TRexpr_bool_not(Texpr_bool *expr_bool)
{
	Texpr_bool *ret;

	return ret;
}

/**
 * \brief 
 * 
 * \param		
 * \return	 
 */
Texpr_bool *TRexpr_bool_log(char type, Texpr_bool *left_expr, Texpr_bool *right_expr)
{
	Texpr_bool *ret;

	return ret;
}

/**
 * \brief 
 * 
 * \param		
 * \return	 
 */
Texpr_bool *TRexpr_bool(char type, Texpr *left_expr, Texpr *right_expr)
{
	Texpr_bool *ret;

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
 * \brief Allocates storage for an integer expresion value
 * 
 * \param	int_val	Value to preserve
 * \return			Pointer to the expresion holding the given value
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
 * \brief Allocates storage for a boolean expresion value
 *
 * \param	bool_val	Value to preserve
 * \return				Pointer to the expresion holding the given value
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
 * \brief Allocates storage for a float expresion value
 *
 * \param	float_val	Value to preserve
 * \return				Pointer to the expresion holding the given value
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
 * \brief Allocates storage for a str expresion value
 *
 * \param	str	Value to preserve
 * \return		Pointer to the expresion holding the given value
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
 * \brief 
 * 
 * \param		
 * \return	 
 */
Texpr *TRexpr(char type, Texpr *left_expr, Texpr *right_expr)
{
	Texpr *ret;

	return ret;
}

/**
 * \brief 
 * 
 * \param		
 * \return	 
 */
Texpr *TRexpr_fcall(Tsentence *function_call)
{
	Texpr *ret;

	return ret;
}
