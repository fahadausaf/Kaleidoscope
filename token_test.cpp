#include <iostream>
using namespace std;

// The Lexer returns tokens [0-255] if it is an unknown character, otherwise
// on of these for known things.

enum Token{
  tok_eof = -1,

  // commands
  tok_def = -2
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

  if (isalpha(LastChar)) {
    IdentifierStr = LastChar;
    while (isalnum((LastChar = getchar())))
      IdentifierStr += LastChar;

    if (IdentifierStr == "def")
      return tok_def;
    if (IdentifierStr == "extern")
      return tok_extern;
    return tok_identifier;
  }
}

int main(){
  cout << "Lexer Test";

  return 0;
}
