#include "variable.h"
#include "atom.h"
#include "number.h"

#include<iostream>
#include <string>
using namespace std;

string Variable::value(){
  return _value;
}

string Variable::symbol(){
  return _symbol;
}

bool Variable::match( Atom& atom ){
  bool ret = _assignable;
  if(_assignable){
    _value = atom._symbol ;
    _assignable = false;
  }
  else if( !_assignable ){
    if( atom._symbol == _value ) return true;
  }
  return ret;
}

bool Variable::match( Number& num ){
  // string num_to_string = to_string( num.value() );
  string num_to_string = num.value() ;
  if( _assignable ) {
    setValue( num_to_string );
    _assignable = false;
    return true;
  }
  else {
    if ( value() == num_to_string ) return true;
  }
  return false;
}

void Variable::setValue( string value ){
  _value = value;
}

bool Variable::getAssignable(){
  return _assignable;
}

void Variable::setAssignableFalse(){
   _assignable = false;
}
