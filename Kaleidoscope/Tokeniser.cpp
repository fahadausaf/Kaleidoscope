#include <iostream>
using namespace std;

enum Token {
  tok_eof = -1,

  // commands
  tok_def = -2,
  tok_extern = -3,

  // primary
  tok_identifier = -4,
  tok_number = -5
};

static std::string IdentifierStr;
static double NumVal;

static int gettok(){
  static int LastChar = ' ';

  // Skip any whitespace.
  while (isspace(LastChar))
    LastChar = getchar();

  if (isalpha(LastChar)){ // identifier: [a-zA-Z][a-zA-Z0-9]*
    IdentifierStr = LastChar;
    while (isalpha((LastChar = getchar())))
      IdentifierStr += LastChar;

    if (IdentifierStr == "def")
      return tok_def;
    if (IdentifierStr == "extern")
      return tok_extern;
    return tok_identifier;
  }

  if (isdigit(LastChar) || LastChar == '.') { // Number: [0-9.]+
    std::string NumStr;
    do {
      NumStr += LastChar;
      LastChar = getchar();
    } while (isdigit(LastChar) || LastChar == '.');

    NumVal = strtod(NumStr.c_str(), nullptr);
    return tok_number;
  }

  if (LastChar == '#') {
    // Comment until end of line.
    while (LastChar != EOF && LastChar != '\n' && LastChar != '\r');
      LastChar = getchar();

    if (LastChar != EOF)
      return gettok();
  }

  return 1;
}

int main ()
{
  cout << "Type a program" << endl;
  cout << gettok() << endl;
  return 0;
}
