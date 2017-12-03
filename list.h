#ifndef LIST_H
#define LIST_H
#include <string>
#include <vector>
#include "term.h"
#include "variable.h"
using std::vector;
using std::string;
#include <stdexcept>

// class Iterator;
class List : public Term {
public:
  List () {}
  List (vector<Term *> const & elements):_elements(elements){}

  Iterator * createIterator();
  Iterator * createBFSIterator();
  Iterator * createDFSIterator();

  Term * args(int index) {
    return _elements[index];
  }

  int arity() const {return _elements.size();}

  Term * head() {
    if( _elements.size() <= 0 )  //throw "Accessing head in an empty list";
      throw std::string("Accessing head in an empty list");
    else
      return _elements[0];
  } // head()

  List * tail() {
    if( _elements.size() <= 0 )
      throw std::string("Accessing tail in an empty list"); // std::invalid_argument
    else {
      std::vector<Term*> v;
      for (std::vector<Term*>::iterator it = _elements.begin()+1 ; it != _elements.end(); ++it)
        v.push_back(*it);
        List *list = new List(v);
        return list;
    } // else
  } // tail()

public:

  string symbol() const{
    string ret = "[";
    if( _elements.size() != 0 ){
      for(int i = 0; i < _elements.size() - 1 ; i++)
        ret += _elements[i]-> symbol() + ", ";
      ret += _elements[_elements.size()-1]-> symbol() ;
    }
    ret += "]";
    return  ret;
  } // symbol

  string value() const {
    string ret = "[";
    if( _elements.size() != 0 ){
      for(int i = 0; i < _elements.size() - 1 ; i++)
        ret += _elements[i]->value() + ", ";
      ret += _elements[_elements.size()-1]->value() ;
    } // if
    ret += "]";
    return  ret;
  } // value

  bool match( Term &term ){
    Variable * var_p = dynamic_cast<Variable *>(&term);
    List * list_p = dynamic_cast<List *>(&term);
    if( !var_p && !list_p ) return false;
    if( var_p ) {
      string var_name = var_p->symbol();
      for( int i = 0; i < _elements.size() ; i++)
        if( _elements[i]->symbol() == var_name ) return false;
      return true;
    }
    else if( list_p ) {
      if( _elements.size() != (list_p->_elements).size() ) return false;
      for( int i = 0; i < _elements.size() ; i++)
        if( _elements[i]->symbol() != list_p->_elements[i]->symbol() ) {
          Variable * v_p = dynamic_cast<Variable *>(_elements[i]);
          Variable * vv_p = dynamic_cast<Variable *>(list_p->_elements[i]);
          // cout << "is var!" << i;
          if( !v_p && !vv_p ) return false;
          if( (v_p && vv_p) || v_p ) v_p->match( *(list_p->_elements[i]) );
          else if( vv_p ) vv_p->match( *( _elements[i]) );
        } // if
      return true;
    }
    return false;
  }

private:
  vector<Term *> _elements;

};

#endif
