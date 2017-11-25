#ifndef PARSER_H
#define PARSER_H
#include <string>
using std::string;

#include "atom.h"
#include "variable.h"
#include "global.h"
#include "scanner.h"
#include "struct.h"
#include "number.h"
#include "list.h"
#include "node.h"

#include<iostream>
using namespace std;
class Parser{
public:
  Parser(Scanner scanner) : _scanner(scanner), _terms(){}

  Term* createTerm(){
    int token = _scanner.nextToken();
    _currentToken = token;
    if(token == VAR){
      return new Variable(symtable[_scanner.tokenValue()].first);
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
  }

  Node* expressionTree(){
    return head;
  }

  void matchings(){
    Term* term = createTerm();
    if(term!=nullptr)
    {
      _terms.push_back(term);
      _currentToken = _scanner.nextToken();
      while( _currentToken == '=' || _currentToken == ',' || _currentToken == ';' ) {
       sym.push_back( _currentToken );
        _terms.push_back(createTerm());
        _currentToken = _scanner.nextToken();
      }
      if( _currentToken != 258 )
        throw string("unexpected token");
      else buildTree();
    }
  }

  void nodeChange( Node* a, Node* b ){
    Operators oop = a->payload;
    a->payload = b->payload;
    b->payload = oop;
  }

  Node *head ;
  void buildTree() {
    Node *node, *temp;
    for( int i = 0; i < sym.size(); i++ ) {
      node = new Node( getEnum(sym[i]) );
      if( i == 0 ) head = temp = node;
      else {
        if( temp->left == NULL ) temp->left = node;
        else temp->right = node;

        if( (node->payload < temp->payload) && (temp->payload == EQUALITY) )
          nodeChange( node, temp );
        else temp = node;
      } // else
    } // for
    temp = head;
    getAllLeaf( temp );
    putTermsToTree();
  } // buildTree()

void getAllLeaf( Node* root ){
  if( root == NULL ) return ;
  if( root->left == NULL  & root->right == NULL){
    nodevec.push_back( root );
    return ;
  }
  if( root-> left ) getAllLeaf( root->left );
  if( root->right ) getAllLeaf( root->right );
}

void putTermsToTree(){
  int node_it, i = 0;
  for( int i = 0; i < _terms.size() ; i++ ){
    node_it = i;
    if( nodevec[node_it/2]->left == NULL ) nodevec[node_it/2]->left = createTermNode( _terms[i] );  //
    else if ( nodevec[node_it/2]->right == NULL ) nodevec[node_it/2]->right = createTermNode( _terms[i]  );
  } // for
}

Node* createTermNode( Term* ter ){
  Node* node = new Node( TERM, ter, NULL, NULL );
  return node;
}

Operators getEnum( int num ){
  if( num == ',' ) return COMMA;
  else if( num == '=') return EQUALITY;
  else if( num == ';' ) return SEMICOLON;
  return TERM;
}

void printSym(){
  for( int i = 0; i < sym.size(); i++ )
    cout << sym[i] << " ";
}


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
      throw string("unexpected token");
    }
  }

  Term * list() {
    int startIndexOfListArgs = _terms.size();
    createTerms();
    if(_currentToken == ']')
    {
      vector<Term *> args(_terms.begin() + startIndexOfListArgs, _terms.end());
      _terms.erase(_terms.begin() + startIndexOfListArgs, _terms.end());
      return new List(args);
    } else {
      throw string("unexpected token");
    }
  }

  vector<Term *> & getTerms() {
    return _terms;
  }



private:
  FRIEND_TEST(ParserTest, createArgs);
  FRIEND_TEST(ParserTest,ListOfTermsEmpty);
  FRIEND_TEST(ParserTest,listofTermsTwoNumber);
  FRIEND_TEST(ParserTest, createTerm_nestedStruct3);

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
  vector<int> sym;
  vector<Node*> nodevec;
  Scanner _scanner;
  int _currentToken;
};
#endif
