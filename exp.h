#ifndef EXP_H
#define EXP_H

#include "atom.h"



#include <string>
#include <iostream>
#include <deque>

using namespace std;

class Exp {
public:
  virtual bool evaluate() = 0;
  virtual string result(){}
};

deque<string> resultString;

void printResult() {
  cout << "SIZE = " << resultString.size();
  for( int i = 0; i < resultString.size(); i++ )
    cout << resultString[i];
}

string showResult( Exp *e ){
  string result = "";
  if( !e->evaluate() ) result = "false.";
  else {
    result = e->result();
    if ( result == "" ) result = "true.";
    else result += ".";
  }
  return result;
}

class MatchExp : public Exp {
public:
  MatchExp(Term* left, Term* right): _left(left), _right(right){
  }

  bool evaluate(){
    //cout << _left->symbol() + " = " + _right->symbol() << &*_left << " " << &*_right <<  "$\n";
    return _left->match(*_right);
  }

  string result(){

    string res = "";
    if ( _left->symbol() == _right->symbol() ) return "";

    Variable* isLeftVar = dynamic_cast<Variable*>(_left);
    Variable* isRighttVar = dynamic_cast<Variable*>(_right);

    if ( isLeftVar && isRighttVar ) {
      return _left->symbol() + " = " + _right->symbol();
    }
    if( isLeftVar ) {
      return _left->symbol() + " = " + _left->value();
    }
    if( isRighttVar ) {
      return _right->symbol() + " = " + _right->value();
    }

    return _left->symbol() + " = " + _right->symbol();
  }

public:

  Term* _left;
  Term* _right;
};

class ConjExp : public Exp {
public:
  ConjExp(Exp *left, Exp *right) : _left(left), _right(right) {

  }

  bool evaluate( ) {

    bool _leVal = _left->evaluate();
    bool _riVal = _right->evaluate();
    _boolEva = _leVal && _riVal;

    return _leVal && _riVal;
  }


  string result(){
   string res = "";

   res += _left->result();
   // cout << _left->result();
   // cout << " , ";
   if ( _left->result() != _right->result() ) {
     if ( _left->result() == "" ) res += _right->result();
     else if ( _right->result() != "" ) res += ", " + _right->result();
   }

   return res;
  }

private:
  bool _boolEva;
  Exp * _left;
  Exp * _right;
};

class DisjExp : public Exp {
public:
  DisjExp(Exp *left, Exp *right) : _left(left), _right(right) {

  }

  bool evaluate() {
    //cout << "(DisVar!)";
    _leftEval = _left->evaluate();
    _rightEval = _right->evaluate();
    return _leftEval || _rightEval ;
  }

  string result(){
   string res = "";
   //cout << "DisRESULT\n" ;

   if ( _leftEval ) res += _left->result();
   if ( _rightEval && (_left->result() !=_right->result()) ) {
    // if ( _right->result() == "" ) res += _right->result();
    if ( _right->result() == "" ) res += "; true";
    else {
      if ( !_leftEval) res += _right->result();
      else res += "; " + _right->result();
    } //if
   }

   // if ( _leftEval ) cout << _left->result();
   // if ( _rightEval && (_left->result() !=_right->result()) ) cout << " ; " + _right->result();


   return res;
  }

private:
  bool _leftEval ;
  bool _rightEval ;
  Exp * _left;
  Exp * _right;
};
#endif
