///////////////////////////////
// Analizador léxico
///////////////////////////////

class Analex extends Lexer;

options {
	charVocabulary = '\3'..'\377';
	k=2;
}

tokens {
	FLOAT_VAL;
	INT_VAL;
	
	PROG="prog";
	ALG="alg";
	FUNC="func";
	AND="y";
	OF="de";
	
	INPUT="entrada";
	OUTPUT="salida";
	INOUT="entsal";
	IN="ent";
	OUT="sal";
	DEV="dev";
	PROC="proc";
	END="fin";
	
	
	CONSTS="cons";
	TYPES="tipos";
	ARRAY="tabla";
	REG="reg";
	ENDREG="freg";
	VARS="var";
	START="prin";
	
	WRITE="escribir";
	READ="leer";
	
	IF="si";
	ELSE="otras";
	IS_NULL="nula";
	ENDIF="fsi";
	
	WHILE="mientras";
	ENDWHILE="fm";
	
	FROM="desde";
	TO="hasta";
	ENDFROMTO="fd";
	
	OR="o";
	NOT="no";
	
	
	
	TRUE="verdadero";
	FALSE="falso";
}

COMMA:',';
ASSIGN:":=";
LE_OP:"<=";
GE_OP:">=";
L_OP:"<";
G_OP:">";
NOT_EQ:"<>";
EQ:"=";
P:'(';
EP:')';
K:'{';
EK:'}';
B:'[';
EB:']';
DOT:'.';
SC:';';
C:':';
BAR:'|';
PLUS:'+';
MINUS:'-';
MOD:'%';
MULT:'*';
DIV:'/';
RAISE:'^';
protected NL: ('\n'|"\r\n"){ newline(); };

COMMENT: "//" (~('\n'|'\r'))*NL{ newline(); }  { $setType(Token.SKIP);};
COMMENT_C: "/*" ('*' ~('/') | ~('*'))* "*/"  { $setType(Token.SKIP);};
STR_VAL: '"' ((NL|~('"')))* '"';
WHITE: (' '|'\t')+ { $setType(Token.SKIP);};
protected DIGIT:('0'..'9');
protected ALFA:('a'..'z'|'A'..'Z'|'_');
protected ALFANUM:(ALFA|DIGIT);

SCRIPT:"#!"(~('\n'|'\r'))+('\n'|"\r\n" { newline(); });

NUMBER: 
	((DIGIT)+ '.') => (DIGIT)+ '.' (DIGIT)+ { $setType(FLOAT_VAL); }
	| (DIGIT)+ { $setType(INT_VAL);};

ID:ALFA(ALFANUM)*;
NLS: (NL(WHITE)?)+;

///////////////////////////////
// Analizador sintáctico
///////////////////////////////
class Anasint extends Parser;

options{
	buildAST = true;
}
tokens {
	DECLARATIONS_BLOCK;
	SENTENCES;
	IF_SENTENCE;
	PROC_CALL;
	ASSIGNMENT;
	IO_STATEMENT;
	WHILE_LOOP;
	FROMTO_LOOP;
	LIBRARY;
	ALGORITHM;
	FUNCTION;
	PROCEDURE;
	ID_LIST;
	ARRAY_DIMENSIONS;
	PROGRAM;
	HEADER;
	
}
program!:
	a:prog_header
	b:declarations_block
	c:sentence_list_block
	d:library
	EOF!
	{
		#program = #(#[PROGRAM, "PROGRAM"], #a, #b, #c, #d);
	}
;

prog_header:
	(SCRIPT!)? (NLS!)? PROG^ id:ID (NLS!)
;

library:
	(algorithm | function | procedure)*
	{
		#library = #(#[LIBRARY, "LIBRARY"], ##);
	}
;


algorithm:
	alg_header
	interface_block
	declarations_block
	sentence_list_block
	{
		#algorithm = #(#[ALGORITHM, "ALGORITHM"], ##);
	}
;

function:
	func_header
	declarations_block
	sentence_list_block
	{
		#function = #(#[FUNCTION, "FUNCTION"], ##);
	}
;

procedure:
	proc_header
	declarations_block
	sentence_list_block
	{
		#procedure = #(#[PROCEDURE, "PROCEDURE"], ##);
	}
;

alg_header:
	ALG! ID (NLS!)
;

func_header:
	FUNC! ID
	P! in_arg_list EP!  DEV! P! func_out_var_dcl EP! (NLS!)
	{
		#func_header = #(#[HEADER, "HEADER"], ##);
	}
;

