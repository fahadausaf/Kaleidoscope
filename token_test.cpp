#include <iostream>
#include <memory>
#include <vector>

using namespace std;

// The Lexer returns tokens [0-255] if it is an unknown character, otherwise
// on of these for known things.

enum Token{
  tok_eof = -1,

  // commands
  tok_def = -2,
  tok_extern = -3,

// primary
  tok_identifier = -4,
  tok_number = -5,
};

static string IdentifierStr;
static double NumVal;

/// gettok - Return the next token from standard input.
static int gettok(){
  static int LastChar = ' ';

  // Skip any whitespace.
  while (isspace(LastChar))
    LastChar = getchar();

  if (isalpha(LastChar)) { // identifier: [a-zA-Z][a-zA-Z0-9]*
    IdentifierStr = LastChar;
    while (isalnum((LastChar = getchar())))
      IdentifierStr += LastChar;

    if (IdentifierStr == "def")
      return tok_def;
    if (IdentifierStr == "extern")
      return tok_extern;
    return tok_identifier;
  }

  if (isdigit(LastChar) || LastChar == '.') { // Number: [0-9.]+
    string NumStr;
    do{
      NumStr += LastChar;
      LastChar = getchar();
    } while (isdigit(LastChar) || LastChar == '.');

    NumVal = strtod(NumStr.c_str(), 0);
    return tok_number;
  }

  if (LastChar == '#') {
    // Comment until end of line
    do
      LastChar = getchar();
    while (LastChar != EOF && LastChar != '\n' && LastChar != '\r');

    if (LastChar != EOF)
      return gettok();
  }

  // Check for end of file. Don't eat the EOF.
  if (LastChar == EOF)
    return tok_eof;

  // Otherwise, just return the character as its ascii value.
  int ThisChar = LastChar;
  LastChar = getchar();
  return ThisChar;
}

//------------------------------------------------------------//

/// ExprAST - Base class for all expression nodes.
class ExprAST {
public:
  virtual ~ExprAST() {}
};

/// NumberExprAST - Expression class for numeric literals like "1.0".
class NumberExprAST : public ExprAST {
  double Val;

public:
  NumberExprAST(double Val) : Val(Val) {}
};

/// VariableExprAST - Expression class for referencing a variable, like "a".
class VariableExprAST : public ExprAST {
  string Name;

public:
  VariableExprAST(const string &Name) : Name(Name) {}
};

/// BinaryExprAST - Expression class for a binary operator.
class BinaryExprAST : public ExprAST {
  char Op;
  unique_ptr<ExprAST> LHS, RHS;

public:
  BinaryExprAST(char op, unique_ptr<ExprAST> LHS, unique_ptr<ExprAST> RHS)
    : Op(op), LHS(move(LHS)), RHS(move(RHS)){}
};

/// CallExprAST - Expression class for function calls.
class CallExprAST : public ExprAST {
  string Callee;
  vector<std::unique_ptr<ExprAST>> Args;

public:
  CallExprAST(const string &Callee, vector<std::unique_ptr<ExprAST>> Args)
    : Callee(Callee), Args(move(Args)) {}
};

/// PrototypeAST - This class represents the "prototype" for a function,
/// which captures its name, and its argument names (thus implicitly the number
/// of arguments the function takes).
class PrototypeAST {
  string Name;
  vector<string> Args;

public:
  PrototypeAST(const string &name, vector<string> Args)
    : Name(name), Args(move(Args)) {}

  const string &getName() const { return Name; }
};

/// FunctionAST - This class represents a function definition itself.
class FunctionAST {
  unique_ptr<PrototypeAST> Proto;
  unique_ptr<ExprAST> Body;

public:
  FunctionAST(unique_ptr<PrototypeAST> Proto, unique_ptr<ExprAST> Body)
    : Proto(move(Proto)), Body(move(Body)) {}
};

//------------------------------------------------------------------//
// 2.3. PArser Basic

//auto LHS = llvm::make_unique<VariableExprAST>("x");

int main(){
  cout << "Lexer Test";

  return 0;
}
