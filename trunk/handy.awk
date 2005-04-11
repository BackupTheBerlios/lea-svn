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
#  * as published by the Free Software Foundation; version 2
#  * of the License.
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
	if (ENVIRON["ACTION"] ~ /^print_rules$/) { print_rules() } else 
	if (ENVIRON["ACTION"] ~ /^print_action_rules$/) { print_action_rules() } else 
	if (ENVIRON["ACTION"] ~ /^print_skeleton_functions$/) { print_skeleton_functions() } else 
	if (ENVIRON["ACTION"] ~ /^print_grammar_no_actions$/) { print_grammar_no_actions() } else 
	if (ENVIRON["ACTION"] ~ /^print_rule_types$/) { print_rule_types() } else 
	if (ENVIRON["ACTION"] ~ /^print_union_types$/) { print_union_types() }
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
#  * \brief Print the list of function calls of a yacc/bison file (readed from stdin), 
#  * indicating with a comment which rules are them in
#  */
function print_action_rules()
{
	while (getline line)
	{
		if (line ~ /[a-zA-Z_][a-zA-Z0-9_]*:$/)
		{
			new_rule=1
			rule=line
		} 
		else if (line ~ /\{[ \t]*\$\$[ \t]*=[ \t]*[^}]+\}$/)
		{
			line = gensub(/\{[ \t]*\$\$[ \t]*=[ \t]*([^}]*)[ \t]*\}$/, "\\1", "g", line)
			if (line ~ /[ \t]*NULL;/)
			{
				if (new_rule ~ 1)
				{
					printf("// %s \n", rule)
					new_rule=0
				}
				
				printf("// %s \n", line)
			} else if (line !~ /[ \t]*(\$[0-9]);/)
			{
				if (new_rule ~ 1)
				{
					printf("// %s \n", rule)
					new_rule=0
				}
				
				print line
			}
		}
	}
}

# /**
#  * \brief Print the skeleton of a list of functions based on its 
#  * prototipe declarations
#  */

function print_skeleton_functions()
{
	while (getline line)
	{
		if (line ~ /^[ \t]*[a-zA-Z_][a-zA-Z0-9_]*[ \t]*\*[a-zA-Z_][a-zA-Z0-9_]*\([a-zA-Z0-9_ ,*\t]+\);[ \t]*$/)
		{
			print "\n/**\n * \\brief \n * \n * \\param\t\t\n * \\return\t \n */"
			printf("%s\n{\n", gensub(/^[ \t]*([a-zA-Z_][a-zA-Z0-9_]*[ \t]*\*[a-zA-Z_][a-zA-Z0-9_]*\([a-zA-Z0-9_ ,*\t]+\));[ \t]*$/, "\\1","g", line))
			printf("\t%s *ret;\n\n\treturn ret;\n}\n", gensub(/^[ \t]*([a-zA-Z_][a-zA-Z0-9_]*)[ \t]*\*[a-zA-Z_][a-zA-Z0-9_]*\([a-zA-Z0-9_ ,*\t]+\);[ \t]*$/, "\\1","g", line))
		}
	}
}

# /**
#  * \brief Print a bison like file *but* without printing actions
#  */

function print_grammar_no_actions()
{
	print "%{\n/*This file was generated executing the following command in parent directory:\n \
	 $ ACTION=print_grammar_no_actions ./handy.awk ../../trunk/lea.y > lea.y */\n%}\n"
	while(getline line)
	{
		if (line ~ /\{[ \t]*\$\$[ \t]*=[ \t]*[^}]+\}$/)
		{
			print "\t\t{  }"
		} else
		{
			print line;
		}
	}
}

# /**
#  * \brief Print the type specifications for a bison-like script
#  */
function print_rule_types()
{
	# First get all the Translation functions and its types from lea-translator.h
	
	while(getline line < "lea-translator.h")
	{
		if (line ~ /^[ \t]*[a-zA-Z_][a-zA-Z0-9_]*[ \t]+\*TR[a-zA-Z0-9_]*\([a-zA-Z0-9_ ,*\t]+\);[ \t]*$/)
		{
			new_name = gensub(/^[ \t]*[a-zA-Z_][a-zA-Z0-9_]*[ \t]+\*(TR[a-zA-Z0-9_]*)\([a-zA-Z0-9_ ,*\t]+\);[ \t]*$/, "\\1","g", line)
			type = gensub(/^[ \t]*([a-zA-Z_][a-zA-Z0-9_]*)[ \t]+\*TR[a-zA-Z0-9_]*\([a-zA-Z0-9_ ,*\t]+\);[ \t]*$/, "\\1","g", line)
				TYPES_ARRAY[new_name] = type
				last_name = new_name
		}
	}
	
	close("lea-translator.h")
	
	# Now for each rule in the bison-like script, locate the first funcion call,
	# and asthe remaining function calls will return the same type that's all we
	# need to know of the rule.
	# Then add actual rule to 
	
	while (getline line)
	{
		if (line ~ /[a-zA-Z_][a-zA-Z0-9_]*:$/)
		{
			new_rule = "1"
			rule=gensub(/([a-zA-Z_][a-zA-Z0-9_]*):$/, "\\1", "g", line)
		}
		else if (line ~ /\{[ \t]*\$\$[ \t]*=[ \t]+TR[a-zA-Z0-9_]+\([a-zA-Z0-9_ ,*\t\$]+\);[ \t]*\}$/ && new_rule ~ "1")
		{
			name = gensub(/\{[ \t]*\$\$[ \t]*=[ \t]+([a-zA-Z0-9_]*)\([a-zA-Z0-9_ ,*\t\$]+\);[ \t]*\}$/, "\\1","g", line)
			name = gensub(/[ \t]*([^ \t]+)/, "\\1", "g", name);
			type = TYPES_ARRAY[name]
			
			# Need to check if that type exists (it's not "") because the rule could be comented
			# in the code and thus the function called might not be prototyped in "lea-translator.h"
			if (type)
			{
				TYPE_RULES_LIST[type] = TYPE_RULES_LIST[type] " " rule
				new_rule="0"
			}
		}
	}
	
	# Finally, print the required list of types & rules
	for(actual in TYPE_RULES_LIST)
	{
		print "%type <" actual ">" TYPE_RULES_LIST[actual]
	}
}

# /**
#  * \brief Print the var delarations that should be included in %union
#  */
function print_union_types()
{
	# First get all the Translation functions and its types
	
	print "//Insert the next code into %union { <here> }\n"
	
	while(getline line)
	{
		if (line ~ /^[ \t]*[a-zA-Z_][a-zA-Z0-9_]*[ \t]+\*TR[a-zA-Z0-9_]*\([a-zA-Z0-9_ ,*\t]+\);[ \t]*$/)
		{
			name = gensub(/^[ \t]*[a-zA-Z_][a-zA-Z0-9_]*[ \t]+\*(TR[a-zA-Z0-9_]*)\([a-zA-Z0-9_ ,*\t]+\);[ \t]*$/, "\\1","g", line)
			type = gensub(/^[ \t]*([a-zA-Z_][a-zA-Z0-9_]*)[ \t]+\*TR[a-zA-Z0-9_]*\([a-zA-Z0-9_ ,*\t]+\);[ \t]*$/, "\\1","g", line)
			if (!(type in CHECK_TYPE_ARRAY))
			{
				print type " *" type ";"
				TYPES_ARRAY[name] = type
				CHECK_TYPE_ARRAY[type] = "1"
			}
		}
	}
	
	print "// End %union code"
}