func_out_var_dcl:
out_var_dcl
	{
		#func_out_var_dcl = #(#[DEV, "DEV"], ##);
	}
;

proc_header:
	PROC! ID
	P! proc_arg_list EP! (NLS!)
	{
		#proc_header = #(#[HEADER, "HEADER"], ##);
	}
;

interface_block:
	(IN^ in_arg_list (NLS!) | OUT^ out_arg_list (NLS!))*
;

proc_arg_list:
	(proc_arg  (SC! proc_arg)*)?
;

proc_arg:
	(IN^ in_arg_list | OUT^ out_arg_list | INOUT^ inout_arg_list)
;

in_arg_list:
	(in_var_dcl (COMMA! in_var_dcl)*)?
;

out_arg_list:
	(out_var_dcl (COMMA! out_var_dcl)*)?
;

inout_arg_list:
	(inout_var_dcl (COMMA! inout_var_dcl)*)?
;

common_var_dcl:
	id_list   C^ (ID (OF! ID)? | ARRAY! array_dimensions OF! ID)
;

in_var_dcl:
	id_list C^ (ID (OF! (ID | INPUT OF! ID))? | ARRAY! array_dimensions OF! ID)
;

out_var_dcl:
	id_list C^ (ID (OF! (ID | OUTPUT OF! ID))? | ARRAY! array_dimensions OF! ID)
;

inout_var_dcl:
	id_list C^ (ID (OF! (ID | INPUT AND OUTPUT OF! ID))? | ARRAY! array_dimensions OF! ID)
;

id_list:
	ID (COMMA! ID)*
	{
		#id_list = #(#[ID_LIST, "ID_LIST"], ##);
	}
;

array_dimensions:
	B! int_val_list EB!
	{
		#array_dimensions = #(#[ARRAY_DIMENSIONS, "ARRAY_DIMENSIONS"], ##);
	}
;

int_val_list:
	int_id_val (COMMA! int_id_val)*
;

int_id_val:
	INT_VAL
	| ID
;

declarations_block:
	(consts_block)?
	(types_block)?
	(vars_block)?
	{
		#declarations_block = #(#[DECLARATIONS_BLOCK, "DECLARATIONS_BLOCK"], ##);
	}
;

consts_block:
	CONSTS^ (NLS!)
		(const_dcl)*
;

const_dcl:
	id_list C^ (TRUE | FALSE | INT_VAL | FLOAT_VAL | CHAR_VAL | STR_VAL | reg_init register) (NLS!)
;

types_block:
	TYPES^ (NLS!)
		(type_dcl)*
;

type_dcl:
	id_list   C^ (ID (OF! ID)? | ARRAY! array_dimensions OF! ID | P! id_list EP! | reg_init register) (NLS!)
;

vars_block:
	VARS^ (NLS!)
		(var_dcl)*
;

var_dcl:
	id_list   C^ (ID (OF! ID)? | ARRAY! array_dimensions OF! ID | reg_init register) (NLS!)
;

reg_init:
	(NLS!)? REG! (NLS!)
;

register:
		common_var_dcl (NLS!)
		(common_var_dcl (NLS!))*
	ENDREG!
;

sentence_list_block:
	START! (NLS!)?
		sentence_list
	END! (NLS!)?
;

sentence_list:
	(sentence)*
	{
		#sentence_list = #(#[SENTENCES, "SENTENCES"], ##);
	}
;

sentence_list2:
	(sentence)+
	{
		#sentence_list2 = #(#[SENTENCES, "SENTENCES"], ##);
	}
;

sentence:
	if_statement
	{
		#sentence = #(#[IF_SENTENCE, "IF_SENTENCE"], ##);
	}
	| (ID P) => procedure_call
	{
		#sentence = #(#[PROC_CALL, "PROC_CALL"], ##);
	}
	| assign_statement
	{
		#sentence = #(#[ASSIGNMENT, "ASSIGNMENT"], ##);
	}
	| output_input_statement
	{
		#sentence = #(#[IO_STATEMENT, "IO_STATEMENT"], ##);
	}
	| while_loop
	{
		#sentence = #(#[WHILE_LOOP, "WHILE_LOOP"], ##);
	}
	| fromto_loop
	{
		#sentence = #(#[FROMTO_LOOP, "FROMTO_LOOP"], ##);
	}
;

if_statement:
	IF! expr_bool C! (NLS!)?
		sentence_list
	elif_statement_list
;

elif_statement_list:
	(BAR ELSE) => BAR! ELSE C! (NLS!)?
		(sentence_list2 | IS_NULL (NLS!))
	ENDIF (NL!)+
	| BAR expr_bool C! ((NL!)+)?
		(sentence_list | IS_NULL (NLS!))
	elif_statement_list
