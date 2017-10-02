#ifndef ATOM_H
#define ATOM_H

#include <string>
using std::string;

class Number;
class Variable;
class Atom {
public:
  Atom (string s):_symbol(s) {}
  // bool operator ==(Atom a) {return _symbol == a._symbol;}
  bool match( Atom& );
  bool match( Number& );
  bool match( Variable& );
  string _symbol;
};

#endif
