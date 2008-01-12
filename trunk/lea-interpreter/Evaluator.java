// $ANTLR : "gramatica.g" -> "Evaluator.java"$

import antlr.TreeParser;
import antlr.Token;
import antlr.collections.AST;
import antlr.RecognitionException;
import antlr.ANTLRException;
import antlr.NoViableAltException;
import antlr.MismatchedTokenException;
import antlr.SemanticException;
import antlr.collections.impl.BitSet;
import antlr.ASTPair;
import antlr.collections.impl.ASTArray;

	
 import java.util.Hashtable;
 import java.util.Map.Entry;
 import com.sun.xml.internal.fastinfoset.util.StringArray;


public class Evaluator extends antlr.TreeParser       implements AnalexTokenTypes
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
public Evaluator() {
	tokenNames = _tokenNames;
}

	public final String [] program(AST _t) throws RecognitionException {
		String []javaCode = {null, null};
		
		AST program_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		
				String a[];
				String b, c, d; initialize();
			
		
		try {      // for error handling
			AST __t272 = _t;
			AST tmp204_AST_in = (AST)_t;
			match(_t,PROGRAM);
			_t = _t.getFirstChild();
			a=prog_header(_t);
			_t = _retTree;
			b=declarations_block(_t,"static");
			_t = _retTree;
			c=sentence_list_block(_t);
			_t = _retTree;
			d=library(_t);
			_t = _retTree;
			_t = __t272;
			_t = _t.getNextSibling();
			
					javaCode[0] = a[0] + b +
					"public static void main(String args[]) {\n"
					+ c + "}\n"
					+ d + "};\n";
					javaCode[1] = a[1];
				
		}
		catch (RecognitionException ex) {
			reportError(ex);
			if (_t!=null) {_t = _t.getNextSibling();}
		}
		_retTree = _t;
		return javaCode;
	}
	
	public final String [] prog_header(AST _t) throws RecognitionException {
		String []javaCode = {null, null};
		
		AST prog_header_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		AST id = null;
		
		try {      // for error handling
			AST __t274 = _t;
			AST tmp205_AST_in = (AST)_t;
			match(_t,PROG);
			_t = _t.getFirstChild();
			id = (AST)_t;
			match(_t,ID);
			_t = _t.getNextSibling();
			_t = __t274;
			_t = _t.getNextSibling();
			
					String p = id.getText();
					p = p.substring(0,1).toUpperCase() + p.substring(1, p.length());
					
					javaCode[0] = "import java.io.*;\n\n" + 
					"class " + p + " {\n" +
					"static BufferedReader __in = new BufferedReader(\n" +
					"		    new InputStreamReader(System.in));\n"; 
					javaCode[1] = p;
				
		}
		catch (RecognitionException ex) {
			reportError(ex);
			if (_t!=null) {_t = _t.getNextSibling();}
		}
		_retTree = _t;
		return javaCode;
	}
	
	public final String  declarations_block(AST _t,
		String prefix
	) throws RecognitionException {
		String javaCode = null;
		
		AST declarations_block_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		String a = "", b = "", c = "";
		
		try {      // for error handling
			AST __t329 = _t;
			AST tmp206_AST_in = (AST)_t;
			match(_t,DECLARATIONS_BLOCK);
			_t = _t.getFirstChild();
			{
			if (_t==null) _t=ASTNULL;
			switch ( _t.getType()) {
			case CONSTS:
			{
				a=consts_block(_t,prefix);
				_t = _retTree;
				break;
			}
			case 3:
			case TYPES:
			case VARS:
			{
				break;
			}
			default:
			{
				throw new NoViableAltException(_t);
			}
			}
			}
			{
			if (_t==null) _t=ASTNULL;
			switch ( _t.getType()) {
			case TYPES:
			{
				b=types_block(_t);
				_t = _retTree;
				break;
			}
			case 3:
			case VARS:
			{
				break;
			}
			default:
			{
				throw new NoViableAltException(_t);
			}
			}
			}
			{
			if (_t==null) _t=ASTNULL;
			switch ( _t.getType()) {
			case VARS:
			{
				c=vars_block(_t,prefix);
				_t = _retTree;
				break;
			}
			case 3:
			{
				break;
			}
			default:
			{
				throw new NoViableAltException(_t);
			}
			}
			}
			_t = __t329;
			_t = _t.getNextSibling();
			
					javaCode = a + b + c;
				
		}
		catch (RecognitionException ex) {
			reportError(ex);
			if (_t!=null) {_t = _t.getNextSibling();}
		}
		_retTree = _t;
		return javaCode;
	}
	
	public final String  sentence_list_block(AST _t) throws RecognitionException {
		String javaCode = "";
		
		AST sentence_list_block_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		
		try {      // for error handling
			javaCode=sentence_list(_t);
			_t = _retTree;
		}
		catch (RecognitionException ex) {
			reportError(ex);
			if (_t!=null) {_t = _t.getNextSibling();}
		}
		_retTree = _t;
		return javaCode;
	}
	
	public final String  library(AST _t) throws RecognitionException {
		String javaCode = null;
		
		AST library_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		StringBuffer s = new StringBuffer(); String a;
		
		try {      // for error handling
			AST __t276 = _t;
			AST tmp207_AST_in = (AST)_t;
			match(_t,LIBRARY);
			_t = _t.getFirstChild();
			{
			_loop278:
			do {
				if (_t==null) _t=ASTNULL;
				switch ( _t.getType()) {
				case FUNCTION:
				{
					a=function(_t);
					_t = _retTree;
					
							s.append(a);
						
					break;
				}
				case PROCEDURE:
				{
					a=procedure(_t);
					_t = _retTree;
					
							s.append(a);
						
					break;
				}
				default:
				{
					break _loop278;
				}
				}
			} while (true);
			}
			_t = __t276;
			_t = _t.getNextSibling();
			
					javaCode = s.toString();
				
		}
		catch (RecognitionException ex) {
			reportError(ex);
			if (_t!=null) {_t = _t.getNextSibling();}
		}
		_retTree = _t;
		return javaCode;
	}
	
	public final String  function(AST _t) throws RecognitionException {
		String javaCode = null;
		
		AST function_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		
				StringBuffer sb = new StringBuffer();
				String a[];
				String b, c;
			
		
		try {      // for error handling
			AST __t280 = _t;
			AST tmp208_AST_in = (AST)_t;
			match(_t,FUNCTION);
			_t = _t.getFirstChild();
			a=func_header(_t,sb);
			_t = _retTree;
			b=declarations_block(_t,"");
			_t = _retTree;
			c=sentence_list_block(_t);
			_t = _retTree;
			_t = __t280;
			_t = _t.getNextSibling();
			
					javaCode = a[0] + sb.toString() + b + c + a[1] + "}\n";
				
		}
		catch (RecognitionException ex) {
			reportError(ex);
			if (_t!=null) {_t = _t.getNextSibling();}
		}
		_retTree = _t;
		return javaCode;
	}
	
	public final String  procedure(AST _t) throws RecognitionException {
		String javaCode = null;
		
		AST procedure_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		
				StringBuffer sb = new StringBuffer();
				String a, b, c;
			
		
		try {      // for error handling
			AST __t282 = _t;
			AST tmp209_AST_in = (AST)_t;
			match(_t,PROCEDURE);
			_t = _t.getFirstChild();
			a=proc_header(_t,sb);
			_t = _retTree;
			b=declarations_block(_t,"");
			_t = _retTree;
			c=sentence_list_block(_t);
			_t = _retTree;
			_t = __t282;
			_t = _t.getNextSibling();
			
					javaCode = a + "{\n" + sb.toString() + b + c + "}\n";
				
		}
		catch (RecognitionException ex) {
			reportError(ex);
			if (_t!=null) {_t = _t.getNextSibling();}
		}
		_retTree = _t;
		return javaCode;
	}
	
	public final String [] func_header(AST _t,
		StringBuffer sb
	) throws RecognitionException {
		String []javaCode = {null, null};
		
		AST func_header_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		AST a = null;
		String b = ""; String []c;
		
		try {      // for error handling
			AST __t284 = _t;
			AST tmp210_AST_in = (AST)_t;
			match(_t,HEADER);
			_t = _t.getFirstChild();
			a = (AST)_t;
			match(_t,ID);
			_t = _t.getNextSibling();
			{
			if (_t==null) _t=ASTNULL;
			switch ( _t.getType()) {
			case C:
			{
				b=in_arg_list(_t,sb);
				_t = _retTree;
				break;
			}
			case DEV:
			{
				break;
			}
			default:
			{
				throw new NoViableAltException(_t);
			}
			}
			}
			AST __t286 = _t;
			AST tmp211_AST_in = (AST)_t;
			match(_t,DEV);
			_t = _t.getFirstChild();
			c=func_out_var_dcl(_t);
			_t = _retTree;
			_t = __t286;
			_t = _t.getNextSibling();
			_t = __t284;
			_t = _t.getNextSibling();
			
					javaCode[0] = "static private " + c[0] + " " + a.getText()
					+ "(" + b + ")\n{\n" + c[1];
					javaCode[1] =  c[2];
				
		}
		catch (RecognitionException ex) {
			reportError(ex);
			if (_t!=null) {_t = _t.getNextSibling();}
		}
		_retTree = _t;
		return javaCode;
	}
	
	public final String  proc_header(AST _t,
		StringBuffer sb
	) throws RecognitionException {
		String javaCode = null;
		
		AST proc_header_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		AST a = null;
		StringBuffer s = new StringBuffer(""); String b;
		
		try {      // for error handling
			AST __t288 = _t;
			AST tmp212_AST_in = (AST)_t;
			match(_t,HEADER);
			_t = _t.getFirstChild();
			a = (AST)_t;
			match(_t,ID);
			_t = _t.getNextSibling();
			{
			int _cnt290=0;
			_loop290:
			do {
				if (_t==null) _t=ASTNULL;
				if (((_t.getType() >= INOUT && _t.getType() <= OUT))) {
					b=proc_arg(_t,sb);
					_t = _retTree;
					
							s.append(b + ", ");
						
				}
				else {
					if ( _cnt290>=1 ) { break _loop290; } else {throw new NoViableAltException(_t);}
				}
				
				_cnt290++;
			} while (true);
			}
			_t = __t288;
			_t = _t.getNextSibling();
			
					
					javaCode = s.toString();
					javaCode = javaCode.substring(0, javaCode.length()-2);
					javaCode = "static private void " + a.getText() + "(" + javaCode + ")\n";
				
		}
		catch (RecognitionException ex) {
			reportError(ex);
			if (_t!=null) {_t = _t.getNextSibling();}
		}
		_retTree = _t;
		return javaCode;
	}
	
	public final String  in_arg_list(AST _t,
		StringBuffer sb
	) throws RecognitionException {
		String javaCode = "";
		
		AST in_arg_list_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		StringBuffer s = new StringBuffer(""); String a;
		
		try {      // for error handling
			{
			int _cnt297=0;
			_loop297:
			do {
				if (_t==null) _t=ASTNULL;
				if ((_t.getType()==C)) {
					a=in_var_dcl(_t,sb);
					_t = _retTree;
					
							s.append(a + ", ");
						
				}
				else {
					if ( _cnt297>=1 ) { break _loop297; } else {throw new NoViableAltException(_t);}
				}
				
				_cnt297++;
			} while (true);
			}
			
					javaCode = s.toString();
					javaCode = javaCode.substring(0, javaCode.length()-2);
				
		}
		catch (RecognitionException ex) {
			reportError(ex);
			if (_t!=null) {_t = _t.getNextSibling();}
		}
		_retTree = _t;
		return javaCode;
	}
	
	public final String [] func_out_var_dcl(AST _t) throws RecognitionException {
		 String []ret = {null, null, null} ;
		
		AST func_out_var_dcl_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		AST id1 = null;
		AST id2 = null;
		AST id3 = null;
		
				StringBuffer s = new StringBuffer();
				String il[], ad[];
				String type;
			
		
		try {      // for error handling
			AST __t311 = _t;
			AST tmp213_AST_in = (AST)_t;
			match(_t,C);
			_t = _t.getFirstChild();
			il=id_list(_t);
			_t = _retTree;
			{
			if (_t==null) _t=ASTNULL;
			switch ( _t.getType()) {
			case ID:
			{
				{
				id1 = (AST)_t;
				match(_t,ID);
				_t = _t.getNextSibling();
				{
				if (_t==null) _t=ASTNULL;
				switch ( _t.getType()) {
				case ID:
				{
					id2 = (AST)_t;
					match(_t,ID);
					_t = _t.getNextSibling();
					break;
				}
				case 3:
				{
					break;
				}
				default:
				{
					throw new NoViableAltException(_t);
				}
				}
				}
				}
				
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
					
				break;
			}
			case ARRAY:
			{
				{
				AST tmp214_AST_in = (AST)_t;
				match(_t,ARRAY);
				_t = _t.getNextSibling();
				ad=array_dimensions(_t);
				_t = _retTree;
				id3 = (AST)_t;
				match(_t,ID);
				_t = _t.getNextSibling();
				}
					
						for(int i = 0; i < il.length; i++)
						{
							s.append(getType(id3.getText()) + " " + il[i] + ad[1] + " = new " + getType(id3.getText()) + ad[0] + ";\n");
						}
						ret[0] = getType(id3.getText()) + ad[0];
						ret[1] = s.toString();
						ret[2] = "return " + il[0] + ";\n";
					
				break;
			}
			default:
			{
				throw new NoViableAltException(_t);
			}
			}
			}
			_t = __t311;
			_t = _t.getNextSibling();
		}
		catch (Exception e) {
			
				// nada, por ahora
			
		}
		_retTree = _t;
		return ret;
	}
	
	public final String  proc_arg(AST _t,
		StringBuffer sb
	) throws RecognitionException {
		String javaCode = "";
		
		AST proc_arg_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		
		try {      // for error handling
			if (_t==null) _t=ASTNULL;
			switch ( _t.getType()) {
			case IN:
			{
				AST __t292 = _t;
				AST tmp215_AST_in = (AST)_t;
				match(_t,IN);
				_t = _t.getFirstChild();
				javaCode=in_arg_list(_t,sb);
				_t = _retTree;
				_t = __t292;
				_t = _t.getNextSibling();
				break;
			}
			case OUT:
			{
				AST __t293 = _t;
				AST tmp216_AST_in = (AST)_t;
				match(_t,OUT);
				_t = _t.getFirstChild();
				javaCode=out_arg_list(_t,sb);
				_t = _retTree;
				_t = __t293;
				_t = _t.getNextSibling();
				break;
			}
			case INOUT:
			{
				AST __t294 = _t;
				AST tmp217_AST_in = (AST)_t;
				match(_t,INOUT);
				_t = _t.getFirstChild();
				javaCode=inout_arg_list(_t,sb);
				_t = _retTree;
				_t = __t294;
				_t = _t.getNextSibling();
				break;
			}
			default:
			{
				throw new NoViableAltException(_t);
			}
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			if (_t!=null) {_t = _t.getNextSibling();}
		}
		_retTree = _t;
		return javaCode;
	}
	
	public final String  out_arg_list(AST _t,
		StringBuffer sb
	) throws RecognitionException {
		String javaCode = "";
		
		AST out_arg_list_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		StringBuffer s = new StringBuffer(""); String a;
		
		try {      // for error handling
			{
			int _cnt300=0;
			_loop300:
			do {
				if (_t==null) _t=ASTNULL;
				if ((_t.getType()==C)) {
					a=out_var_dcl(_t,sb);
					_t = _retTree;
					
							s.append(a + ", ");
						
				}
				else {
					if ( _cnt300>=1 ) { break _loop300; } else {throw new NoViableAltException(_t);}
				}
				
				_cnt300++;
			} while (true);
			}
			
					javaCode = s.toString();
					javaCode = javaCode.substring(0, javaCode.length()-2);
				
		}
		catch (RecognitionException ex) {
			reportError(ex);
			if (_t!=null) {_t = _t.getNextSibling();}
		}
		_retTree = _t;
		return javaCode;
	}
	
	public final String  inout_arg_list(AST _t,
		StringBuffer sb
	) throws RecognitionException {
		String javaCode = "";
		
		AST inout_arg_list_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		StringBuffer s = new StringBuffer(""); String a;
		
		try {      // for error handling
			{
			int _cnt303=0;
			_loop303:
			do {
				if (_t==null) _t=ASTNULL;
				if ((_t.getType()==C)) {
					a=inout_var_dcl(_t,sb);
					_t = _retTree;
					
							s.append(a + ", ");
						
				}
				else {
					if ( _cnt303>=1 ) { break _loop303; } else {throw new NoViableAltException(_t);}
				}
				
				_cnt303++;
			} while (true);
			}
			
					javaCode = s.toString();
					javaCode = javaCode.substring(0, javaCode.length()-2);
				
		}
		catch (RecognitionException ex) {
			reportError(ex);
			if (_t!=null) {_t = _t.getNextSibling();}
		}
		_retTree = _t;
		return javaCode;
	}
	
	public final String  in_var_dcl(AST _t,
		StringBuffer sb
	) throws RecognitionException {
		String javaCode = "";
		
		AST in_var_dcl_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		
		try {      // for error handling
			javaCode=common_var_dcl(_t,"", sb);
			_t = _retTree;
		}
		catch (RecognitionException ex) {
			reportError(ex);
			if (_t!=null) {_t = _t.getNextSibling();}
		}
		_retTree = _t;
		return javaCode;
	}
	
	public final String  out_var_dcl(AST _t,
		StringBuffer sb
	) throws RecognitionException {
		String javaCode = "";
		
		AST out_var_dcl_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		
		try {      // for error handling
			javaCode=common_var_dcl(_t,"", sb);
			_t = _retTree;
		}
		catch (RecognitionException ex) {
			reportError(ex);
			if (_t!=null) {_t = _t.getNextSibling();}
		}
		_retTree = _t;
		return javaCode;
	}
	
	public final String  inout_var_dcl(AST _t,
		StringBuffer sb
	) throws RecognitionException {
		String javaCode = "";
		
		AST inout_var_dcl_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		
		try {      // for error handling
			javaCode=common_var_dcl(_t,"", sb);
			_t = _retTree;
		}
		catch (RecognitionException ex) {
			reportError(ex);
			if (_t!=null) {_t = _t.getNextSibling();}
		}
		_retTree = _t;
		return javaCode;
	}
	
	public final String  common_var_dcl(AST _t,
		String terminator, StringBuffer sb
	) throws RecognitionException {
		String javaCode = "";
		
		AST common_var_dcl_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		AST id1 = null;
		AST id2 = null;
		AST id3 = null;
		
				StringBuffer s = new StringBuffer();
				String il[], ad[];
				String type;
			
		
		try {      // for error handling
			AST __t305 = _t;
			AST tmp218_AST_in = (AST)_t;
			match(_t,C);
			_t = _t.getFirstChild();
			il=id_list(_t);
			_t = _retTree;
			{
			if (_t==null) _t=ASTNULL;
			switch ( _t.getType()) {
			case ID:
			{
				{
				id1 = (AST)_t;
				match(_t,ID);
				_t = _t.getNextSibling();
				{
				if (_t==null) _t=ASTNULL;
				switch ( _t.getType()) {
				case ID:
				{
					id2 = (AST)_t;
					match(_t,ID);
					_t = _t.getNextSibling();
					break;
				}
				case 3:
				{
					break;
				}
				default:
				{
					throw new NoViableAltException(_t);
				}
				}
				}
				}
				
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
					
				break;
			}
			case ARRAY_DIMENSIONS:
			{
				{
				ad=array_dimensions(_t);
				_t = _retTree;
				id3 = (AST)_t;
				match(_t,ID);
				_t = _t.getNextSibling();
				}
					
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
					
				break;
			}
			default:
			{
				throw new NoViableAltException(_t);
			}
			}
			}
			_t = __t305;
			_t = _t.getNextSibling();
		}
		catch (Exception e) {
			
				javaCode = "";
			
		}
		_retTree = _t;
		return javaCode;
	}
	
	public final String [] id_list(AST _t) throws RecognitionException {
		String []ret = null;
		
		AST id_list_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		AST id = null;
		StringArray s = new StringArray();
		
		try {      // for error handling
			AST __t320 = _t;
			AST tmp219_AST_in = (AST)_t;
			match(_t,ID_LIST);
			_t = _t.getFirstChild();
			{
			int _cnt322=0;
			_loop322:
			do {
				if (_t==null) _t=ASTNULL;
				if ((_t.getType()==ID)) {
					id = (AST)_t;
					match(_t,ID);
					_t = _t.getNextSibling();
					
							s.add(id.getText());
						
				}
				else {
					if ( _cnt322>=1 ) { break _loop322; } else {throw new NoViableAltException(_t);}
				}
				
				_cnt322++;
			} while (true);
			}
			_t = __t320;
			_t = _t.getNextSibling();
			
					ret = getArray(s);
				
		}
		catch (RecognitionException ex) {
			reportError(ex);
			if (_t!=null) {_t = _t.getNextSibling();}
		}
		_retTree = _t;
		return ret;
	}
	
	public final String [] array_dimensions(AST _t) throws RecognitionException {
		String []javaCode = {null, null};
		
		AST array_dimensions_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		StringBuffer s = new StringBuffer(), s2 = new StringBuffer(); String a;
		
		try {      // for error handling
			AST __t324 = _t;
			AST tmp220_AST_in = (AST)_t;
			match(_t,ARRAY_DIMENSIONS);
			_t = _t.getFirstChild();
			{
			int _cnt326=0;
			_loop326:
			do {
				if (_t==null) _t=ASTNULL;
				if ((_t.getType()==INT_VAL||_t.getType()==ID)) {
					a=int_id_val(_t);
					_t = _retTree;
					
							s.append("[" + a + "]");
							s2.append("[]");
						
				}
				else {
					if ( _cnt326>=1 ) { break _loop326; } else {throw new NoViableAltException(_t);}
				}
				
				_cnt326++;
			} while (true);
			}
			_t = __t324;
			_t = _t.getNextSibling();
			
					javaCode[0] = s.toString();
					javaCode[1] = s2.toString();
				
		}
		catch (RecognitionException ex) {
			reportError(ex);
			if (_t!=null) {_t = _t.getNextSibling();}
		}
		_retTree = _t;
		return javaCode;
	}
	
	public final String  int_id_val(AST _t) throws RecognitionException {
		String javaCode = null;
		
		AST int_id_val_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		AST a1 = null;
		AST a2 = null;
		
		try {      // for error handling
			if (_t==null) _t=ASTNULL;
			switch ( _t.getType()) {
			case INT_VAL:
			{
				a1 = (AST)_t;
				match(_t,INT_VAL);
				_t = _t.getNextSibling();
				
						javaCode = a1.getText();
					
				break;
			}
			case ID:
			{
				a2 = (AST)_t;
				match(_t,ID);
				_t = _t.getNextSibling();
				
						javaCode = a2.getText();
					
				break;
			}
			default:
			{
				throw new NoViableAltException(_t);
			}
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			if (_t!=null) {_t = _t.getNextSibling();}
		}
		_retTree = _t;
		return javaCode;
	}
	
	public final String  consts_block(AST _t,
		String prefix
	) throws RecognitionException {
		String javaCode = null;
		
		AST consts_block_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		StringBuffer s = new StringBuffer(); String a;
		
		try {      // for error handling
			AST __t334 = _t;
			AST tmp221_AST_in = (AST)_t;
			match(_t,CONSTS);
			_t = _t.getFirstChild();
			{
			_loop336:
			do {
				if (_t==null) _t=ASTNULL;
				if ((_t.getType()==C)) {
					a=const_dcl(_t,prefix);
					_t = _retTree;
					
							s.append(a);
						
				}
				else {
					break _loop336;
				}
				
			} while (true);
			}
			_t = __t334;
			_t = _t.getNextSibling();
			
					javaCode = s.toString();
				
		}
		catch (RecognitionException ex) {
			reportError(ex);
			if (_t!=null) {_t = _t.getNextSibling();}
		}
		_retTree = _t;
		return javaCode;
	}
	
	public final String  types_block(AST _t) throws RecognitionException {
		 String javaCode =  null ;
		
		AST types_block_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		
				StringBuffer s = new StringBuffer(); String t;
			
		
		try {      // for error handling
			AST __t341 = _t;
			AST tmp222_AST_in = (AST)_t;
			match(_t,TYPES);
			_t = _t.getFirstChild();
			{
			_loop343:
			do {
				if (_t==null) _t=ASTNULL;
				if ((_t.getType()==C)) {
					t=type_dcl(_t);
					_t = _retTree;
					
							s.append(t);
						
				}
				else {
					break _loop343;
				}
				
			} while (true);
			}
			_t = __t341;
			_t = _t.getNextSibling();
			
					javaCode = s.toString();
				
		}
		catch (RecognitionException ex) {
			reportError(ex);
			if (_t!=null) {_t = _t.getNextSibling();}
		}
		_retTree = _t;
		return javaCode;
	}
	
	public final String  vars_block(AST _t,
		String prefix
	) throws RecognitionException {
		String javaCode = "";
		
		AST vars_block_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		
				StringBuffer s = new StringBuffer();
				String v;
			
		
		try {      // for error handling
			AST __t351 = _t;
			AST tmp223_AST_in = (AST)_t;
			match(_t,VARS);
			_t = _t.getFirstChild();
			{
			_loop353:
			do {
				if (_t==null) _t=ASTNULL;
				if ((_t.getType()==C)) {
					v=var_dcl(_t,prefix);
					_t = _retTree;
					
							s.append(v);
						
				}
				else {
					break _loop353;
				}
				
			} while (true);
			}
			_t = __t351;
			_t = _t.getNextSibling();
			
					javaCode = s.toString();
				
		}
		catch (RecognitionException ex) {
			reportError(ex);
			if (_t!=null) {_t = _t.getNextSibling();}
		}
		_retTree = _t;
		return javaCode;
	}
	
	public final String  const_dcl(AST _t,
		String prefix
	) throws RecognitionException {
		String javaCode = null;
		
		AST const_dcl_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		AST i = null;
		AST f = null;
		AST c = null;
		AST s = null;
		
				StringBuffer sb = new StringBuffer();
				String[] il;
				String type, value;
			
		
		try {      // for error handling
			AST __t338 = _t;
			AST tmp224_AST_in = (AST)_t;
			match(_t,C);
			_t = _t.getFirstChild();
			il=id_list(_t);
			_t = _retTree;
			{
			if (_t==null) _t=ASTNULL;
			switch ( _t.getType()) {
			case TRUE:
			{
				AST tmp225_AST_in = (AST)_t;
				match(_t,TRUE);
				_t = _t.getNextSibling();
				
						type = "final boolean";
						value = "true";
					
				break;
			}
			case FALSE:
			{
				AST tmp226_AST_in = (AST)_t;
				match(_t,FALSE);
				_t = _t.getNextSibling();
				
						type = "final boolean";
						value = "false";
					
				break;
			}
			case INT_VAL:
			{
				i = (AST)_t;
				match(_t,INT_VAL);
				_t = _t.getNextSibling();
				
						type = "final int";
						value = i.getText();
					
				break;
			}
			case FLOAT_VAL:
			{
				f = (AST)_t;
				match(_t,FLOAT_VAL);
				_t = _t.getNextSibling();
				
						type = "final float";
						value = f.getText();
					
				break;
			}
			case CHAR_VAL:
			{
				c = (AST)_t;
				match(_t,CHAR_VAL);
				_t = _t.getNextSibling();
				
						type = "final char";
						value = c.getText();
					
				break;
			}
			case STR_VAL:
			{
				s = (AST)_t;
				match(_t,STR_VAL);
				_t = _t.getNextSibling();
				
						type = "final String";
						value = s.getText().replaceAll("\n", "\\\\n\" +\n\"");
					
				break;
			}
			default:
			{
				throw new NoViableAltException(_t);
			}
			}
			}
			_t = __t338;
			_t = _t.getNextSibling();
			
					for(int j = 0; j < il.length; j++)
					{
						sb.append(prefix + " " + type + " " + il[j] + " = " + value + ";\n");
					}
					javaCode = sb.toString();
				
		}
		catch (RecognitionException ex) {
			reportError(ex);
			if (_t!=null) {_t = _t.getNextSibling();}
		}
		_retTree = _t;
		return javaCode;
	}
	
	public final String  type_dcl(AST _t) throws RecognitionException {
		String javaCode = "";
		
		AST type_dcl_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		AST id1 = null;
		AST id2 = null;
		AST id3 = null;
		
				StringBuffer s = new StringBuffer();
				String id_list[], id_list2[], ad[];
				String type, reg;
			
		
		try {      // for error handling
			AST __t345 = _t;
			AST tmp227_AST_in = (AST)_t;
			match(_t,C);
			_t = _t.getFirstChild();
			id_list=id_list(_t);
			_t = _retTree;
			{
			if (_t==null) _t=ASTNULL;
			switch ( _t.getType()) {
			case ID:
			{
				{
				id1 = (AST)_t;
				match(_t,ID);
				_t = _t.getNextSibling();
				{
				if (_t==null) _t=ASTNULL;
				switch ( _t.getType()) {
				case ID:
				{
					id2 = (AST)_t;
					match(_t,ID);
					_t = _t.getNextSibling();
					break;
				}
				case 3:
				{
					break;
				}
				default:
				{
					throw new NoViableAltException(_t);
				}
				}
				}
				}
				
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
					
				break;
			}
			case ARRAY_DIMENSIONS:
			{
				{
				ad=array_dimensions(_t);
				_t = _retTree;
				id3 = (AST)_t;
				match(_t,ID);
				_t = _t.getNextSibling();
				}
					
						for(int i = 0; i < id_list.length; i++)
						{
							commonTypes.put(id_list[i], getType(id3.getText()) + ad[0]);
						}
					
				break;
			}
			case ID_LIST:
			{
				id_list2=id_list(_t);
				_t = _retTree;
				
						for(int i = 0; i < id_list.length; i++)
						{
							commonTypes.put(id_list[i], getType(id_list2[i]));
						}
					
				break;
			}
			case C:
			{
				reg=register(_t);
				_t = _retTree;
				
						javaCode = "class __reg" + regCount + " {\n" + reg + "};\n";
						
						for(int i = 0; i < id_list.length; i++)
						{
							commonTypes.put(id_list[i], "__reg" + regCount);
						}
						regCount++; 
					
				break;
			}
			default:
			{
				throw new NoViableAltException(_t);
			}
			}
			}
			_t = __t345;
			_t = _t.getNextSibling();
		}
		catch (Exception e) {
			
				// nada, por ahora
			
		}
		_retTree = _t;
		return javaCode;
	}
	
	public final String  register(AST _t) throws RecognitionException {
		String javaCode = "";
		
		AST register_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		
				StringBuffer s = new StringBuffer();
				String c;
			
		
		try {      // for error handling
			{
			int _cnt362=0;
			_loop362:
			do {
				if (_t==null) _t=ASTNULL;
				if ((_t.getType()==C)) {
					c=common_var_dcl(_t,";\n", null);
					_t = _retTree;
					
							s.append(c);
						
				}
				else {
					if ( _cnt362>=1 ) { break _loop362; } else {throw new NoViableAltException(_t);}
				}
				
				_cnt362++;
			} while (true);
			}
			
					javaCode = s.toString();
				
		}
		catch (RecognitionException ex) {
			reportError(ex);
			if (_t!=null) {_t = _t.getNextSibling();}
		}
		_retTree = _t;
		return javaCode;
	}
	
	public final String  var_dcl(AST _t,
		String prefix
	) throws RecognitionException {
		String javaCode = "";
		
		AST var_dcl_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		AST id1 = null;
		AST id2 = null;
		AST id3 = null;
		
				StringBuffer s = new StringBuffer();
				String type, reg;
				String []il;
				String []ad;
				boolean f = false;
			
		
		try {      // for error handling
			AST __t355 = _t;
			AST tmp228_AST_in = (AST)_t;
			match(_t,C);
			_t = _t.getFirstChild();
			il=id_list(_t);
			_t = _retTree;
			{
			if (_t==null) _t=ASTNULL;
			switch ( _t.getType()) {
			case ID:
			{
				{
				id1 = (AST)_t;
				match(_t,ID);
				_t = _t.getNextSibling();
				{
				if (_t==null) _t=ASTNULL;
				switch ( _t.getType()) {
				case ID:
				{
					id2 = (AST)_t;
					match(_t,ID);
					_t = _t.getNextSibling();
					f = true;
					break;
				}
				case 3:
				{
					break;
				}
				default:
				{
					throw new NoViableAltException(_t);
				}
				}
				}
				}
				
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
					
				break;
			}
			case ARRAY_DIMENSIONS:
			{
				{
				ad=array_dimensions(_t);
				_t = _retTree;
				id3 = (AST)_t;
				match(_t,ID);
				_t = _t.getNextSibling();
				}
					
						for(int i = 0; i < il.length; i++)
						{
							s.append(prefix + " " + getType(id3.getText()) + " " + il[i] + ad[1] + " = new " + getType(id3.getText()) + ad[0] + ";\n");
						}
					
				break;
			}
			case C:
			{
				reg=register(_t);
				_t = _retTree;
				
						type = "__reg" + regCount;
						s.append("class " + type + " {\n" + reg + "};\n");
						
						for(int i = 0; i < il.length; i++)
						{
							s.append(prefix + " " + type + " " + il[i] + ";\n");
						}
						regCount++; 
					
				break;
			}
			default:
			{
				throw new NoViableAltException(_t);
			}
			}
			}
			_t = __t355;
			_t = _t.getNextSibling();
			
					javaCode = s.toString();
				
		}
		catch (Exception e) {
			
				// nada, por ahora
			
		}
		_retTree = _t;
		return javaCode;
	}
	
	public final String  sentence_list(AST _t) throws RecognitionException {
		String javaCode = "";
		
		AST sentence_list_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		
				StringBuffer s = new StringBuffer();
				String a;
			
		
		try {      // for error handling
			AST __t365 = _t;
			AST tmp229_AST_in = (AST)_t;
			match(_t,SENTENCES);
			_t = _t.getFirstChild();
			{
			_loop367:
			do {
				if (_t==null) _t=ASTNULL;
				if (((_t.getType() >= IF_SENTENCE && _t.getType() <= FROMTO_LOOP))) {
					a=sentence(_t);
					_t = _retTree;
					
							s.append(a);
						
				}
				else {
					break _loop367;
				}
				
			} while (true);
			}
			_t = __t365;
			_t = _t.getNextSibling();
			
					javaCode = s.toString();
				
		}
		catch (RecognitionException ex) {
			reportError(ex);
			if (_t!=null) {_t = _t.getNextSibling();}
		}
		_retTree = _t;
		return javaCode;
	}
	
	public final String  sentence(AST _t) throws RecognitionException {
		String javaCode = "";
		
		AST sentence_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		
		try {      // for error handling
			if (_t==null) _t=ASTNULL;
			switch ( _t.getType()) {
			case IF_SENTENCE:
			{
				javaCode=if_statement(_t);
				_t = _retTree;
				break;
			}
			case PROC_CALL:
			{
				javaCode=procedure_call(_t);
				_t = _retTree;
				break;
			}
			case ASSIGNMENT:
			{
				javaCode=assign_statement(_t);
				_t = _retTree;
				break;
			}
			case IO_STATEMENT:
			{
				javaCode=output_input_statement(_t);
				_t = _retTree;
				break;
			}
			case WHILE_LOOP:
			{
				javaCode=while_loop(_t);
				_t = _retTree;
				break;
			}
			case FROMTO_LOOP:
			{
				javaCode=fromto_loop(_t);
				_t = _retTree;
				break;
			}
			default:
			{
				throw new NoViableAltException(_t);
			}
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			if (_t!=null) {_t = _t.getNextSibling();}
		}
		_retTree = _t;
		return javaCode;
	}
	
	public final String  if_statement(AST _t) throws RecognitionException {
		String javaCode = "";
		
		AST if_statement_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		
				String a, b, c;
			
		
		try {      // for error handling
			AST __t370 = _t;
			AST tmp230_AST_in = (AST)_t;
			match(_t,IF_SENTENCE);
			_t = _t.getFirstChild();
			a=expr(_t);
			_t = _retTree;
			b=sentence_list(_t);
			_t = _retTree;
			c=elif_statement_list(_t);
			_t = _retTree;
			_t = __t370;
			_t = _t.getNextSibling();
			
					javaCode = "if( " + a + ") {\n" + b + "}\n" + c;
				
		}
		catch (RecognitionException ex) {
			reportError(ex);
			if (_t!=null) {_t = _t.getNextSibling();}
		}
		_retTree = _t;
		return javaCode;
	}
	
	public final String  procedure_call(AST _t) throws RecognitionException {
		String javaCode = "";
		
		AST procedure_call_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		AST a = null;
		
			StringBuffer sb = new StringBuffer();
			String []b;
		
		
		try {      // for error handling
			AST __t394 = _t;
			AST tmp231_AST_in = (AST)_t;
			match(_t,PROC_CALL);
			_t = _t.getFirstChild();
			a = (AST)_t;
			match(_t,ID);
			_t = _t.getNextSibling();
			b=expr_list(_t);
			_t = _retTree;
			_t = __t394;
			_t = _t.getNextSibling();
			
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
		catch (RecognitionException ex) {
			reportError(ex);
			if (_t!=null) {_t = _t.getNextSibling();}
		}
		_retTree = _t;
		return javaCode;
	}
	
	public final String  assign_statement(AST _t) throws RecognitionException {
		String javaCode = "";
		
		AST assign_statement_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		
				String a = null;
				String b[];
			
		
		try {      // for error handling
			AST __t375 = _t;
			AST tmp232_AST_in = (AST)_t;
			match(_t,ASSIGNMENT);
			_t = _t.getFirstChild();
			a=struct_call(_t);
			_t = _retTree;
			b=mult_assign(_t);
			_t = _retTree;
			_t = __t375;
			_t = _t.getNextSibling();
			
					javaCode = a + " = " + b[0] + ";\n";
				
		}
		catch (RecognitionException ex) {
			reportError(ex);
			if (_t!=null) {_t = _t.getNextSibling();}
		}
		_retTree = _t;
		return javaCode;
	}
	
	public final String  output_input_statement(AST _t) throws RecognitionException {
		String javaCode = "";
		
		AST output_input_statement_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		
				StringBuffer sb = new StringBuffer();
				String a[];
				boolean read = false;
			
		
		try {      // for error handling
			AST __t380 = _t;
			AST tmp233_AST_in = (AST)_t;
			match(_t,IO_STATEMENT);
			_t = _t.getFirstChild();
			{
			if (_t==null) _t=ASTNULL;
			switch ( _t.getType()) {
			case READ:
			{
				AST tmp234_AST_in = (AST)_t;
				match(_t,READ);
				_t = _t.getNextSibling();
				
						read = true;
					
				break;
			}
			case WRITE:
			{
				AST tmp235_AST_in = (AST)_t;
				match(_t,WRITE);
				_t = _t.getNextSibling();
				
						sb.append("System.out.println(");	
					
				break;
			}
			default:
			{
				throw new NoViableAltException(_t);
			}
			}
			}
			a=expr_list_full(_t);
			_t = _retTree;
			_t = __t380;
			_t = _t.getNextSibling();
			
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
		catch (RecognitionException ex) {
			reportError(ex);
			if (_t!=null) {_t = _t.getNextSibling();}
		}
		_retTree = _t;
		return javaCode;
	}
	
	public final String  while_loop(AST _t) throws RecognitionException {
		String javaCode = "";
		
		AST while_loop_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		
			String a, b;
		
		
		try {      // for error handling
			AST __t383 = _t;
			AST tmp236_AST_in = (AST)_t;
			match(_t,WHILE_LOOP);
			_t = _t.getFirstChild();
			a=expr(_t);
			_t = _retTree;
			b=sentence_list(_t);
			_t = _retTree;
			_t = __t383;
			_t = _t.getNextSibling();
			
						javaCode = "while( " + a + " ) {\n" + b + "}\n";
				
		}
		catch (RecognitionException ex) {
			reportError(ex);
			if (_t!=null) {_t = _t.getNextSibling();}
		}
		_retTree = _t;
		return javaCode;
	}
	
	public final String  fromto_loop(AST _t) throws RecognitionException {
		String javaCode = "";
		
		AST fromto_loop_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		
			String a[];
			String b, c;
		
		
		try {      // for error handling
			AST __t386 = _t;
			AST tmp237_AST_in = (AST)_t;
			match(_t,FROMTO_LOOP);
			_t = _t.getFirstChild();
			a=fromto_assign_statement(_t);
			_t = _retTree;
			b=expr(_t);
			_t = _retTree;
			c=sentence_list(_t);
			_t = _retTree;
			_t = __t386;
			_t = _t.getNextSibling();
			
					javaCode= "for(int " + a[0] + "; " + a[1]  +
					"  <= " + b + "; " + a[1] +"++) {\n" + c + "}\n";
					
				
		}
		catch (RecognitionException ex) {
			reportError(ex);
			if (_t!=null) {_t = _t.getNextSibling();}
		}
		_retTree = _t;
		return javaCode;
	}
	
	public final String  expr(AST _t) throws RecognitionException {
		String javaCode = "";
		
		AST expr_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		
			StringBuffer sb = new StringBuffer();
			String a, b = null;
		
		
		try {      // for error handling
			if (_t==null) _t=ASTNULL;
			switch ( _t.getType()) {
			case OR:
			{
				AST __t402 = _t;
				AST tmp238_AST_in = (AST)_t;
				match(_t,OR);
				_t = _t.getFirstChild();
				a=expr_and(_t);
				_t = _retTree;
				
						sb.append(a);
					
				{
				int _cnt404=0;
				_loop404:
				do {
					if (_t==null) _t=ASTNULL;
					if ((_tokenSet_0.member(_t.getType()))) {
						b=expr_and(_t);
						_t = _retTree;
						
								sb.append(" || " + b);
							
					}
					else {
						if ( _cnt404>=1 ) { break _loop404; } else {throw new NoViableAltException(_t);}
					}
					
					_cnt404++;
				} while (true);
				}
				_t = __t402;
				_t = _t.getNextSibling();
				
						javaCode = "(" + sb.toString() + ")";
					
				break;
			}
			case FLOAT_VAL:
			case INT_VAL:
			case AND:
			case TRUE:
			case FALSE:
			case GE_OP:
			case L_OP:
			case G_OP:
			case NOT_EQ:
			case EQ:
			case PLUS:
			case MINUS:
			case MOD:
			case MULT:
			case DIV:
			case RAISE:
			case STR_VAL:
			case ID:
			case STRUCT_CALL:
			case PREFIX:
			case EXPR:
			{
				javaCode=expr_and(_t);
				_t = _retTree;
				break;
			}
			default:
			{
				throw new NoViableAltException(_t);
			}
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			if (_t!=null) {_t = _t.getNextSibling();}
		}
		_retTree = _t;
		return javaCode;
	}
	
	public final String  elif_statement_list(AST _t) throws RecognitionException {
		String javaCode = "";
		
		AST elif_statement_list_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		
				String a = null, b = null, c;
			
		
		try {      // for error handling
			if (_t==null) _t=ASTNULL;
			switch ( _t.getType()) {
			case ELSE:
			{
				AST tmp239_AST_in = (AST)_t;
				match(_t,ELSE);
				_t = _t.getNextSibling();
				{
				if (_t==null) _t=ASTNULL;
				switch ( _t.getType()) {
				case SENTENCES:
				{
					a=sentence_list(_t);
					_t = _retTree;
					break;
				}
				case IS_NULL:
				{
					AST tmp240_AST_in = (AST)_t;
					match(_t,IS_NULL);
					_t = _t.getNextSibling();
					break;
				}
				default:
				{
					throw new NoViableAltException(_t);
				}
				}
				}
				
						
						if(a == null)
						{
							a = ";\n";
						}
						javaCode = "else {\n" + a + "}\n";
					
				break;
			}
			case FLOAT_VAL:
			case INT_VAL:
			case AND:
			case OR:
			case TRUE:
			case FALSE:
			case GE_OP:
			case L_OP:
			case G_OP:
			case NOT_EQ:
			case EQ:
			case PLUS:
			case MINUS:
			case MOD:
			case MULT:
			case DIV:
			case RAISE:
			case STR_VAL:
			case ID:
			case STRUCT_CALL:
			case PREFIX:
			case EXPR:
			{
				a=expr(_t);
				_t = _retTree;
				{
				if (_t==null) _t=ASTNULL;
				switch ( _t.getType()) {
				case SENTENCES:
				{
					b=sentence_list(_t);
					_t = _retTree;
					break;
				}
				case IS_NULL:
				{
					AST tmp241_AST_in = (AST)_t;
					match(_t,IS_NULL);
					_t = _t.getNextSibling();
					break;
				}
				default:
				{
					throw new NoViableAltException(_t);
				}
				}
				}
				c=elif_statement_list(_t);
				_t = _retTree;
				
						if(b == null)
						{
							b = ";\n";
						}
						javaCode = "else if(" + a + ") {\n" + b + "}\n" + c;
					
				break;
			}
			default:
			{
				throw new NoViableAltException(_t);
			}
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			if (_t!=null) {_t = _t.getNextSibling();}
		}
		_retTree = _t;
		return javaCode;
	}
	
	public final String  struct_call(AST _t) throws RecognitionException {
		String javaCode = "";
		
		AST struct_call_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		
			StringBuffer sb = new StringBuffer();
			String a = null, b;
		
		
		try {      // for error handling
			AST __t390 = _t;
			AST tmp242_AST_in = (AST)_t;
			match(_t,STRUCT_CALL);
			_t = _t.getFirstChild();
			a=variable_call(_t);
			_t = _retTree;
			
					sb.append(a);
				
			{
			_loop392:
			do {
				if (_t==null) _t=ASTNULL;
				if ((_t.getType()==ID)) {
					b=variable_call(_t);
					_t = _retTree;
					
							sb.append("." + b);
						
				}
				else {
					break _loop392;
				}
				
			} while (true);
			}
			_t = __t390;
			_t = _t.getNextSibling();
			
					javaCode = sb.toString();
				
		}
		catch (RecognitionException ex) {
			reportError(ex);
			if (_t!=null) {_t = _t.getNextSibling();}
		}
		_retTree = _t;
		return javaCode;
	}
	
	public final String [] mult_assign(AST _t) throws RecognitionException {
		String []javaCode = {""};
		
		AST mult_assign_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		
				String a = "";
				StringArray sa = new StringArray();
			
		
		try {      // for error handling
			{
			int _cnt378=0;
			_loop378:
			do {
				if (_t==null) _t=ASTNULL;
				if ((_tokenSet_1.member(_t.getType()))) {
					a=expr(_t);
					_t = _retTree;
					
							sa.add(a);
						
				}
				else {
					if ( _cnt378>=1 ) { break _loop378; } else {throw new NoViableAltException(_t);}
				}
				
				_cnt378++;
			} while (true);
			}
			
					javaCode = getArray(sa);
				
		}
		catch (RecognitionException ex) {
			reportError(ex);
			if (_t!=null) {_t = _t.getNextSibling();}
		}
		_retTree = _t;
		return javaCode;
	}
	
	public final String [] expr_list_full(AST _t) throws RecognitionException {
		String []javaCode = {};
		
		AST expr_list_full_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		
			StringArray sa = new StringArray();
			String e;
		
		
		try {      // for error handling
			{
			int _cnt400=0;
			_loop400:
			do {
				if (_t==null) _t=ASTNULL;
				if ((_tokenSet_1.member(_t.getType()))) {
					e=expr(_t);
					_t = _retTree;
					
							sa.add(e);
						
				}
				else {
					if ( _cnt400>=1 ) { break _loop400; } else {throw new NoViableAltException(_t);}
				}
				
				_cnt400++;
			} while (true);
			}
			
					javaCode = getArray(sa);
				
		}
		catch (RecognitionException ex) {
			reportError(ex);
			if (_t!=null) {_t = _t.getNextSibling();}
		}
		_retTree = _t;
		return javaCode;
	}
	
	public final String [] fromto_assign_statement(AST _t) throws RecognitionException {
		String []javaCode = {"", ""};
		
		AST fromto_assign_statement_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		
			String a, b;
		
		
		try {      // for error handling
			a=struct_call(_t);
			_t = _retTree;
			b=expr(_t);
			_t = _retTree;
			
					javaCode[0] = a + " = " + b;
					javaCode[1] = a;
				
		}
		catch (RecognitionException ex) {
			reportError(ex);
			if (_t!=null) {_t = _t.getNextSibling();}
		}
		_retTree = _t;
		return javaCode;
	}
	
	public final String  function_call(AST _t) throws RecognitionException {
		String javaCode = "";
		
		AST function_call_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		AST a = null;
		
			StringBuffer sb = new StringBuffer();
			String []b;
		
		
		try {      // for error handling
			a = (AST)_t;
			match(_t,ID);
			_t = _t.getNextSibling();
			b=expr_list(_t);
			_t = _retTree;
			
					sb.append(a.getText() + "(");
					for(int i = 0; i < b.length-1; i++)
					{
						sb.append(b[i] + ", ");
					}
					if(b.length > 0)
					sb.append(b[b.length-1]);
					javaCode = sb.toString();
				
		}
		catch (RecognitionException ex) {
			reportError(ex);
			if (_t!=null) {_t = _t.getNextSibling();}
		}
		_retTree = _t;
		return javaCode;
	}
	
	public final String [] expr_list(AST _t) throws RecognitionException {
		String []javaCode = {};
		
		AST expr_list_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		
			StringArray sa = new StringArray();
			String e;
		
		
		try {      // for error handling
			{
			_loop397:
			do {
				if (_t==null) _t=ASTNULL;
				if ((_tokenSet_1.member(_t.getType()))) {
					e=expr(_t);
					_t = _retTree;
					
							sa.add(e);
						
				}
				else {
					break _loop397;
				}
				
			} while (true);
			}
			
					javaCode = getArray(sa);
				
		}
		catch (RecognitionException ex) {
			reportError(ex);
			if (_t!=null) {_t = _t.getNextSibling();}
		}
		_retTree = _t;
		return javaCode;
	}
	
	public final String  variable_call(AST _t) throws RecognitionException {
		String javaCode = "";
		
		AST variable_call_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		AST a = null;
		
			StringBuffer sb = new StringBuffer();
			String []b=null;
		
		
		try {      // for error handling
			a = (AST)_t;
			match(_t,ID);
			_t = _t.getNextSibling();
			b=expr_list(_t);
			_t = _retTree;
			
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
		catch (RecognitionException ex) {
			reportError(ex);
			if (_t!=null) {_t = _t.getNextSibling();}
		}
		_retTree = _t;
		return javaCode;
	}
	
	public final String  expr_and(AST _t) throws RecognitionException {
		String javaCode = "";
		
		AST expr_and_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		
			StringBuffer sb = new StringBuffer();
			String a, b = null;
		
		
		try {      // for error handling
			if (_t==null) _t=ASTNULL;
			switch ( _t.getType()) {
			case AND:
			{
				AST __t406 = _t;
				AST tmp243_AST_in = (AST)_t;
				match(_t,AND);
				_t = _t.getFirstChild();
				a=expr_eq(_t);
				_t = _retTree;
				
						sb.append(a);
					
				{
				int _cnt408=0;
				_loop408:
				do {
					if (_t==null) _t=ASTNULL;
					if ((_tokenSet_2.member(_t.getType()))) {
						b=expr_eq(_t);
						_t = _retTree;
						
								sb.append(" && " + b);
							
					}
					else {
						if ( _cnt408>=1 ) { break _loop408; } else {throw new NoViableAltException(_t);}
					}
					
					_cnt408++;
				} while (true);
				}
				_t = __t406;
				_t = _t.getNextSibling();
				
							javaCode = "(" + sb.toString() + ")";
					
				break;
			}
			case FLOAT_VAL:
			case INT_VAL:
			case TRUE:
			case FALSE:
			case GE_OP:
			case L_OP:
			case G_OP:
			case NOT_EQ:
			case EQ:
			case PLUS:
			case MINUS:
			case MOD:
			case MULT:
			case DIV:
			case RAISE:
			case STR_VAL:
			case ID:
			case STRUCT_CALL:
			case PREFIX:
			case EXPR:
			{
				javaCode=expr_eq(_t);
				_t = _retTree;
				break;
			}
			default:
			{
				throw new NoViableAltException(_t);
			}
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			if (_t!=null) {_t = _t.getNextSibling();}
		}
		_retTree = _t;
		return javaCode;
	}
	
	public final String  expr_eq(AST _t) throws RecognitionException {
		String javaCode = "";
		
		AST expr_eq_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		
			String a, b = null;
		
		
		try {      // for error handling
			if (_t==null) _t=ASTNULL;
			switch ( _t.getType()) {
			case EQ:
			{
				AST __t410 = _t;
				AST tmp244_AST_in = (AST)_t;
				match(_t,EQ);
				_t = _t.getFirstChild();
				a=expr_eq(_t);
				_t = _retTree;
				b=expr_eq(_t);
				_t = _retTree;
				_t = __t410;
				_t = _t.getNextSibling();
				
						javaCode = "( " + a	+ " == " + b + " )";
					
				break;
			}
			case NOT_EQ:
			{
				AST __t411 = _t;
				AST tmp245_AST_in = (AST)_t;
				match(_t,NOT_EQ);
				_t = _t.getFirstChild();
				a=expr_eq(_t);
				_t = _retTree;
				b=expr_eq(_t);
				_t = _retTree;
				_t = __t411;
				_t = _t.getNextSibling();
				
						javaCode = "( " + a	+ " != " + b + " )";
					
				AST __t412 = _t;
				AST tmp246_AST_in = (AST)_t;
				match(_t,LE_OP);
				_t = _t.getFirstChild();
				a=expr_eq(_t);
				_t = _retTree;
				b=expr_eq(_t);
				_t = _retTree;
				_t = __t412;
				_t = _t.getNextSibling();
				
						javaCode = "( " + a	+ " <= " + b + " )";
					
				break;
			}
			case GE_OP:
			{
				AST __t413 = _t;
				AST tmp247_AST_in = (AST)_t;
				match(_t,GE_OP);
				_t = _t.getFirstChild();
				a=expr_eq(_t);
				_t = _retTree;
				b=expr_eq(_t);
				_t = _retTree;
				_t = __t413;
				_t = _t.getNextSibling();
				
						javaCode = "( " + a	+ " >= " + b + " )";
					
				break;
			}
			case L_OP:
			{
				AST __t414 = _t;
				AST tmp248_AST_in = (AST)_t;
				match(_t,L_OP);
				_t = _t.getFirstChild();
				a=expr_eq(_t);
				_t = _retTree;
				b=expr_eq(_t);
				_t = _retTree;
				_t = __t414;
				_t = _t.getNextSibling();
				
						javaCode = "( " + a	+ " < " + b + " )";
					
				break;
			}
			case G_OP:
			{
				AST __t415 = _t;
				AST tmp249_AST_in = (AST)_t;
				match(_t,G_OP);
				_t = _t.getFirstChild();
				a=expr_eq(_t);
				_t = _retTree;
				b=expr_eq(_t);
				_t = _retTree;
				_t = __t415;
				_t = _t.getNextSibling();
				
						javaCode = "( " + a	+ " > " + b + " )";
					
				break;
			}
			case FLOAT_VAL:
			case INT_VAL:
			case TRUE:
			case FALSE:
			case PLUS:
			case MINUS:
			case MOD:
			case MULT:
			case DIV:
			case RAISE:
			case STR_VAL:
			case ID:
			case STRUCT_CALL:
			case PREFIX:
			case EXPR:
			{
				javaCode=expr_mult(_t);
				_t = _retTree;
				break;
			}
			default:
			{
				throw new NoViableAltException(_t);
			}
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			if (_t!=null) {_t = _t.getNextSibling();}
		}
		_retTree = _t;
		return javaCode;
	}
	
	public final String  expr_mult(AST _t) throws RecognitionException {
		String javaCode = "";
		
		AST expr_mult_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		
			StringBuffer sb = new StringBuffer();
			String a, b;
		
		
		try {      // for error handling
			if (_t==null) _t=ASTNULL;
			switch ( _t.getType()) {
			case MULT:
			{
				AST __t417 = _t;
				AST tmp250_AST_in = (AST)_t;
				match(_t,MULT);
				_t = _t.getFirstChild();
				a=expr_prefix(_t);
				_t = _retTree;
				b=sub_expr_mult(_t);
				_t = _retTree;
				_t = __t417;
				_t = _t.getNextSibling();
				
						sb.append("( " + a + " * " + b + " )");
						javaCode = sb.toString();
					
				break;
			}
			case DIV:
			{
				AST __t418 = _t;
				AST tmp251_AST_in = (AST)_t;
				match(_t,DIV);
				_t = _t.getFirstChild();
				a=expr_prefix(_t);
				_t = _retTree;
				b=sub_expr_mult(_t);
				_t = _retTree;
				_t = __t418;
				_t = _t.getNextSibling();
				
						sb.append("( " + a + " / " + b + " )");
						javaCode = sb.toString();
					
				break;
			}
			case MOD:
			{
				AST __t419 = _t;
				AST tmp252_AST_in = (AST)_t;
				match(_t,MOD);
				_t = _t.getFirstChild();
				a=expr_prefix(_t);
				_t = _retTree;
				b=sub_expr_mult(_t);
				_t = _retTree;
				_t = __t419;
				_t = _t.getNextSibling();
				
						sb.append("( " + a + " % " + b + " )");
						javaCode = sb.toString();
					
				break;
			}
			case RAISE:
			{
				AST __t420 = _t;
				AST tmp253_AST_in = (AST)_t;
				match(_t,RAISE);
				_t = _t.getFirstChild();
				a=expr_prefix(_t);
				_t = _retTree;
				b=sub_expr_mult(_t);
				_t = _retTree;
				_t = __t420;
				_t = _t.getNextSibling();
				
						sb.append("( " + a + " ^ " + b + " )");
						javaCode = sb.toString();
					
				break;
			}
			case PLUS:
			{
				AST __t421 = _t;
				AST tmp254_AST_in = (AST)_t;
				match(_t,PLUS);
				_t = _t.getFirstChild();
				a=expr_prefix(_t);
				_t = _retTree;
				b=sub_expr_mult(_t);
				_t = _retTree;
				_t = __t421;
				_t = _t.getNextSibling();
				
						sb.append("( " + a + " + " + b + " )");
						javaCode = sb.toString();
					
				break;
			}
			case MINUS:
			{
				AST __t422 = _t;
				AST tmp255_AST_in = (AST)_t;
				match(_t,MINUS);
				_t = _t.getFirstChild();
				a=expr_prefix(_t);
				_t = _retTree;
				b=sub_expr_mult(_t);
				_t = _retTree;
				_t = __t422;
				_t = _t.getNextSibling();
				
						sb.append("( " + a + " - " + b + " )");
						javaCode = sb.toString();
					
				break;
			}
			case FLOAT_VAL:
			case INT_VAL:
			case TRUE:
			case FALSE:
			case STR_VAL:
			case ID:
			case STRUCT_CALL:
			case PREFIX:
			case EXPR:
			{
				javaCode=expr_prefix(_t);
				_t = _retTree;
				break;
			}
			default:
			{
				throw new NoViableAltException(_t);
			}
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			if (_t!=null) {_t = _t.getNextSibling();}
		}
		_retTree = _t;
		return javaCode;
	}
	
	public final String  expr_prefix(AST _t) throws RecognitionException {
		String javaCode = "";
		
		AST expr_prefix_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		
			String a;
			boolean b = true;
		
		
		try {      // for error handling
			if (_t==null) _t=ASTNULL;
			switch ( _t.getType()) {
			case PREFIX:
			{
				AST __t428 = _t;
				AST tmp256_AST_in = (AST)_t;
				match(_t,PREFIX);
				_t = _t.getFirstChild();
				{
				if (_t==null) _t=ASTNULL;
				switch ( _t.getType()) {
				case PLUS:
				{
					AST tmp257_AST_in = (AST)_t;
					match(_t,PLUS);
					_t = _t.getNextSibling();
					b = false;
					break;
				}
				case MINUS:
				{
					AST tmp258_AST_in = (AST)_t;
					match(_t,MINUS);
					_t = _t.getNextSibling();
					break;
				}
				default:
				{
					throw new NoViableAltException(_t);
				}
				}
				}
				a=expr_base(_t);
				_t = _retTree;
				_t = __t428;
				_t = _t.getNextSibling();
				
						if(b == false)
							javaCode = "(+" + a + ")";
						else
							javaCode = "(-" + a + ")";
					
				break;
			}
			case FLOAT_VAL:
			case INT_VAL:
			case TRUE:
			case FALSE:
			case STR_VAL:
			case ID:
			case STRUCT_CALL:
			case EXPR:
			{
				javaCode=expr_base(_t);
				_t = _retTree;
				break;
			}
			default:
			{
				throw new NoViableAltException(_t);
			}
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			if (_t!=null) {_t = _t.getNextSibling();}
		}
		_retTree = _t;
		return javaCode;
	}
	
	public final String  sub_expr_mult(AST _t) throws RecognitionException {
		String javaCode = "";
		
		AST sub_expr_mult_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		
			StringBuffer sb = new StringBuffer();
			String a, b, op;
		
		
		try {      // for error handling
			a=expr_prefix(_t);
			_t = _retTree;
			
					sb.append(a);
				
			{
			_loop426:
			do {
				if (_t==null) _t=ASTNULL;
				if (((_t.getType() >= PLUS && _t.getType() <= RAISE))) {
					{
					if (_t==null) _t=ASTNULL;
					switch ( _t.getType()) {
					case MULT:
					{
						AST tmp259_AST_in = (AST)_t;
						match(_t,MULT);
						_t = _t.getNextSibling();
						op = " * ";
						break;
					}
					case DIV:
					{
						AST tmp260_AST_in = (AST)_t;
						match(_t,DIV);
						_t = _t.getNextSibling();
						op = " / ";
						break;
					}
					case MOD:
					{
						AST tmp261_AST_in = (AST)_t;
						match(_t,MOD);
						_t = _t.getNextSibling();
						op = " % ";
						break;
					}
					case RAISE:
					{
						AST tmp262_AST_in = (AST)_t;
						match(_t,RAISE);
						_t = _t.getNextSibling();
						op = " ^ ";
						break;
					}
					case PLUS:
					{
						AST tmp263_AST_in = (AST)_t;
						match(_t,PLUS);
						_t = _t.getNextSibling();
						op = " + ";
						break;
					}
					case MINUS:
					{
						AST tmp264_AST_in = (AST)_t;
						match(_t,MINUS);
						_t = _t.getNextSibling();
						op = " - ";
						break;
					}
					default:
					{
						throw new NoViableAltException(_t);
					}
					}
					}
					b=expr_prefix(_t);
					_t = _retTree;
					
							sb.append(b + op);
						
				}
				else {
					break _loop426;
				}
				
			} while (true);
			}
			
					javaCode = sb.toString();
				
		}
		catch (RecognitionException ex) {
			reportError(ex);
			if (_t!=null) {_t = _t.getNextSibling();}
		}
		_retTree = _t;
		return javaCode;
	}
	
	public final String  expr_base(AST _t) throws RecognitionException {
		String javaCode = "";
		
		AST expr_base_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		AST a = null;
		AST b = null;
		AST c = null;
		
		try {      // for error handling
			if (_t==null) _t=ASTNULL;
			switch ( _t.getType()) {
			case INT_VAL:
			{
				a = (AST)_t;
				match(_t,INT_VAL);
				_t = _t.getNextSibling();
				
						javaCode = a.getText();
					
				break;
			}
			case FLOAT_VAL:
			{
				b = (AST)_t;
				match(_t,FLOAT_VAL);
				_t = _t.getNextSibling();
				
						javaCode = b.getText();
					
				break;
			}
			case STR_VAL:
			{
				c = (AST)_t;
				match(_t,STR_VAL);
				_t = _t.getNextSibling();
				
						javaCode = c.getText().replaceAll("\n", "\\\\n\" +\n\"");
					
				break;
			}
			case ID:
			{
				javaCode=function_call(_t);
				_t = _retTree;
				break;
			}
			case STRUCT_CALL:
			{
				javaCode=struct_call(_t);
				_t = _retTree;
				break;
			}
			case EXPR:
			{
				AST __t431 = _t;
				AST tmp265_AST_in = (AST)_t;
				match(_t,EXPR);
				_t = _t.getFirstChild();
				javaCode=expr(_t);
				_t = _retTree;
				_t = __t431;
				_t = _t.getNextSibling();
				break;
			}
			case TRUE:
			{
				AST tmp266_AST_in = (AST)_t;
				match(_t,TRUE);
				_t = _t.getNextSibling();
				
						javaCode = "true";
					
				break;
			}
			case FALSE:
			{
				AST tmp267_AST_in = (AST)_t;
				match(_t,FALSE);
				_t = _t.getNextSibling();
				
						javaCode = "false";
					
				break;
			}
			default:
			{
				throw new NoViableAltException(_t);
			}
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			if (_t!=null) {_t = _t.getNextSibling();}
		}
		_retTree = _t;
		return javaCode;
	}
	
	
	public static final String[] _tokenNames = {
		"<0>",
		"EOF",
		"<2>",
		"NULL_TREE_LOOKAHEAD",
		"FLOAT_VAL",
		"INT_VAL",
		"\"prog\"",
		"\"alg\"",
		"\"func\"",
		"\"y\"",
		"\"de\"",
		"\"entrada\"",
		"\"salida\"",
		"\"entsal\"",
		"\"ent\"",
		"\"sal\"",
		"\"dev\"",
		"\"proc\"",
		"\"fin\"",
		"\"cons\"",
		"\"tipos\"",
		"\"tabla\"",
		"\"reg\"",
		"\"freg\"",
		"\"var\"",
		"\"prin\"",
		"\"escribir\"",
		"\"leer\"",
		"\"si\"",
		"\"otras\"",
		"\"nula\"",
		"\"fsi\"",
		"\"mientras\"",
		"\"fm\"",
		"\"desde\"",
		"\"hasta\"",
		"\"fd\"",
		"\"o\"",
		"\"no\"",
		"\"verdadero\"",
		"\"falso\"",
		"COMMA",
		"ASSIGN",
		"LE_OP",
		"GE_OP",
		"L_OP",
		"G_OP",
		"NOT_EQ",
		"EQ",
		"P",
		"EP",
		"K",
		"EK",
		"B",
		"EB",
		"DOT",
		"SC",
		"C",
		"BAR",
		"PLUS",
		"MINUS",
		"MOD",
		"MULT",
		"DIV",
		"RAISE",
		"NL",
		"COMMENT",
		"COMMENT_C",
		"STR_VAL",
		"WHITE",
		"DIGIT",
		"ALFA",
		"ALFANUM",
		"SCRIPT",
		"NUMBER",
		"ID",
		"NLS",
		"DECLARATIONS_BLOCK",
		"SENTENCES",
		"IF_SENTENCE",
		"PROC_CALL",
		"ASSIGNMENT",
		"IO_STATEMENT",
		"WHILE_LOOP",
		"FROMTO_LOOP",
		"LIBRARY",
		"ALGORITHM",
		"FUNCTION",
		"PROCEDURE",
		"ID_LIST",
		"ARRAY_DIMENSIONS",
		"PROGRAM",
		"HEADER",
		"CHAR_VAL",
		"STRUCT_CALL",
		"PREFIX",
		"EXPR"
	};
	
	private static final long[] mk_tokenSet_0() {
		long[] data = { -575913745268604368L, 7516194833L, 0L, 0L};
		return data;
	}
	public static final BitSet _tokenSet_0 = new BitSet(mk_tokenSet_0());
	private static final long[] mk_tokenSet_1() {
		long[] data = { -575913607829650896L, 7516194833L, 0L, 0L};
		return data;
	}
	public static final BitSet _tokenSet_1 = new BitSet(mk_tokenSet_1());
	private static final long[] mk_tokenSet_2() {
		long[] data = { -575913745268604880L, 7516194833L, 0L, 0L};
		return data;
	}
	public static final BitSet _tokenSet_2 = new BitSet(mk_tokenSet_2());
	}
	
