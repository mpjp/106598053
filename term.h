#ifndef TERM_H
#define TERM_H

#include <string>

using std::string;
// #include "variable.h"

class Term{

public:
  virtual string symbol() const= 0;

  virtual string value() const{
    return symbol();
  };

  // virtual bool match(Term & term) {
  //   return symbol() == term.symbol();
  // }

  virtual bool match(Term & term) ;


};
#endif