;


assign_statement:
	struct_call ASSIGN! (expr | mult_assign) (NLS!)
;

mult_assign:
	K! mult_assign_list EK!
;

mult_assign_list:
	(expr | mult_assign) (COMMA! (expr | mult_assign))*
;

output_input_statement:
	(READ | WRITE) ((P) => P! expr_list_full EP! | expr_list_full) (NLS!)
;


while_loop:
	WHILE! expr_bool (NLS!)
		sentence_list
	ENDWHILE! (NLS!)
;

fromto_assign_statement:
	struct_call ASSIGN! expr
	| P! struct_call ASSIGN! expr EP!
;

fromto_loop:
	FROM! fromto_assign_statement TO! expr (NLS!)
		sentence_list
	ENDFROMTO! (NLS!)
;

function_call:
	ID P! expr_list EP!
;

variable_call:
	ID (B! expr_list_full EB!)?
;

struct_call:
	variable_call (DOT! variable_call)*
	{
		#struct_call = #(#[STRUCT_CALL, "STRUCT_CALL"], ##);
	}
;

procedure_call:
	ID P! expr_list EP! (NLS!)
;

expr_list:
	(expr_list_full)?
;

expr_list_full:
	expr (COMMA! expr)*
;



expr_bool: expr
;

expr:
	expr_and (OR^ expr_and (OR! expr_and)*)?
;

expr_and:
	expr_eq (AND^ expr_eq (AND! expr_eq)*)?
;

expr_eq:
	expr_rel ((EQ^ | NOT_EQ^) expr_rel)?
;

expr_rel:
	expr_sum ((LE_OP^ | GE_OP^ | L_OP^ | G_OP^) expr_sum)?
;

expr_sum:
	expr_mult ((PLUS^ | MINUS^) expr_mult ((PLUS | MINUS) expr_mult))?
;

expr_mult:
	expr_raise ((MULT^ | DIV^ | MOD^) expr_raise ((MULT | DIV | MOD) expr_raise)*)?
;

expr_raise:
	expr_prefix ((RAISE^) expr_prefix ((RAISE) expr_prefix)*)?
;

expr_prefix:
	(PLUS | MINUS) expr_base
	{
		#expr_prefix = #(#[PREFIX, "PREFIX"], ##);
	}
	| expr_base
;

expr_base:
	INT_VAL
	| FLOAT_VAL
	| STR_VAL
	| (ID P) => function_call
	| struct_call
	| P! expr EP!
	{
		#expr_base = #(#[EXPR, "EXPR"], ##);
	}
	| TRUE
	| FALSE
;

///////////////////////////////
// Evaluador de expresiones
///////////////////////////////
{
	
 import java.util.Hashtable;
 import java.util.Map.Entry;
 import com.sun.xml.internal.fastinfoset.util.StringArray;
}
class Evaluator extends TreeParser;

{
 int regCount = 0;
 String tempString;
 Hashtable<String, String> commonTypes = new Hashtable<String, String>();
 
 protected String[] getArray(StringArray sa)
 {
 	String []a = new String[sa.getSize()];
 	for(int i = 0; i < sa.getSize(); i++)
 		a[i] = sa.get(i);
 	return a;
 }
 protected String getType(String type)
 {
 	if(commonTypes.containsKey(type))
 		return commonTypes.get(type);
 	else
 		return type;
 }
 
 protected void initialize()
 {
	commonTypes.put("logico", "boolean");
	commonTypes.put("real", "float");
	commonTypes.put("cadena", "String");
	commonTypes.put("entero", "int");
	commonTypes.put("caracter", "char");
 }
}

program  returns [String []javaCode = {null, null}]
	{
		String a[];
		String b, c, d; initialize();
	}:
	#(PROGRAM
		a=prog_header
		b=declarations_block["static"]
		c=sentence_list_block
		d=library)
	{
		javaCode[0] = a[0] + b +
		"public static void main(String args[]) {\n"
		+ c + "}\n"
		+ d + "};\n";
		javaCode[1] = a[1];
	}
;

prog_header returns [String []javaCode = {null, null}]:
	#(PROG  id:ID)
	{
		String p = id.getText();
		p = p.substring(0,1).toUpperCase() + p.substring(1, p.length());
		
		javaCode[0] = "import java.io.*;\n\n" + 
		"class " + p + " {\n" +
		"static BufferedReader __in = new BufferedReader(\n" +
		"		    new InputStreamReader(System.in));\n"; 
		javaCode[1] = p;
	}
