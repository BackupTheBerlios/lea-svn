#!/bin/awk -f
# /**
#  * \file handy.awk
#  * \brief  Handy bunch of subroutines
#  *
#  * \author Eduardo Robles Elvira <edulix@iespana.es>
#  *
#  * This is part of Lea. Lea is free software; 
#  * you can redistribute it and/or
#  * modify it under the terms of the GNU General Public License
#  * as published by the Free Software Foundation; either version 2
#  * of the License, or (at your option) any later version.
#  * 
#  * Lea is distributed in the hope that it will be useful,
#  * but WITHOUT ANY WARRANTY; without even the implied warranty of
#  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  * GNU General Public License for more details.
#  * 
#  * You should have received a copy of the GNU General Public License
#  * along with Lea; if not, write to the Free Software
#  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
#  * 
#  * See COPYING for details.
#  */

# /**
#  * \brief User can select which action to execute setting the $ACTION var
#  */
BEGIN {
	"echo $ACTION" | getline action
	
	if (action ~ /^print_rules$/) { print_rules() } else 
	if (action ~ /^print_action_rules$/) { print_action_rules() }
}

# /**
#  * \brief This function prints the list of (yacc/bison type)rule names separated with spaces
#  */
function print_rules()
{
	while (getline line)
	{
		if (line ~ /[a-zA-Z_][a-zA-Z0-9_]*:$/)
		{
			printf("%s ", substr(line, 0, length(line) - 1))
		}
	}
	print "\n"
}

# /**
#  * \brief Print the list of function calls in a yacc/bison file, marking with a comment which rules are them in
#  */
function print_action_rules()
{
	while (getline line)
	{
		if (line ~ /[a-zA-Z_][a-zA-Z0-9_]*:$/)
		{
			new_rule="true"
			rule=line
		} 
		else if (line ~ /\{[ \t]*\$\$[ \t]*=[ \t]*[^}]+\}$/)
		{
			line = gensub(/\{[ \t]*\$\$[ \t]*=[ \t]*([^}]*)[ \t]*\}$/, "\\1", "g", line)
			if (line ~ /[ \t]*NULL;/)
			{
				if (new_rule ~ "true")
				{
					printf("// %s \n", rule)
					new_rule="false"
				}
				
				printf("// %s \n", line)
			} else if (line !~ /[ \t]*(\$[0-9]);/)
			{
				if (new_rule ~ "true")
				{
					printf("// %s \n", rule)
					new_rule="false"
				}
				
				print line
			}
		}
	}
}
