%{
/**
 * \file lea.y
 * \brief Lea Lexical analyzer
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
	#include <stdlib.h>
	#include <string.h>
	#include "y.tab.h"
%}

%option always-interactive

%x comment

D			[0-9]
L			[a-zA-Z_]
H			[a-fA-F0-9]
ID			{L}+{H}*

%%


%{/*
   * This is for scripting  to work:
   * TODO: this should only apply when it's on the first line!
   * TODO: this should determine login_prompt var!
   */
%}
^"#!/"({ID}\/)*{ID}$ /* empty */


%{/*
   * Eat up all C-style comments
   */
%}
"/*" {
	BEGIN(comment);
}


%{/*
   * Eat up all C-style comments
   */
%}
<comment>([^*])+ /* empty */

<comment>"*"+[^*/\n]* /* empty */

<comment>"*"+"/" {
	BEGIN(INITIAL);
}


%{/*
   * Eat up blank spaces, also
   */
%}
[ \t]+ /* empty */


%{/*
   * Integer value recogniced
   */
%}
[0-9]+ {
	yylval.integer_val = atoi(yytext);
	return INT;
}


%{/*
   * Algebraical operator recogniced
   */
%}
[+\-*/()\n] {
	return yytext[0];
}


%{/*
   * Assignation operator recogniced
   */
%}
":=" {
	return EQ;
}


%{/*
   * Variable identifier recogniced
   */
%}
{ID} {
	yylval.string_name = strdup(yytext);
	return INT_VAR;
}


%{/*
   * Throw everything else to the parser
   */
%}
. {
	return yytext;
}

%%