;

library returns [String javaCode = null]
	{ StringBuffer s = new StringBuffer(); String a; }:
	#(LIBRARY
	(a=function
	{
		s.append(a);
	} | a=procedure
	{
		s.append(a);
	}
	
	)*)
	{
		javaCode = s.toString();
	}
;

function returns [String javaCode = null]
	{
		StringBuffer sb = new StringBuffer();
		String a[];
		String b, c;
	}:
	#(FUNCTION
	a=func_header[sb]
	b=declarations_block[""]
	c=sentence_list_block)
	{
		javaCode = a[0] + sb.toString() + b + c + a[1] + "}\n";
	}
;

procedure returns [String javaCode = null]
	{
		StringBuffer sb = new StringBuffer();
		String a, b, c;
	}:
	#(PROCEDURE
	a=proc_header[sb]
	b=declarations_block[""]
	c=sentence_list_block)
	{
		javaCode = a + "{\n" + sb.toString() + b + c + "}\n";
	}
;

// func_out_var_dcl[0] es el tipo que devuelve
// func_out_var_dcl[1] es la lista de declaraciones
// func_out_var_dcl[2] es la sentencia return
// javaCode[0] es el codigo de la cabecera
// javaCode[1] es func_out_var_dcl[2]
func_header[StringBuffer sb] returns [String []javaCode = {null, null}]
	{ String b = ""; String []c; }:
	#(HEADER
	a:ID
	(b=in_arg_list[sb])?
	#(DEV c=func_out_var_dcl))
	{
		javaCode[0] = "static private " + c[0] + " " + a.getText()
		+ "(" + b + ")\n{\n" + c[1];
		javaCode[1] =  c[2];
	}
;

proc_header[StringBuffer sb] returns [String javaCode = null]
	{ StringBuffer s = new StringBuffer(""); String b; }:
	#(HEADER
	a:ID
	(b=proc_arg[sb]
	{
		s.append(b + ", ");
	}
	)+)
	{
		
		javaCode = s.toString();
		javaCode = javaCode.substring(0, javaCode.length()-2);
		javaCode = "static private void " + a.getText() + "(" + javaCode + ")\n";
	}
;

// TODO: comprobar que IN, OUT, INOUT sean correctos
// por ahora no se hace por simplicidad
proc_arg[StringBuffer sb] returns [String javaCode = ""]:
	#(IN javaCode=in_arg_list[sb])
	| #(OUT javaCode=out_arg_list[sb])
	| #(INOUT javaCode=inout_arg_list[sb])
;

in_arg_list[StringBuffer sb] returns [String javaCode = ""]
	{ StringBuffer s = new StringBuffer(""); String a; }:
	(a=in_var_dcl[sb]
	{
		s.append(a + ", ");
	}
	)+
	{
		javaCode = s.toString();
		javaCode = javaCode.substring(0, javaCode.length()-2);
	}
;

out_arg_list[StringBuffer sb] returns [String javaCode = ""]
	{ StringBuffer s = new StringBuffer(""); String a; }:
	(a=out_var_dcl[sb]
	{
		s.append(a + ", ");
	}
	 )+
	{
		javaCode = s.toString();
		javaCode = javaCode.substring(0, javaCode.length()-2);
	}
;


inout_arg_list[StringBuffer sb] returns [String javaCode = ""]
	{ StringBuffer s = new StringBuffer(""); String a; }:
	(a=inout_var_dcl[sb]
	{
		s.append(a + ", ");
	}
	)+
	{
		javaCode = s.toString();
		javaCode = javaCode.substring(0, javaCode.length()-2);
	}
;



common_var_dcl [String terminator, StringBuffer sb] returns [String javaCode = ""]
	{
		StringBuffer s = new StringBuffer();
		String il[], ad[];
		String type;
	}:
	#(C il=id_list ( (id1:ID (id2:ID)?)
	{
		if(id2 != null && id2.getText() != null)
		{
			if(id1.getText() != "fichero")
				throw new Exception("error de sintaxis");
			else {
				type = "Fichero<" + getType(id2.getText()) + ">";
			}
		} else {
			type = getType(id1.getText());
		}
		for(int i = 0; i < il.length; i++)
		{
			s.append(type + " " + il[i] + terminator);
		}
		javaCode = s.toString();
	}
	| (ad=array_dimensions id3:ID)
	{	
		if(sb == null)
			for(int i = 0; i < il.length; i++)
				s.append(getType(id3.getText()) + " " + il[i] + ad[1]);
		else
			for(int i = 0; i < il.length; i++)
			{
				s.append(getType(id3.getText()) + " " + il[i] + ad[1]);
				sb.append(il[i] + " = new " + getType(id3.getText()) + ad[0] + ";\n");
			}
			
		javaCode = s.toString();
	}
	))
