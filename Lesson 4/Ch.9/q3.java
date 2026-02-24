//Challenge Question #3
//This demonstrates the changes needed to be made in the 
//craftinginterpreter package to allow for the addition of break statements

//Editing the AST
defineAs(outputDir, "Stmt", Arrays..asList(
    "Block : List<Stmt> statements",
    "Break : ", //<---
    "Expression : Expr expression",
    "If : Expr condition, Stmt thenBranch, Stmt elseBranch",
    "Print : Expr expression",
    "Var : Token name, Expr intializer",
    "While : Expr condition, Stmt body"

));

//Store paramters in fields
String[] fields;
if (fieldList.isEmpty()){
    fields = new String[0]; 
} else{
    fields = fieldList.split(",");
}


//Adding the "break keyword" to the parser
AND, BREAK, CLAS, ELSE, FALSE, FUN, FOR, IF, NIL, OR,
keywords.put("break", BREAK);

//Parsing the "break" statement
if (match(BREAK)) return breakStatement();

//method 
private Stmt breeakStatement(){
    consume(SEMICOLON, "EXPECT ';' after 'break'.");
    return new Stmt.Break();
}



//Preventing illegal break 
//In the parser
private int loopDepth = 0;

//In the forStatment();
try {
    loopDepth++;
    Stmt body = statement();

    if (increment != null) {
        body = new Stmt.Block(Arrays.asList(
            body, new Stmt.Expression(increment)));
    }

    if (condition == null) condition = new Expr.Literal(true);
    body = new Stmt.While(condition, body);

    if (initializer != null) {
        body = new Stmt.Block(Arrays.asList(initializer, body));
    }

    return body;

} finally {
    loopDepth--;
}

//In the whileStatement();
try {
    loopDepth++;
    Expr condition = expression();
    Stmt body = statement();

    return new Stmt.While(condition, body);

} finally {
    loopDepth--;
}

//Updating breakStatement()
private Stmt breakStatement(){
    if (loopDepth == 0 ){
        error(previous(), "Must be inside a loop to use 'break'.");
    }
    consume(SEMICOLON, "Expect ';' after 'break'.");
    return new Stmt.Break();
}


//Finally implement the "break" exception
@Override
public Void visitBreakStmt(Stmt.Break stmt){
    throw new BreakException();
}

//Catching the break in a while loop
@Override
public Void visitWhileStmt(Stmt.While stmt){
    try {
        while (isTruthy(evaluate(stmt.condition))){
            execute(stmt.body);
        }
    } catch (Break Exception ex) {
        //Do nothing just catch the exception to break out of the loop
    }
    return null;
}