#ifndef ITERATOR_H
#define ITERATOR_H

#include "struct.h"
#include "list.h"
#include<iostream>
using namespace std;
#include <list>

template< class T >
class Iterator {
public:
  virtual void first() = 0;
  virtual void next() = 0;
  virtual Term* currentItem() const = 0;
  virtual bool isDone() const = 0;
};

template<class T>
class DFSIterator :public Iterator<T>{
public:
  DFSIterator( Term* temp ):_index(0), _temp( temp ) {
    Iterator<T>* it = temp->createIterator();
    it->first();
    dfsVisit( it );
  }
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
    }
  }
private:
  int _index;
  vector<Term*> allTerm;
  Term* _temp;
};


template<class T>
class BFSIterator :public Iterator<T>{
public:
  BFSIterator(Term * temp):_index(0) {
     Iterator<T>* it = temp->createIterator();
     allIterator.push_back( it );
     it->first();
     bsf();
  }
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
      Term* tterm = it->currentItem();
      allTerm.push_back( tterm );
      it->next();
      while( !it->isDone() ){
        tterm = it->currentItem();
        allTerm.push_back( tterm );
        Iterator<T> *childIt = tterm->createIterator();
        if( !childIt->isDone() ) {
          allIterator.push_back( childIt );
        }
        it->next();
      } // while
      allIterator.pop_front();
    } // while
  }

  void print(){
    for( int i = 0; i < allTerm.size(); i++ )
      cout << allTerm[i]->symbol();
  }


private:
  int _index;
  list<Iterator<T>*> allIterator;
  vector<Term*> allTerm;
  Term* currTerm;
};

template<class T>
class NullIterator :public Iterator<T>{
public:
  NullIterator(Term* n){}
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
  StructIterator(Struct *s): _index(0), _s(s) {}
  int _index;
  Struct* _s;
};

template<class T>
class ListIterator :public Iterator<T> {
public:
  ListIterator(List *list): _index(0), _list(list) {}

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
  int _index;
  List* _list;
};
#endif
