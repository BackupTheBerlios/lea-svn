/**
 * \file calc.h
 * \brief Functions for the calculator
 *
 * \author Eduardo Robles Elvira <edulix@iespana.es>
 *
 * This is part of calc. calc is free software; 
 * you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * calc is distributed in the hope that it will be useful,
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
 
#ifndef CALC_H
	#define CALC_H
	
	#include <stdlib.h>
	#include <string.h>
	
	/**
	 * Symbol type definition
	 * It stores each variable name and value
	 */
	
	typedef struct {
		char *name;
		int value;
	} symrec;
	
	/**
	 * boolean type
	 */
	typedef enum{false, true} bool;
	
	/**
	 * Types of values for a karnaugh map entry
	 */
	typedef enum{F=0, T=1, I=2} kbool;
	
	/**
	 * Symbols table
	 */
	
	symrec *sptr;
	
	/**
	 * Pointer to the first unused symbol/next symbol to use
	 */
	
	symrec *actual;
	
	/**
	 * Buffer size
	 * When all the Symbols in the Symbols table are already used, 
	 * this is the number of symbols we'll add to the table
	 */
	
	const int buffer = 10;
	
	/**
	 * Number of actual records in the Symbols table.
	 */
	
	int n_records = 0;
	
	/**
	 * Determines if we'll print the login prompt or not.
	 * NOTE: in our implementation, if it's set to I we'll
	 * also print the login prompt
	 */
	
	kbool user_prompt=I;
	
	
	/*
	 * Function prototypes
	 */
	void add_sym(char *name, int value); 
	int get_sym(char *name);
	void set_sym(char *name, int value);
	int exists_symbol(char *name);
	void init_table();
	void prompt();
	
	/*
	 * Function declarations
	 */
	
	/**
	 * Add a new var to the array of them
	 * \param[in]	name	Identifier for the new var
	 * \param[in]	value	Initial value of the var
	 */
	void add_sym(char *name, int value)
	{
		// If we've run out of symbols, add <buffer> more,
		// readjusting 'n_records' and 'actual'.
		if (actual >= &sptr[n_records-2])
		{
			n_records += buffer;
			sptr = realloc(sptr, sizeof(symrec) * (n_records));
			actual = &sptr[n_records - 9];
		}
		
		// Set this symbol's values
		actual->name = malloc(strlen(name));
		actual->name = name;
		actual->value = value;
		
		// Make 'actual' point  to next symbol to be used
		actual++;
	}
	
	/**
	 * Get a var from the array of them by its identifier
	 * 
	 * \param[in]	name	Variable identifier
	 * \return 				Value of that variable, or 0 if it's not in the
	 *						array of vars.
	 */
	int get_sym(char *name)
	{
		int i;
		
		// Go across the array of vars
		for (i = 0; &sptr[i] < actual; i++)
		{
			// If actual var is the one we're looking for, return it's value
			if (strcmp(sptr[i].name, name) == 0)
				return sptr[i].value;
		}
		
		// If there's no var with that name in our array of vars, return 0 (as a default value)
		return 0;
	}
	
	/**
	 * Sets a var to a value. 
	 * If the var doesn't exist in the array of them, create it and assign the
	 * given value.
	 * \param[in]	name	Identifier of the given var
	 * \param[in]	value	Initial value of the var
	 * \see void add_sym(char *name, int value)
	 */
	void set_sym(char *name, int value)
	{
		int i = exists_symbol(name);
		
		if (i >= 0)
			sptr[i].value = value;
		else
			add_sym(name, value);
	}
	
	/**
	 * Let you know if a variable with a given name is in the array
	 * of them, and if so, which is the index position in the array.
	 * \param[in]	name	Identifier of the var to locate
	 * \return				Returns -1 if no variable with such a name
	 *						exists in the array of vars. Otherwise,
	 *						returns the the index position in the array.
	 */
	int exists_symbol(char *name)
	{
		int i;
		
		for (i = 0; &sptr[i] < actual; i++)
		{
			if(strcmp(sptr[i].name, name) == 0)
				return i;
		}
		
		return -1;
	}
	
	/**
	 * Initialise the array of vars.
	 * It allocates some memory for it and set properly enviromental
	 * variables.
	 */
	void init_table()
	{
		// Allocate memory according to buffer
		n_records = buffer;
		sptr = realloc(sptr, sizeof(symrec) * (n_records));
		
		// set actual to next variable symbol to use
		actual = sptr;
	}
	
	/**
	 * Prints a prompt to the user if user_prompt var is not set 0
	 */
	void prompt()
	{
		if (user_prompt != 0)
			printf("> ");
	}

#endif
