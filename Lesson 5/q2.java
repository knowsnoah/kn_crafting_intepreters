//Chapter 10 Challenge Question 2
//We need to modify three things: AST, parser, and the Interpreter

//AST Change: In Expr.java add a new class below:
static class Function extends Expr {
  final List<Token> params;
  final List<Stmt> body;

  Function(List<Token> params, List<Stmt> body) {
    this.params = params;
    this.body = body;
  }

  <R> R accept(Visitor<R> visitor) {
    return visitor.visitFunctionExpr(this);
  }
}


//For the Parser change, in Parser.java, modify primary()
if (match(FUN)) return functionExpression();

//then implement
private Expr functionExpression() {
  consume(LEFT_PAREN, "Expect '(' after 'fun'.");

  List<Token> parameters = new ArrayList<>();
  if (!check(RIGHT_PAREN)) {
    do {
      if (parameters.size() >= 255) {
        error(peek(), "Can't have more than 255 parameters.");
      }

      parameters.add(
          consume(IDENTIFIER, "Expect parameter name."));
    } while (match(COMMA));
  }

  consume(RIGHT_PAREN, "Expect ')' after parameters.");
  consume(LEFT_BRACE, "Expect '{' before function body.");

  List<Stmt> body = block();
  return new Expr.Function(parameters, body);
}

//Lastly the interpreter change, in Interpreter.java implement
@Override
public Object visitFunctionExpr(Expr.Function expr) {
  return new LoxFunction(expr, environment);
}