;
exception catch [Exception e]
{
	javaCode = "";
}

// func_out_var_dcl[0] es el tipo que devuelve
// func_out_var_dcl[1] es la lista de declaraciones
// func_out_var_dcl[2] es la sentencia return
func_out_var_dcl returns [ String []ret = {null, null, null} ]
	{
		StringBuffer s = new StringBuffer();
		String il[], ad[];
		String type;
	}:
	#(C il=id_list ( (id1:ID (id2:ID)?)
	{
		if(id2 != null && id2.getText() != null)
		{
			if(id1.getText() != "fichero")
				throw new Exception("error de sintaxis");
			else {
				type = "Fichero<" + getType(id2.getText()) + ">";
			}
		} else {
			type = getType(id1.getText());
		}
		for(int i = 0; i < il.length; i++)
		{
			s.append(type + " " + il[i] + ";\n");
		}
		ret[0] = type;
		ret[1] = s.toString();
		ret[2] = "return " + il[0] + ";\n";
	}
	| (ARRAY ad=array_dimensions id3:ID)
	{	
		for(int i = 0; i < il.length; i++)
		{
			s.append(getType(id3.getText()) + " " + il[i] + ad[1] + " = new " + getType(id3.getText()) + ad[0] + ";\n");
		}
		ret[0] = getType(id3.getText()) + ad[0];
		ret[1] = s.toString();
		ret[2] = "return " + il[0] + ";\n";
	}
	))
;
exception catch [Exception e] {
	// nada, por ahora
}

in_var_dcl[StringBuffer sb] returns [String javaCode = ""]:
javaCode=common_var_dcl["", sb]
;

out_var_dcl[StringBuffer sb] returns [String javaCode = ""]:
javaCode=common_var_dcl["", sb]
;

inout_var_dcl[StringBuffer sb] returns [String javaCode = ""]:
javaCode=common_var_dcl["", sb]
;

id_list returns [String []ret = null]
	{StringArray s = new StringArray();}:
	#(ID_LIST (id:ID
	{
		s.add(id.getText());
	}
	)+)
	{
		ret = getArray(s);
	}
;

array_dimensions returns [String []javaCode = {null, null}]
	{StringBuffer s = new StringBuffer(), s2 = new StringBuffer(); String a; }:
	#(ARRAY_DIMENSIONS (a=int_id_val
	{
		s.append("[" + a + "]");
		s2.append("[]");
	}
	)+)
	{
		javaCode[0] = s.toString();
		javaCode[1] = s2.toString();
	}
;


int_id_val returns [String javaCode = null]:
	a1:INT_VAL
	{
		javaCode = a1.getText();
	}
	| a2:ID
	{
		javaCode = a2.getText();
	}
;

declarations_block[String prefix] returns [String javaCode = null]
	{ String a = "", b = "", c = ""; }:
	#(DECLARATIONS_BLOCK
	(a=consts_block[prefix])?
	(b=types_block)?
	(c=vars_block[prefix])?)
	{
		javaCode = a + b + c;
	}
;

consts_block[String prefix] returns [String javaCode = null]
	{ StringBuffer s = new StringBuffer(); String a; }:
	#(CONSTS
	(a=const_dcl[prefix]
	{
		s.append(a);
	}
	)*)
	{
		javaCode = s.toString();
	}
;

const_dcl[String prefix] returns [String javaCode = null]
	{
		StringBuffer sb = new StringBuffer();
		String[] il;
		String type, value;
	}:
	#(C il=id_list (
	TRUE
	{
		type = "final boolean";
		value = "true";
	}
	| FALSE
	{
		type = "final boolean";
		value = "false";
	}
	| i:INT_VAL
	{
		type = "final int";
		value = i.getText();
	}
	| f:FLOAT_VAL
	{
		type = "final float";
		value = f.getText();
	}
	| c:CHAR_VAL
	{
		type = "final char";
		value = c.getText();
	}
	| s:STR_VAL
	{
		type = "final String";
		value = s.getText().replaceAll("\n", "\\\\n\" +\n\"");
	}
	// TODO: register val
	))
	{
		for(int j = 0; j < il.length; j++)
		{
			sb.append(prefix + " " + type + " " + il[j] + " = " + value + ";\n");
		}
		javaCode = sb.toString();
	}
