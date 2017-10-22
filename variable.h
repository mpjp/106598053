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
  Member(string s, Term* tptr ): memValue(new string(s)), _tptr(tptr) {}
  ~Member(){}

  void setmemValue( Term *tp ){
    _tptr = tp;
  }

  Term* gerTermptr(){
    return _tptr;
  }

  void addVariable( Variable* vp ){
    mem_v.push_back( vp );
  }

  string getmemValue(){
    return _tptr->value();
  }

  string *memValue = new string;
  std::vector<Variable*> mem_v;
  Term *_tptr ;

};

class Variable : public Term{
public:
  Variable(string s):_symbol(s){
    assignable = true;
    varassignbefore = false;
    mem_ptr->addVariable( this );
  }

  string const _symbol;
  Member *mem_ptr = new Member( _symbol, this );

  bool match( Term &term ) {

    Variable * var_p = dynamic_cast<Variable *>(&term);

    if( var_p ){ // is var
      if( !getassignable() && !var_p->getassignable() ) { // all assign before
        if( value() == var_p->value() ) return true;
        return false;
      }
      else if( getassignable() == false ) {  // X already assign, var point to myself
        get_all_pointer_change( var_p->mem_ptr->mem_v, this, true );
        //var_p->mem_ptr = mem_ptr;
        //var_p->setassignableFalse();
      }
      else if( var_p->getassignable() == false ) { // myself point to var address
        //mem_ptr = var_p->mem_ptr;
        get_all_pointer_change( mem_ptr->mem_v, var_p , true );
        //setassignableFalse();
      }
      else {  // all not assign before

        if( var_p->getvarassignbefore() && getvarassignbefore() ){
          if( check_var_var_assign_before( var_p->mem_ptr ) ) return true;
          int size = (mem_ptr->mem_v).size();  //X , Y
          get_all_pointer_change( mem_ptr->mem_v, var_p, false );

          // std::vector<Variable*> temp_v = mem_ptr->mem_v; // you Z,W
          // for(vector<Variable*>::iterator iter = temp_v.begin(); iter != temp_v.end(); ++iter){
          //   cout << (*iter)->symbol() << ", addr = " << (*iter)->mem_ptr << " " ;
          //   var_p->mem_ptr->addVariable( *iter );
          //   (*iter)->mem_ptr = var_p->mem_ptr;
          //   //(*iter)->mem_ptr->setmemValue( var_p->mem_ptr->gerTermptr() );
          // }
          // //cout << "\n value = " << var_p->mem_ptr->memValue << "\n";


        }  // if all assign Variable before
        //******************************************

        else if( getvarassignbefore() ){
          var_p->mem_ptr = mem_ptr;
          var_p->mem_ptr->setmemValue( var_p );
          var_p->varassignbefore = true;
          mem_ptr->addVariable( var_p );
        }
        else {
          //if( !var_p->varassignbefore ) var_p->mem_ptr->addVariable( this );
          mem_ptr = var_p->mem_ptr;
          var_p->varassignbefore = true;
          varassignbefore = true;
          var_p->mem_ptr->addVariable( this );
        }


        // if( var_p->mem_ptr->varassignbefore ) {
        //   mem_ptr->setmemValue( var_p );
        //   //point_new_address_myself( var_p );
        // }
        // else { // X=Y
        //   mem_ptr->varassignbefore = true;
        //   //mem_setmemValue( var_p ); //->symbol()  important //var_p->value()
        //   mem_ptr->setmemValue( var_p );
        //   //point_new_address( var_p );
        //   //***
        //   mem_ptr->addVariable( this ); // X = Y
        //   mem_ptr->addVariable( var_p );
        //
        // }
      }
      // return true;
    }
    else { // atom , num, struct
      if( getassignable() == false ) {
        if( value() != term.value() ) return false;
      }
      mem_ptr->setmemValue( &term );
      setassignableFalse();
    } // else

    return true;
  }


  void get_all_pointer_change( vector<Variable*> vp, Variable* var_p, bool setassignableFalse ){
    std::vector<Variable*> temp_v = vp; // you Z,W
    for(vector<Variable*>::iterator iter = temp_v.begin(); iter != temp_v.end(); ++iter){
      var_p->mem_ptr->addVariable( *iter );
      (*iter)->mem_ptr = var_p->mem_ptr;
      if( setassignableFalse ) (*iter)->setassignableFalse();
    } // for
  }

  bool check_var_var_assign_before( Member* mp ) {
    int size = mp->mem_v.size();
    for( int i =0; i <size; i++ ){
      Variable *temp = mp->mem_v[i];
      if( temp == this )  return true;
    } // for
    return false;
  }

  string symbol() const{
    return _symbol;
  }

  string value() const {
    Term *tp = mem_ptr->gerTermptr();
    Variable * vp = dynamic_cast<Variable *>(tp);
    if( vp ){ return vp->symbol(); }
    return tp->value();
  }

  void setassignableFalse(){
    assignable = false;
  }

  bool getassignable(){
    return assignable;
  }

  bool getvarassignbefore(){
    return varassignbefore;
  }

private:
  string _value;
  bool assignable; //
  bool varassignbefore; //
};

#endif
