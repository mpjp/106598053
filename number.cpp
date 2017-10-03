#include "number.h"
#include "atom.h"
#include "variable.h"
#include <iostream>
#include <string>

using std::to_string;


string Number::value(){
  return std::to_string(_num );
}

string Number::symbol(){
  return _symbol;
}

bool Number::match( Atom& a ){
  return false;
}

bool Number::match( Variable& var ){
  if( var.getAssignable() ){
    var.setAssignableFalse();
    var.setValue( to_string(_num) );
    return true;
  }
  else if( !var.getAssignable() ){
    if( var.value() == to_string(_num) ) return true;
  }
  return false;
}

bool Number::match( Number& compar ){  //***
  return std::to_string(_num) == compar.value();
}
