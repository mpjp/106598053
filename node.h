#ifndef NODE_H
#define NODE_H

enum Operators {SEMICOLON, COMMA, EQUALITY, TERM}; // 0123 ;,=Term

#include <string>
#include <vector>
using namespace std;

class Node {
public:
  Node(Operators op):payload(op), term(0), left(0), right(0) {}
  Node(Operators op, Term *t, Node *l, Node *r):payload(op), term(t), left(l), right(r) {}

  bool evaluate(){
    head = this;
    getAllnodes(head);
    return visitAllnodes();
  }

  void getAllnodes( Node* node ){
    if ( node == NULL ) return ;
    if ( node->left ) getAllnodes( node->left );
    allStatment.push_back( node );
    if( node->right ) getAllnodes( node->right );
  }

  void isStructFindVariableContentMatch( Struct* str, Variable* var ) {
    for( int i = 0; i < str->arity(); i++ ){
      Variable * isVarInStr = dynamic_cast<Variable *>(str->args(i));
      Struct * isStrInStr = dynamic_cast<Struct *>(str->args(i));
      if ( isVarInStr ){
        if ( isVarInStr->symbol() == var->symbol() )
          var->match( *isVarInStr );
      }
      if( isStrInStr ) isStructFindVariableContentMatch( isStrInStr, var );
    }
  } // isStructFindVariableContentMatch

  void matchStructContentBefore( Struct* str, int startPosition, int stopNode ){
    for( int i = 0; i < str->arity() ; i++ ){
      Variable * isVarInStr = dynamic_cast<Variable *>(str->args(i));
      Struct * isStrInStr = dynamic_cast<Struct *>(str->args(i));
      if ( isVarInStr ) MatchBefore( isVarInStr, startPosition, stopNode );
      if ( isStrInStr ) matchStructContentBefore( isStrInStr, startPosition, stopNode );
    } // for
  } // matchStructContentBefore()

  bool MatchBefore( Variable* var, int startPosition, int stopNode ){
    for( int i = startPosition; i < stopNode; i++ ){
      if( allStatment[i]->payload == TERM ){
        if( allStatment[i]->term->symbol() == var->symbol() ) {
          if( !var->match( *(allStatment[i]->term) ) ) return false;
        }
        else {
          Struct * isStr = dynamic_cast<Struct *>(allStatment[i]->term);
          if( isStr )
            isStructFindVariableContentMatch( isStr, var );
        } // else
      } // if is term
    } // for
    return true;
  } // MatchBefore()


  bool isVarOrStructThenMatchBefore( Node* node, int startPosition, int stopNode ) {
    Variable * isVar_left = dynamic_cast<Variable *>(node->left->term);
    if ( isVar_left )
      if(!MatchBefore( isVar_left, startPosition, stopNode )) return false;
    Variable * isVar_right = dynamic_cast<Variable *>(node->right->term);
    if ( isVar_right )
      if(!MatchBefore( isVar_right, startPosition, stopNode )) return false;

    Struct * isStr_left = dynamic_cast<Struct *>(node->left->term);
    Struct * isStr_right = dynamic_cast<Struct *>(node->right->term);
    if ( isStr_left ) matchStructContentBefore( isStr_left, startPosition, stopNode );
    if ( isStr_right ) matchStructContentBefore( isStr_right, startPosition,stopNode );
    return true;
  } // isVarOrStructThenMatchBefore()

  bool matchNode( Node *node ) {
    Term* leftnode = node->left->term;
    Term* rightnode = node->right->term;
    if( !leftnode->match( *rightnode ) ) return false ;
    return true;
  }

  bool visitAllnodes() {
    Operators followOp  = TERM;
    int startPosition = 0;
    for( int i = 0; i < allStatment.size(); i++ ) {
      if ( allStatment[i]->payload == EQUALITY ) {
         if( followOp == COMMA ) isVarOrStructThenMatchBefore( allStatment[i], startPosition, i-1 );
         if( !matchNode( allStatment[i] ) ) return false ;
      } // if
      else if( allStatment[i]->payload != TERM ) {
        if ( allStatment[i]->payload == SEMICOLON ) startPosition = i+1;
        followOp = allStatment[i]->payload;
      }
    } // for

    return true;
  }


  Operators payload;
  vector<Node*> allStatment;
  Term* term;
  Node *left, *right;
  Node* head, *temp;
};

#endif
