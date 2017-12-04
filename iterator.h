#ifndef ITERATOR_H
#define ITERATOR_H

#include "struct.h"
#include "list.h"
#include<iostream>
#include <list>

using namespace std;

template< class T >
class Iterator {
public:
  virtual void first() = 0;
  virtual void next() = 0;
  virtual T currentItem() const = 0;
  virtual bool isDone() const = 0;
};

template<class T>
class DFSIterator :public Iterator<T>{
public:
  friend class Struct;
  friend class List;
  void first(){
    _index = 0;
  }
  Term* currentItem() const{
    return allTerm[_index];
  }
  bool isDone() const{
    return _index >= allTerm.size();
  }
  void next(){
    _index++;
  }
  void dfsVisit( Iterator<T>* it ){
    Iterator<T> *itemp;
    while( !it->isDone() ){
      Term* tterm = it->currentItem();
      itemp = tterm->createIterator();
      allTerm.push_back( tterm );
      it->next();
      if( !itemp->isDone() ) dfsVisit( itemp );
    } // while
  }
private:
  DFSIterator( T temp ):_index(0), _temp( temp ) {
    Iterator<T>* it = temp->createIterator();
    it->first();
    dfsVisit( it );
  }
  int _index;
  vector<Term*> allTerm;
  Term* _temp;
};


template<class T>
class BFSIterator :public Iterator<T>{
public:
  friend class Struct;
  friend class List;

  void first() {
    _index = 0;
  }
  Term* currentItem() const {
    return allTerm[_index];
  }
  void next() {
    _index++;
  }
  bool isDone() const {
    return _index >= allTerm.size();
  }

  void bsf(){
    while( !allIterator.empty() ){
      Iterator<T> *it = allIterator.front();
      it->first();
      while( !it->isDone() ){
        Term* tterm = it->currentItem();  //Term*
        allTerm.push_back( tterm );
        Iterator<T> *childIt = tterm->createIterator();
        childIt->first();
        if( !childIt->isDone() ) {
          allIterator.push_back( childIt );
        }
        it->next();
      } // while
      allIterator.pop_front();
    } // while
  }

private:
  BFSIterator(T temp):_index(0) {
     Iterator<T>* it = temp->createIterator();
     allIterator.push_back( it );
     it->first();
     bsf();
  }
  int _index;
  list<Iterator<T>*> allIterator;
  vector<Term*> allTerm;
  Term* currTerm;
};

template<class T>
class NullIterator :public Iterator<T>{
public:
  NullIterator(T n){}
  void first(){}
  void next(){}
  Term* currentItem() const{
      return nullptr;
  }
  bool isDone() const{
    return true;
  }

};

template<class T>
class StructIterator :public Iterator<T> {
public:
  friend class Struct;
  void first() {
    _index = 0;
  }

  Term* currentItem() const {
    return _s->args(_index);
  }

  bool isDone() const {
    return _index >= _s->arity();
  }

  void next() {
    _index++;
  }
private:
  StructIterator(Struct* s): _index(0), _s(s) {}
  int _index;
  Struct* _s;
};

template<class T>
class ListIterator :public Iterator<T> {
public:
  friend class List;

  void first() {
    _index = 0;
  }

  Term* currentItem() const {
    return _list->args(_index);
  }

  bool isDone() const {
    return _index >= _list->arity();
  }

  void next() {
    _index++;
  }

private:
  ListIterator(List *list): _index(0), _list(list) {}
  int _index;
  List* _list;
};
#endif
