#include "term.h"
#include "iterator.h"
#include <typeinfo>

Iterator<Term*> * Term::createIterator(){
  return new NullIterator<Term*>(this);
}
