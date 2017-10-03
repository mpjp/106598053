#include "atom.h"
#include "number.h"
#include "variable.h"

#include <string>
#include<iostream>
using std::string;

bool Atom::match( Atom& a ){
  return _symbol == a._symbol;
}

bool Atom::match( Number& b ){
  return false;
}

bool Atom::match( Variable& var ){  // tom = X
  if( var.getAssignable() ) {
    var.setAssignableFalse();
    var.setValue( _symbol );
    return true;
  }
  else if( var.value() == _symbol ) return true;

  return false;
}
