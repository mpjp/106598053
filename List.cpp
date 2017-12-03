#include "list.h"
#include "iterator.h"

Iterator * List::createIterator()
{
  return new ListIterator(this);
}

Iterator * List::createBFSIterator()
{
  return new BFSIterator<List>(this);
}

Iterator * List::createDFSIterator()
{
  return new DFSIterator<List>(this);
}
