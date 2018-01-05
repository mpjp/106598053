#include <iostream>
#include <string>
#include <string.h>

#include "atom.h"
#include "variable.h"
#include "exp.h"
#include "parser.h"

#include "list.h"
#include "struct.h"

using namespace std;

int main() {
  string::size_type position;
  string str , result =  "";
  cout << "?-";

  // Scanner s("X=1,X=2.");
  // Parser p(s);
  // p.buildExpression();
  // result = showResult( p.getExpressionTree() );
  // cout << "res = " << result;

  while( str != "halt" ){

    getline(cin, str, '\n');
    position = str.find(".");
    if ( str != " " || str != "\n") result += str;
    if ( position != str.npos ) {
      // cout << "find!";
      //cout << result << "\n";
      //result = "";

      Scanner s(result);
      Parser p(s);
      try{
        p.buildExpression();
        string result = showResult( p.getExpressionTree() );
        cout << result << "\n\n";
      } catch (std::string & msg) {
        cout << msg << "\n";
      }

      result = "";
    } // if

    if ( result == "" ) cout << "?-";
    else if ( result != "halt" ) cout << "|  ";
  } // while

}
