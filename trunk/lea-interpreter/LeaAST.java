import antlr.*;
import antlr.collections.*;
@SuppressWarnings("serial")

public class LeaAST extends CommonAST {
     // Nuevo atributo
     int linea;
     // Constructor vacío
     public LeaAST() {
     }
     // Constructor a partir de un token
     public LeaAST(Token t){
         initialize(t);
     }
//   Constructor a partir de un árbol
     public LeaAST(AST a) {
          initialize(a);
     }
//      Inicialización a partir de un token
     public void initialize(Token t) {
        super.initialize(t);
        setLinea(t.getLine());
     }
//      Inicialización a partir de un árbol
     public void initialize(AST a)
     {
        super.initialize(a);
        if(a instanceof LeaAST) {
           setLinea(((LeaAST)a).getLinea());
        }
     }
//      Métodos de actualización y acceso
//      del atributo linea
     public void setLinea(int l) {
        linea=l;
     }
     public int getLinea() {
        return linea;
     }
//      Redefinición del método toString
     public String toString() {
        StringBuffer sb = new StringBuffer("");
        String textoCommonAST = super.toString();
        sb.append(textoCommonAST);
        sb.append( " (línea: ");
        sb.append( linea );
        sb.append( ")" );
        return sb.toString();
     }

}
