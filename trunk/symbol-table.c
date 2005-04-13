/**
 * \file symbol-table.c
 * \brief Smybol table implementation (using hash tables)
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

#include "symbol-table.h"

/**
 * \brief Create a Hash for a given data
 * This function is used verbatim from http://www.azillionmonkeys.com/qed/hash.html
 * © Copyright 2004 by Paul Hsieh. See http://www.azillionmonkeys.com/qed/weblicense.html
 * for license details
 * 
 * \param	data	data from which get a hash
 * \param	len		length of the data string
 * \return	hash	resulting hash
 */
uint32_t getHash(const char *data, size_t len)
{
	uint32_t hash = 0, tmp;
	size_t rem;
	
	if (len <= 0 || data == NULL) return 0;
	
	rem = len & 3;
	len >>= 2;
	
	/* Main loop */
	for (;len > 0; len--) {
		hash	+= get16bits (data);
		tmp		= (get16bits (data+2) << 11) ^ hash;
		hash	= (hash << 16) ^ tmp;
		data	+= 2*sizeof (uint16_t);
		hash	+= hash >> 11;
	}
	
	/* Handle end cases */
	switch (rem) {
		case 3:
			hash += get16bits (data);
			hash ^= hash << 16;
			hash ^= data[sizeof (uint16_t)] << 18;
			hash += hash >> 11;
			break;
		case 2:
			hash += get16bits (data);
			hash ^= hash << 11;
			hash += hash >> 17;
			break;
		case 1:
			hash += *data;
			hash ^= hash << 10;
			hash += hash >> 1;
	}
	
	/* Force "avalanching" of final 127 bits */
	hash ^= hash << 3;
	hash += hash >> 5;
	hash ^= hash << 2;
	hash += hash >> 15;
	hash ^= hash << 10;
	
	return hash;
}

/**
 * \brief Initialize a symbol table
 * 
 * \return	symTable	Initialized symbol table
 */
Tsym_list **initSymTable()
{
	// Allocate memory:
	Tsym_list **symTable = malloc(PRIME * sizeof(Tsym_list *));
	unsigned int i;
	
	// Initialize memory:
	for (i = 0; i < PRIME; i++)
	{
		symTable[i] = malloc (sizeof(Tsym_list));
		symTable[i]->data = calloc(1, sizeof(char));
	}
	
	return symTable;
}
/**
 * \brief Add a symbol to the table
 * Symbol list works similar to a LIFO so that symbols are added to be the first
 * in the symbol list.
 * 
 * \param	symTable	Symbol table to be used
 * \param	data		The data used as the searching key
 * \return	!found		Return 0 (false) only if that data already existed; 1 (true) otherwise
 */
bool addSym(Tsym_list **symTable, const char *data, const void *sym)
{
	size_t		len					= strlen(data);					// Data string length
	uint32_t	hash				= getHash(data, len) % PRIME;	// Array index
	Tsym_list 	*symListActual		= symTable[hash],				// Actual symList element
				*symListNew;										// Smybol to add
	bool		found				= 0;							// Searching loop iterate condition
	
	// Searching loop
	while(!found && strcmp(symListActual->data, ""))
	{
		// Found ! Symbol already exist:
		if (!strcmp(data, symListActual->data))
		{
			found = 1;
		// Not found, reiterate:
		} else
			symListActual = symListActual->next;
	}
	
	// Finally, if symbol was not found, add symbol:
	if (!found)
	{
		symListNew			= malloc(sizeof(Tsym_list));
		symListNew->data	= malloc(len);
		symListNew->sym		= (void *)sym;
		symListNew->next	= symTable[hash];
		strcpy(symListNew->data, data);
		
		symTable[hash] = symListNew;
	}
	
	return !found;
}

/**
 * \brief Delete a symbol in the table
 * 
 * \param	symTable	Symbol table to be used
 * \param	data		The data used as the searching key
 * \return	found		Return 1 (true) only if data was deleted successfully; 0 (false) otherwise
 */
bool delSym(Tsym_list **symTable, const char *data)
{
	size_t		len					= strlen(data);					// Data string length
	uint32_t	hash				= getHash(data, len) % PRIME;	// Array index
	Tsym_list	*symListPrevious	= symTable[hash],				// Previous symlist element
				*symListActual		= symListPrevious;				// Actual symList element
	bool		found				= 0;							// Searching loop iterate condition
	
	// Searching loop
	while(!found && strcmp(symListActual->data, ""))
	{
		// Found !
		if (!strcmp(data, symListActual->data))
		{
			found = 1;
			
			// Deal with extreme cases:
			if (symListPrevious != symListActual)
				symListPrevious->next = symListActual->next;
			else
				symTable[hash] = symListActual->next;
			
			free(symListActual->data);
			free(symListActual);
		// Not found, reiterate:
		} else {
			symListPrevious = symListActual;
			symListActual = symListActual->next;
		}
	}
	
	return found;
}
/**
 * \brief Retrieve a symbol in the table
 * Symbol list wimplements the idea of a rudimentary cache:
 * frequently accessed elements are more accesible (nearer to head).
 * This done by moving one step to head elements each time they are
 * accessed.
 * 
 * \param	symTable	Symbol table to be used
 * \param	data		The data used as the searching key
 * \return	ret			symbol retrieved
 */
const void *getSym(Tsym_list **symTable, const char *data)
{
	const void	*ret			= NULL;							// Returning value
	size_t		len				= strlen(data);					// Data string length
	uint32_t	hash			= getHash(data, len) % PRIME;	// Array index
	Tsym_list	*symList0		= symTable[hash],				// For extreme cases
				*symList1		= symList0,						// For extreme cases
				*symListActual	= symList0,						// Actual symList element
				*symListActualNextTemp;							// Temporal pointer
	bool		found			= 0;							// Searching loop iterate condition
	
	// Searching loop
	while(!found && strcmp(symListActual->data, ""))
	{
		// Found !
		if (!strcmp(data, symListActual->data))
		{
			found = 1;
			ret = symListActual->sym;
			
			// Move one step to head retrieved element:
			// These conditionals deal with extreme cases
			if(symList0 != symList1)
			{
				symList0->next			= symListActual;
				symListActualNextTemp	= symListActual->next;
				symListActual->next		= symList1;
				symList1->next			= symListActualNextTemp;
			} else if(symList1 != symListActual)
			{
				symListActualNextTemp	= symListActual->next;
				symListActual->next		= symList1;
				symList1->next			= symListActualNextTemp;
				symTable[hash]			= symListActual;
			}
		// Not found, reiterate:
		} else {
			// Deal with extreme cases:
			if(symList0 != symList1)
			{
				symList0 = symList1;
				symList1 = symListActual;
				symListActual = symListActual->next;
			} else if(symList1 != symListActual)
			{
				symList1 = symListActual;
				symListActual = symListActual->next;
			} else
				symListActual = symListActual->next;
		}
	}
	
	return ret;
}
