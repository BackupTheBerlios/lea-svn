%{
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
