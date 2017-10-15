#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include "atom.h"
#include "term.h"
#include "number.h"
#include "struct.h"
using std::string;

#include<iostream>
using namespace std;

class Member{
public:
  Member(string s ): memValue(s) {
    assignable = true;
    varassignbefore = false;
  }
  ~Member(){}
  void setassignableFalse() {
    assignable = false;
  }
  bool getassignable(){
    return assignable;
  }
  void setmemValue( string s ){
    memValue = s;
  }
  string memValue;
  bool assignable;
  bool varassignbefore;
};

class Variable : public Term{
public:
  Variable(string s):_symbol(s){}

  string const _symbol;
  Member *mem_ptr = new Member( _symbol );

  bool match( Term &term ) {

    Variable * var_p = dynamic_cast<Variable *>(&term);

    if( var_p ){ // is var
      if( !mem_assignable() && !var_p->mem_assignable() ) { // all assign before
        if( value() == var_p->value() ) return true;
        return false;
      }
      else if( mem_assignable() == false ) {  // X already assign
        point_new_address( var_p ); // var point to myself
        var_p->mem_setassignableFalse();
      }
      else if( var_p->mem_assignable() == false ) {
        point_new_address_myself( var_p );  // myself point to var address
      }
      else {  // all not assign before
        if( var_p->mem_ptr->varassignbefore ) {
          point_new_address_myself( var_p );
        }
        else {
          mem_ptr->varassignbefore = true;
          mem_setmemValue( var_p->value() ); //->symbol()
          point_new_address( var_p );
        }
      }
      // return true;
    }
    else { // atom , num, struct
      if( mem_assignable() == false ) {
        if( value() != term.value() ) return false;
      }
      // Struct * stru_p = dynamic_cast<Struct *>(&term);
      mem_setmemValue( term.value() );
      mem_setassignableFalse();
    }
    return true;
  }

  void point_new_address( Variable * var_p ){
    Member *temp = var_p->mem_ptr;
    var_p->mem_ptr = mem_ptr;
    //
    if( symbol() != var_p->symbol() ) delete temp;
  }

  void point_new_address_myself( Variable * var_p ){
    Member *temp = mem_ptr;
    mem_ptr = var_p->mem_ptr;
    if( symbol() != var_p->symbol() ) delete temp;
  }

  string symbol() const{
    return _symbol;
  }

  string value() const {
    return mem_ptr->memValue;
  }

  bool mem_assignable(){
    return mem_ptr->getassignable();
  }

  void mem_setmemValue( string s ) {
    mem_ptr->setmemValue( s );
  }

  void mem_setassignableFalse(){
    mem_ptr->setassignableFalse();
  }

private:
  string _value;
};

#endif
