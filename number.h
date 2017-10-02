#ifndef NUMBER_H
#define NUMBER_H

#include<string>

using std::string;

class Atom;
class Variable;
class Number{
  public :
    Number( int n ):_num( n ){}
    Number( string s ):_symbol(s){}

    string value();
    //int value();
    //string AAvalue();
    string symbol();
    bool match( Number& );
    bool match( Atom& );
    bool match( Variable& );

  private:
    int _num;
    string _symbol;
};

#endif
