// Chapter 13 Question 3
// One feature I noticed Lox was missing is a simple built-in function
// to get the length of a string, similar to len() in Python.
// Many object-oriented languages provide an easy way to get the
// length of a string or collection, but Lox does not include this
// functionality by default.

// I implemented a native len() function that takes a single argument.
// If the argument is a string, it returns the string’s length.
// Otherwise, it throws a runtime error.

globals.define("len", new LoxCallable() {
  @Override
  public int arity() {
    return 1;
  }

  @Override
  public Object call(Interpreter interpreter, List<Object> arguments) {
    Object arg = arguments.get(0);

    if (arg instanceof String) {
      return ((String) arg).length();
    }

    throw new RuntimeError(
        null,
        "len() expects a string."
    );
  }

  @Override
  public String toString() {
    return "<native fn>";
  }
});