#include "iostream"
#include "term.h"
#include "variable.h"

bool Term::match(Term & term) {
  Variable * var_p = dynamic_cast<Variable *>(&term);
  if( var_p ){
    if( var_p->mem_assignable() ) {
      // cout << "!!";
      var_p->match( *this );
    }
    // cout << "\nsymbol() = " << symbol() << "var = " << var_p->value();
    return symbol() == var_p->value() ;
  }
  return symbol() == term.symbol();
}
