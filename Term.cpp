#include "iostream"
#include "term.h"
#include "variable.h"
#include "list.h"

bool Term::match(Term & term) {
  Variable * var_p = dynamic_cast<Variable *>(&term);
  List * list_p = dynamic_cast<List *>(&term);
  if( var_p ){
    if( var_p->getassignable() ) {
      // cout << "!!";
      var_p->match( *this );
    }
    // cout << "\nsymbol() = " << symbol() << "var = " << var_p->value();
    return symbol() == var_p->value() ;
  }
  else if( list_p ){
    return false;
  }
  return symbol() == term.symbol();
}