;

types_block returns [ String javaCode =  null ]
	{
		StringBuffer s = new StringBuffer(); String t;
	}:
	#(TYPES
	(t=type_dcl
	{
		s.append(t);
	}
	)*)
	{
		javaCode = s.toString();
	}
;

type_dcl returns [String javaCode = ""]
	{
		StringBuffer s = new StringBuffer();
		String id_list[], id_list2[], ad[];
		String type, reg;
	}:
	#(C id_list=id_list ( (id1:ID (id2:ID)?)
	{
		if(id2 != null && id2.getText() != null)
		{
			if(id1.getText() != "fichero")
				throw new Exception("error de sintaxis");
			else {
				type = "Fichero<" + getType(id2.getText()) + ">";
			}
		} else {
			type = getType(id1.getText());
		}
		for(int i = 0; i < id_list.length; i++)
		{
			commonTypes.put(id_list[i], type);
		}
	}
	| (ad=array_dimensions id3:ID)
	{	
		for(int i = 0; i < id_list.length; i++)
		{
			commonTypes.put(id_list[i], getType(id3.getText()) + ad[0]);
		}
	}
	| id_list2=id_list
	{
		for(int i = 0; i < id_list.length; i++)
		{
			commonTypes.put(id_list[i], getType(id_list2[i]));
		}
	}
	| reg=register
	{
		javaCode = "class __reg" + regCount + " {\n" + reg + "};\n";
		
		for(int i = 0; i < id_list.length; i++)
		{
			commonTypes.put(id_list[i], "__reg" + regCount);
		}
		regCount++; 
	}
	))
;
exception catch [Exception e] {
	// nada, por ahora
}

vars_block[String prefix] returns [String javaCode = ""]
	{
		StringBuffer s = new StringBuffer();
		String v;
	}:
	#(VARS
	(v=var_dcl[prefix]
	{
		s.append(v);
	}
	)*)
	{
		javaCode = s.toString();
	}
;

var_dcl[String prefix] returns [String javaCode = ""]
	{
		StringBuffer s = new StringBuffer();
		String type, reg;
		String []il;
		String []ad;
		boolean f = false;
	}:
	#(C il=id_list ( (id1:ID (id2:ID { f = true; })?)
	{
		if(f == true)
		{
			if(id1.getText() != "fichero")
				throw new Exception("error de sintaxis");
			else {
				type = "Fichero<" + getType(id2.getText()) + ">";
			}
		} else {
			type = getType(id1.getText());
		}
		for(int i = 0; i < il.length; i++)
		{
			s.append(prefix + " " + type + " " + il[i] + ";\n");
		}
	}
	| (ad=array_dimensions id3:ID)
	{	
		for(int i = 0; i < il.length; i++)
		{
			s.append(prefix + " " + getType(id3.getText()) + " " + il[i] + ad[1] + " = new " + getType(id3.getText()) + ad[0] + ";\n");
		}
	}
	| reg=register
	{
		type = "__reg" + regCount;
		s.append("class " + type + " {\n" + reg + "};\n");
		
		for(int i = 0; i < il.length; i++)
		{
			s.append(prefix + " " + type + " " + il[i] + ";\n");
		}
		regCount++; 
	}
	))
	{
		javaCode = s.toString();
	}
;
exception catch [Exception e] {
	// nada, por ahora
}

register returns [String javaCode = ""]
	{
		StringBuffer s = new StringBuffer();
		String c;
	}:
	(c=common_var_dcl[";\n", null]
	{
		s.append(c);
	}
	)+
	{
		javaCode = s.toString();
	}
;

sentence_list_block returns [String javaCode = ""]:
	javaCode=sentence_list
;


sentence_list returns [String javaCode = ""]
	{
		StringBuffer s = new StringBuffer();
		String a;
	}:
	#(SENTENCES (a=sentence
	{
		s.append(a);
	}
	)*)
	{
		javaCode = s.toString();
	}
;

sentence  returns [String javaCode = ""]:
	javaCode=if_statement
	| javaCode=procedure_call
	| javaCode=assign_statement
	| javaCode=output_input_statement
	| javaCode=while_loop
	| javaCode=fromto_loop
;

if_statement returns [String javaCode = ""]
	{
		String a, b, c;
	}:
	#(IF_SENTENCE
	a=expr
	b=sentence_list
	c=elif_statement_list)
	{
		javaCode = "if( " + a + ") {\n" + b + "}\n" + c;
	}
;

