#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
using std::string;

class Atom;
class Number;
class Variable{
public:
  Variable(string s):_symbol(s){
    _assignable = true;
  }
  string const _symbol;
  string value();
  string symbol();
  bool match( Atom& atom );
  bool match( Number& );
  bool getAssignable();
  void setAssignableFalse();
  void setValue( string );

private:
  string _value;
  bool _assignable ;  //= true
};

#endif
