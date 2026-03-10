//Chapter 13 Question 1
//Choosing to add multiple inheritance to Lox

//Modifying the LoxClass.java (updating the constructor)
LoxClass(String name, List<LoxClass> superclasses,
        Map<String, LoxFunction> methods) {
    this.name = name;
    this.superclasses = superclasses;
    this.methods = methods;
    }


//Changing the findMethod() logic as well
LoxFunction findMethod(String name) {
    if (methods.containsKey(name)) {
        return methods.get(name);
    }

    for (LoxClass superclass : superclasses) {
        LoxFunction method = superclass.findMethod(name);
        if (method != null) return method;
    }

    return null;
}

//Modiying the classDeclaration() in Parser.java
List<Expr.Variable> superclasses = new ArrayList<>();
if (match(LESS)) {
    do {
        consume(IDENTIFIER, "Expect superclass name.");
        superclasses.add(new Expr.Variable(previous()));
    } while (match(COMMA));
}

//Lastly some changes in the ASTPrinter.java 
@Override 
public String visitBreakStmt(Stmt.break stmt) {
    return "break";
} 

@Override 
public String visitContinueStmt(Stmt.Continue stmt) {
    StringBuilder builder = new StringBuilder();
    builder.append("(class " + stmt.name.lexeme);

    if (!stmt..superclasses.isEmpty()){
        builder.append("<");
        for (Expr.Variable superclass : stmt.superclasses){
            builder.append(" " + print(superclass));
        }
    }
} 