elif_statement_list returns [String javaCode = ""]
	{
		String a = null, b = null, c;
	}:
	ELSE
	(a=sentence_list | IS_NULL)
	{
		
		if(a == null)
		{
			a = ";\n";
		}
		javaCode = "else {\n" + a + "}\n";
	}
	| 
	a=expr
	(b=sentence_list | IS_NULL)
	c=elif_statement_list
	{
		if(b == null)
		{
			b = ";\n";
		}
		javaCode = "else if(" + a + ") {\n" + b + "}\n" + c;
	}
;

//TODO: mult_assign
assign_statement returns [String javaCode = ""]
	{
		String a = null;
		String b[];
	}:
	#(ASSIGNMENT a=struct_call b=mult_assign)
	{
		javaCode = a + " = " + b[0] + ";\n";
	}
;

mult_assign returns [String []javaCode = {""}]
	{
		String a = "";
		StringArray sa = new StringArray();
	}:
	(a=expr
	{
		sa.add(a);
	}
	)+
	{
		javaCode = getArray(sa);
	}
;

output_input_statement returns [String javaCode = ""]
	{
		StringBuffer sb = new StringBuffer();
		String a[];
		boolean read = false;
	}:
	#(IO_STATEMENT (READ
	{
		read = true;
	}
	| WRITE
	{
		sb.append("System.out.println(");	
	}
	)
	 a=expr_list_full)
	{
		if(read)
		{
			for(int i = 0; i < a.length-1; i++)
				sb.append(a[i] + " = __in.readLine();\n");
		} else {
			for(int i = 0; i < a.length-1; i++)
				sb.append(a[i] + " + ");
			sb.append(a[a.length-1]);
			
			sb.append(");\n");
			javaCode = sb.toString();
		}
	}
;

while_loop returns [String javaCode = ""]
{
	String a, b;
}:
	#(WHILE_LOOP a=expr b=sentence_list)
	{
			javaCode = "while( " + a + " ) {\n" + b + "}\n";
	}
;

// javaCode[0] es la asignación
// javaCode[1] es la variable a asignar
fromto_assign_statement returns [String []javaCode = {"", ""}]
{
	String a, b;
}:
	a=struct_call b=expr
	{
		javaCode[0] = a + " = " + b;
		javaCode[1] = a;
	}
;

fromto_loop returns [String javaCode = ""]
{
	String a[];
	String b, c;
}:
	#(FROMTO_LOOP a=fromto_assign_statement b=expr
		c=sentence_list)
	{
		javaCode= "for(int " + a[0] + "; " + a[1]  +
		"  <= " + b + "; " + a[1] +"++) {\n" + c + "}\n";
		
	}
;

function_call returns [String javaCode = ""]
{
	StringBuffer sb = new StringBuffer();
	String []b;
}:
	a:ID b=expr_list
	{
		sb.append(a.getText() + "(");
		for(int i = 0; i < b.length-1; i++)
		{
			sb.append(b[i] + ", ");
		}
		if(b.length > 0)
		sb.append(b[b.length-1]);
		javaCode = sb.toString();
	}
;

variable_call returns [String javaCode = ""]
{
	StringBuffer sb = new StringBuffer();
	String []b=null;
}:
	a:ID b=expr_list
	{
		if(b != null && b.length > 0)
		{
			sb.append(a.getText() + "[");
			for(int i = 0; i < b.length-1; i++)
			{
				sb.append(b[i] + "][");
			}
			sb.append(b[b.length-1] + "]");
			
			javaCode = sb.toString();
		} else
			javaCode = a.getText();
	}
;

struct_call returns [String javaCode = ""]
{
	StringBuffer sb = new StringBuffer();
	String a = null, b;
}:
	#(STRUCT_CALL a=variable_call
	{
		sb.append(a);
	}
	(b=variable_call
	{
		sb.append("." + b);
	})*)
	{
		javaCode = sb.toString();
	}
;

procedure_call returns [String javaCode = ""]
{
	StringBuffer sb = new StringBuffer();
	String []b;
}:
	#(PROC_CALL a:ID b=expr_list)
	{
		sb.append(a.getText() + "(");
		for(int i = 0; i < b.length-1; i++)
		{
			sb.append(b[i] + ", ");
		}
		if(b.length > 0)
			sb.append(b[b.length-1]);
		
		sb.append(");\n");
		javaCode = sb.toString();
	}
;

expr_list returns [String []javaCode = {}]
{
	StringArray sa = new StringArray();
	String e;
}:
	(e=expr
	{
		sa.add(e);
	}
	)*
	{
		javaCode = getArray(sa);
	}
;

