#ifndef NUMBER_H
#define NUMBER_H

#include "term.h"
#include<string>
#include<iostream>

using std::string;

class Number : public Term {
public:
  Number( double n ):_num( n ){}
  Number( string s ):_symbol(s){}

  //string value();
  string symbol() const {
    return std::to_string( _num );
  }
private:
  double _num;
  string _symbol;
};



#endif
