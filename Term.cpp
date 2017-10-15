#include "iostream"
#include "term.h"
#include "variable.h"

bool Term::match(Term & term) {
  Variable * var_p = dynamic_cast<Variable *>(&term);
  if( var_p ){
    return symbol() == var_p->value() ;
  }
  return symbol() == term.symbol();
}
