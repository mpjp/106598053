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

class Variable;
class Member{
public:
  Member(string s): memValue(new string(s)) {
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
    *memValue = s;
  }
  void addVariable( Variable* vp ){
    mem_v.push_back( vp );
  }
  void removeVariable(){
    while (!mem_v.empty())
     mem_v.pop_back();
  }
  string getmemValue(){
    return *memValue;
  }
  string *memValue = new string;
  std::vector<Variable*> mem_v;

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
        if( var_p->mem_ptr->varassignbefore && mem_ptr->varassignbefore ){

          if( check_var_var_assign_before( var_p->mem_ptr ) ) return true;
          int size = (mem_ptr->mem_v).size();  //X , Y
          //cout << "size = " << size;

          std::vector<Variable*> temp_v = mem_ptr->mem_v; // you Z,W
          for(vector<Variable*>::iterator iter = temp_v.begin(); iter != temp_v.end()-1; ++iter){
            // cout << (*iter)->symbol() << "addr = " << (*iter)->mem_ptr ;
            var_p->mem_ptr->addVariable( *iter );
            (*iter)->mem_ptr = var_p->mem_ptr;
          }
          // //cout << "\n value = " << var_p->mem_ptr->memValue << "\n";


        }  // if all assign Variable before
        //******************************************

        if( var_p->mem_ptr->varassignbefore ) {
          point_new_address_myself( var_p );
        }
        else { // X=Y
          mem_ptr->varassignbefore = true;
          mem_setmemValue( var_p->value() ); //->symbol()  important
          point_new_address( var_p );
          //***
          mem_ptr->addVariable( this ); // X = Y
          mem_ptr->addVariable( var_p );

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

  bool check_var_var_assign_before( Member* mp ) {
    int size = mp->mem_v.size();
    for( int i =0; i <size; i++ ){
      Variable *temp = mp->mem_v[i];
      if( temp == this ) {
        // cout << "find!";
        return true; // already at same address
      } // if
    } // for
    return false;
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
    return mem_ptr->getmemValue();
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
