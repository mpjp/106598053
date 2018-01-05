#ifndef PARSER_H
#define PARSER_H
#include <string>
using std::string;

#include "atom.h"
#include "variable.h"
#include "global.h"
#include "scanner.h"
#include "struct.h"
#include "list.h"
#include "exp.h"
#include <stack>

using std::stack;

using namespace std;

class Parser{
public:
  Parser(Scanner scanner) : _scanner(scanner), _terms() {}

  Term* createTerm(){
    int token = _scanner.nextToken();
    _currentToken = token;
    if(token == VAR){
      Variable *var = new Variable(symtable[_scanner.tokenValue()].first);
      if(!findSameVariable( var )) _allVariable.push_back( var );
      else {
        delete var;
        return actualVarPointer;
      }
      return var;
    }else if(token == NUMBER){
      return new Number(_scanner.tokenValue());
    }else if(token == ATOM || token == ATOMSC){
      Atom* atom = new Atom(symtable[_scanner.tokenValue()].first);
      if(_scanner.currentChar() == '(' ) {
        return structure();
      }
      else
        return atom;
    }

    else if(token == '['){
      return list();
    }

    return nullptr;

  } // createTerm()


  Term * structure() {
    Atom structName = Atom(symtable[_scanner.tokenValue()].first);
    int startIndexOfStructArgs = _terms.size();
    _scanner.nextToken();
    createTerms();
    if(_currentToken == ')')
    {
      vector<Term *> args(_terms.begin() + startIndexOfStructArgs, _terms.end());
      _terms.erase(_terms.begin() + startIndexOfStructArgs, _terms.end());
      return new Struct(structName, args);
    } else {
      throw string("Unbalanced operator");
    }
  }

  Term * list() {
    int startIndexOfListArgs = _terms.size();
    createTerms();
    if(_currentToken == ']')
    {
      vector<Term *> args(_terms.begin() + startIndexOfListArgs, _terms.end());
      _terms.erase(_terms.begin() + startIndexOfListArgs, _terms.end());
      if(args.size()==0){
        return new Atom("[]");
      }
      return new List(args);
    } else {
      throw string("Unbalanced operator");
    }
  } // list()

  // void matchVarInListOrStruct( vector<Term*> args ){
  //   for( std::vector<Term*>::iterator it = args.begin() ; it != args.end(); ++it )
  //     cout << (*it)->symbol() << "in list = " << *it;
  //     //findSameVariable( *it );
  // }

  bool findSameVariable( Term* var ) {
    for( std::vector<Term*>::iterator it = _allVariable.begin() ; it != _allVariable.end(); ++it ){
      if( var->symbol() == (*it)->symbol() ) {
        var = *it;
        actualVarPointer = *it;
        return true;
      }
    }
    return false;
  } // bool


  vector<Term *> & getTerms() {
    return _terms;
  }

  void buildExpression(){
    // createTerm();
    disjunctionMatch();
    restDisjunctionMatch();

    if (createTerm() != nullptr || _currentToken != '.')
      throw string("Missing token '.'");
  }

  void restDisjunctionMatch() {
    if (_scanner.currentChar() == ';') {

      //cout << "clear!";
      _allVariable.clear();

      createTerm();
      disjunctionMatch();
      Exp *right = _expStack.top();
      _expStack.pop();
      Exp *left = _expStack.top();
      _expStack.pop();
      _expStack.push(new DisjExp(left, right));
      restDisjunctionMatch();
    }
  }

  void disjunctionMatch() {
    conjunctionMatch();
    restConjunctionMatch();
  }

  void restConjunctionMatch() {
    if (_scanner.currentChar() == ',') {
      createTerm();
      if( _scanner.currentChar() == '.') throw string( "Unexpected ',' before '.'" );
      conjunctionMatch();
      Exp *right = _expStack.top();
      _expStack.pop();
      Exp *left = _expStack.top();
      _expStack.pop();
      _expStack.push(new ConjExp(left, right));
      restConjunctionMatch();
    }
  }

  void conjunctionMatch() {
    Term * left = createTerm();

    Term *temp = createTerm();
    int _currtemp = _currentToken;
    if (temp == nullptr && _currentToken == '=') {

      Term * right = createTerm();
      MatchExp *matchExp = new MatchExp(left, right);

      _expStack.push( matchExp );
    }
    else {
      if ( _currtemp == '='|| _currtemp == '.') {
        if( left == nullptr ) throw string(" does never get assignment");
        else throw string( left->symbol() + " does never get assignment");
      }
      // else if ( pp == nullptr ) cout << "@@";
      else {
        char ww = static_cast<char>(_currtemp);
        std::string str(1, ww);
        throw string( "Unexpected '" + str + "' before '.'" );
      }
    }
  }

  Exp* getExpressionTree(){
    return _expStack.top();
  }



public:
  // FRIEND_TEST(ParserTest, createArgs);
  // FRIEND_TEST(ParserTest,ListOfTermsEmpty);
  // FRIEND_TEST(ParserTest,listofTermsTwoNumber);
  // FRIEND_TEST(ParserTest, createTerm_nestedStruct3);
  // FRIEND_TEST(ParserTest, createTerms);

  void createTerms() {
    Term* term = createTerm();
    if(term!=nullptr)
    {
      _terms.push_back(term);
      while((_currentToken = _scanner.nextToken()) == ',') {
        _terms.push_back(createTerm());
      }
    }
  }

  vector<Term *> _terms;
  vector<Term*> _allVariable;
  Scanner _scanner;
  int _currentToken;
  stack<Exp*> _expStack;
  Term* actualVarPointer ;
};
#endif