expr_list_full returns [String []javaCode = {}]
{
	StringArray sa = new StringArray();
	String e;
}:
	(e=expr
	{
		sa.add(e);
	}
	)+
	{
		javaCode = getArray(sa);
	}
;

expr returns [String javaCode = ""]
{
	StringBuffer sb = new StringBuffer();
	String a, b = null;
}:
	#(OR a=expr_and
	{
		sb.append(a);
	}
	(b=expr_and
	{
		sb.append(" || " + b);
	}
	)+)
	{
		javaCode = "(" + sb.toString() + ")";
	}
	| javaCode=expr_and
;

expr_and returns [String javaCode = ""]
{
	StringBuffer sb = new StringBuffer();
	String a, b = null;
}:
	#(AND a=expr_eq
	{
		sb.append(a);
	}
	(b=expr_eq
	{
		sb.append(" && " + b);
	}
	)+)
	{
			javaCode = "(" + sb.toString() + ")";
	}
	| javaCode=expr_eq
;

expr_eq returns [String javaCode = ""]
{
	String a, b = null;
}:
	#(EQ a=expr_eq b=expr_eq)
	{
		javaCode = "( " + a	+ " == " + b + " )";
	}
	| 
	#(NOT_EQ a=expr_eq b=expr_eq)
	{
		javaCode = "( " + a	+ " != " + b + " )";
	}
	#(LE_OP a=expr_eq b=expr_eq)
	{
		javaCode = "( " + a	+ " <= " + b + " )";
	}
	| 
	#(GE_OP a=expr_eq b=expr_eq)
	{
		javaCode = "( " + a	+ " >= " + b + " )";
	}
	| 
	#(L_OP a=expr_eq b=expr_eq)
	{
		javaCode = "( " + a	+ " < " + b + " )";
	}
	| 
	#(G_OP a=expr_eq b=expr_eq)
	{
		javaCode = "( " + a	+ " > " + b + " )";
	}
	| javaCode=expr_mult
;

expr_mult returns [String javaCode = ""]
{
	StringBuffer sb = new StringBuffer();
	String a, b;
}:
	#(MULT a=expr_prefix b=sub_expr_mult)
	{
		sb.append("( " + a + " * " + b + " )");
		javaCode = sb.toString();
	}
	| #(DIV a=expr_prefix b=sub_expr_mult)
	{
		sb.append("( " + a + " / " + b + " )");
		javaCode = sb.toString();
	}
	| #(MOD a=expr_prefix b=sub_expr_mult)
	{
		sb.append("( " + a + " % " + b + " )");
		javaCode = sb.toString();
	}
	| #(RAISE a=expr_prefix b=sub_expr_mult)
	{
		sb.append("( " + a + " ^ " + b + " )");
		javaCode = sb.toString();
	}
	| #(PLUS a=expr_prefix b=sub_expr_mult)
	{
		sb.append("( " + a + " + " + b + " )");
		javaCode = sb.toString();
	}
	| #(MINUS a=expr_prefix b=sub_expr_mult)
	{
		sb.append("( " + a + " - " + b + " )");
		javaCode = sb.toString();
	}
	| javaCode=expr_prefix
;

sub_expr_mult returns [String javaCode = ""]
{
	StringBuffer sb = new StringBuffer();
	String a, b, op;
}:
	a=expr_prefix
	{
		sb.append(a);
	}
	((MULT {op = " * "; }
	| DIV { op = " / "; }
	| MOD { op = " % "; }
	| RAISE { op = " ^ "; }
	| PLUS { op = " + "; }
	| MINUS { op = " - "; }
	) b=expr_prefix
	{
		sb.append(b + op);
	}
	)*
	{
		javaCode = sb.toString();
	}
;

expr_prefix returns [String javaCode = ""]
{
	String a;
	boolean b = true;
}:
	#(PREFIX (PLUS {b = false;} | MINUS)  a=expr_base)
	{
		if(b == false)
			javaCode = "(+" + a + ")";
		else
			javaCode = "(-" + a + ")";
	}
	| javaCode=expr_base
;

expr_base returns [String javaCode = ""]:
	a:INT_VAL
	{
		javaCode = a.getText();
	}
	| b:FLOAT_VAL
	{
		javaCode = b.getText();
	}
	| c:STR_VAL
	{
		javaCode = c.getText().replaceAll("\n", "\\\\n\" +\n\"");
	}
	| javaCode=function_call
	| javaCode=struct_call
	| #(EXPR javaCode=expr)
	| TRUE
	{
		javaCode = "true";
	}
	| FALSE
	{
		javaCode = "false";
	}
;
