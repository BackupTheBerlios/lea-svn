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

#include <stdio.h>
#include "symbol-table.c"

void debug(Tsym_table *symTable)
{
	unsigned int i, j;
	Tsym_list	*symList;
	
	for (i = 0; i < symTable->PRIME; i++)
	{
		printf("hash: %i\n", i);
		symList	= symTable->elements[i];
		j=0;
		while(strcmp(symList->data, ""))
		{
			printf("\tdata[%i][%i] = \"%s\", symList = %i, symList->next = %i\n", i, j, symList->data, symList, symList->next);
			j++;
			symList = symList->next;
		}
		printf("\tdata[%i][%i] = \"%s\"\n", i, j, symList->data);
	}
}

int main(int argc, char *argv[])
{
	int task;
	char *key;
	const unsigned int PRIME = 101;
	uint32_t hash;
	Tsym_table *mySymTable = initSymTable(PRIME);
	
	while(1)
	{
		debug(mySymTable);
		
		printf(	"You can do now the next tasks:\n"
				"\t1. add a symbol\n"\
				"\t2. del a symbol\n"\
				"\t3. get a symbol\n");
		
		scanf("%i", &task);
		
		switch(task) {
			case 1:
				printf("1.1 (add) enter symbol key: ");
				scanf("%s", key);
				
				system("clear");
				
				hash = getHash(key, strlen(key));
				printf("1.2 (add) \"%s\" hash: \"%u\" hash % PRIME: \"%u\"\n", key, hash, hash % PRIME);
				
				if(addSym(mySymTable, key, NULL))
					printf("1.3 (add) Symbol successfully added\n\n");
				else
					printf("1.3 (add) Symbol could not be added\n\n");
				break;
			case 2:
				printf("2.1 (del) enter symbol key: ");
				scanf("%s", key);
				
				system("clear");
				
				hash = getHash(key, strlen(key));
				printf("2.2 (del) \"%s\" hash: \"%u\" hash % PRIME: \"%u\"\n", key, hash, hash % PRIME);
				
				if(delSym(mySymTable, key))
					printf("2.3 (del) Symbol successfully deleted\n\n");
				else
					printf("2.3 (del) Symbol could not be deleted\n\n");
				
				break;
			case 3:
				printf("3.1 (get) enter symbol key: ");
				scanf("%s", key);
				
				system("clear");
				
				hash = getHash(key, strlen(key));
				printf("3.2 (get) \"%s\" hash: \"%u\" hash % PRIME: \"%u\"\n", key, hash, hash % PRIME);
				
				if(getSym(mySymTable, key) == (void *)NULL)
					printf("3.3 (get) Symbol successfully retrieved \n\n");
				else
					printf("3.3 (get) Symbol could not be retrieved\n\n");
				
				break;
		}
	}
	return 0;
}
