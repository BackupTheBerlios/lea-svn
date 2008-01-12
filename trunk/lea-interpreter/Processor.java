/////////////////////////////////////
// Processor.java (clase principal)
/////////////////////////////////////
import java.io.*;

import com.sun.xml.internal.fastinfoset.util.StringArray;

import antlr.ANTLRException;
import antlr.Token;
import antlr.collections.AST;
import antlr.debug.misc.ASTFrame;
import java.util.Map.Entry;
import java.util.Hashtable;
import java.lang.Runtime;
public class Processor {
	public static void main(String args[]) throws Exception {
		try {
			FileInputStream fis = new FileInputStream(args[0]);
			String []javaCode;
			Analex analex = null;
			Anasint anasint = null;
			Evaluator evaluator = null;
			AST tree = null;
			analex = new Analex(fis);
			anasint = new Anasint(analex);
			anasint.setASTNodeClass("LeaAST");
			anasint.program();
			tree = anasint.getAST();
			//ASTFrame frame= new ASTFrame(args[0],tree);
			//frame.setVisible(true);

			evaluator = new Evaluator();
			
			javaCode = evaluator.program(tree);
			
			try{
				// Escribe el código en un temporal
				FileWriter fstream = new FileWriter("/tmp/" + javaCode[1] + ".java");
				BufferedWriter out = new BufferedWriter(fstream);
				out.write(javaCode[0]);
				out.close();
				// Compila el código
				exec("rm " + "/tmp/" + javaCode[1] + ".{class,java}");
				exec("javac " + "/tmp/" + javaCode[1] + ".java");
				// Ejecuta el código
				exec("java " + "-cp /tmp/ " + javaCode[1]);
			}catch (Exception e){
				System.err.println("Error: " + e.getMessage());
			}
			
//			System.out.println(anasint.getAST().toStringTree());
//			Token token = analex.nextToken( ); // first token
//			 while (token.getType( ) != Token.EOF_TYPE) {
			  // mientras no se alcance el último token
//			  System.out.println(token.toString());
//			  token = analex.nextToken( );
//			}
		} catch (ANTLRException ae) {
			System.err.println(ae.getMessage());
		} catch (FileNotFoundException fnfe) {
			System.err.println("No se encontró el fichero");
		}
	}
	
	static protected void exec(String command) throws Exception
	{
		Process p = Runtime.getRuntime().exec(command);
		BufferedReader input = new BufferedReader (
				new InputStreamReader(p.getInputStream()));
		String line;
		while ((line = input.readLine()) != null) {
			System.out.println(line);
		}
		input.close();
	}
}

