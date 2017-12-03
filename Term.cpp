#include "term.h"
#include "iterator.h"
#include <typeinfo>

Iterator * Term::createIterator(){
  return new NullIterator(this);
}
