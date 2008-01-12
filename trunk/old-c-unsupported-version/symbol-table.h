/**
 * \file symbol-table.h
 * \brief Symbol table header
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

#ifndef SYMBOL_TABLE_H
	#define SYMBOL_TABLE_H
	
	#include <stdlib.h>
	#include <stdint.h>
	#include <string.h>
	/**
	 * \brief bool type definition
	 */
	#ifndef BOOL_TYPE
		#define BOOL_TYPE
		typedef enum {false, true} bool;
	#endif
	
	#undef get16bits
	#if (defined(__GNUC__) && defined(__i386__)) || defined(__WATCOMC__) \
	|| defined(_MSC_VER) || defined (__BORLANDC__) || defined (__TURBOC__)
		#define get16bits(d) (*((const uint16_t *) (d)))
	#endif
	
	#if !defined (get16bits)
		#define get16bits(d) ((((const uint8_t *)(d))[1] << UINT32_C(8))\
		+((const uint8_t *)(d))[0])
	#endif
	
	/**
	 * \brief Tsym_list type definition
	 */
	typedef struct Tsym_list Tsym_list;
	
	struct Tsym_list {
		char *data;
		void *sym;
		Tsym_list *next;
	};
	
	/**
	 * \brief Tsym_table definition
	 */
	typedef struct {
		Tsym_list **elements;
		// number of list elements
		unsigned int PRIME;
	} Tsym_table;
	
	/**
	 * Prototypes definition
	 */
	
	Tsym_table *initSymTable(const unsigned int PRIME);
	bool addSym(Tsym_table *symTable, const char *data, const void *sym);
	bool delSym(Tsym_table *symTable, const char *data);
	const void *getSym(Tsym_table *, const char *data);
	uint32_t getHash(const char *data, size_t len);
#endif
