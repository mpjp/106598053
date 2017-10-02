#ifndef UTTERM_H
#define UTTERM_H

//#include "term.h"
#include "atom.h"
#include "number.h"
#include "variable.h"
#include<iostream>
//using namespace std;
using std::string;
//test Number.value()
TEST (Number,ctor) {
  Number number( 50 );
  ASSERT_EQ( "50", number.value() );
}
//
// //test Number.symbol()
TEST (Number, symbol) {
  Number number("X");
  ASSERT_EQ( "X", number.symbol() );
}

//?- 25=25.
//true.
TEST (Number, matchSuccess) {
  Number numberA(25) ;
  Number numberB(25);
  ASSERT_TRUE( numberA.match( numberB ) );
}

//?- 25=0.
//false.
TEST (Number, matchFailureDiffValue) {
  Number numberA(25) ;
  Number numberB(0);
  ASSERT_FALSE( numberA.match( numberB ) );
}

//?- 25=tom.
//false.
TEST (Number, matchFailureDiffConstant) {
  Number numberA(25) ;
  Atom tom("tom");
  ASSERT_FALSE( numberA.match( tom ) );
}

//?- 25=X.
//true.
TEST (Number, matchSuccessToVar) {
  Number num(25);
  Variable var( "X" );
  ASSERT_TRUE( num.match(var) );
}

// ?- tom=25.
// false.
TEST (Atom, matchFailureDiffConstant) {
  Atom tom("tom");
  Number num(25);
  ASSERT_FALSE( tom.match(num) );
}

// ?- tom = X.
// X = tom.
TEST (Atom, matchSuccessToVar) {
  Atom tom("tom");
  Variable var("X");
  ASSERT_TRUE(tom.match( var ) );
  ASSERT_EQ( "tom", var.value() );
}

// ?- X=tom, tom=X.
// X = tom.
TEST (Atom, matchSuccessToVarInstantedToDiffConstant) {
  Variable var("X");
  Atom tom("tom");

  EXPECT_TRUE( var.match( tom ) );
  EXPECT_TRUE( tom.match( var ) );
  ASSERT_EQ( "tom", var.value() );

}

// ?- X=jerry, tom=X.
// false.
TEST (Atom, matchFailureToVarInstantedToDiffConstant) {
  Variable var("X");
  Atom jerry("jerry");
  Atom tom("tom");

  EXPECT_TRUE( var.match( jerry ));
  EXPECT_FALSE( tom.match( var ));
}

// ?- X = 5.
// X = 5.
TEST (Var, matchSuccessToNumber) {
  Variable var("X");
  Number num(5);
  EXPECT_TRUE( var.match( num ) );
  ASSERT_EQ( "5", var.value() ); // only string used
}

// ?- X=25, X= 100.
// false.
TEST (Var, matchFailureToTwoDiffNumbers) {
  Variable var("X");
  Number num25(25);
  Number num100(100);
  EXPECT_TRUE( var.match( num25 ) );
  EXPECT_FALSE( var.match( num100 ) );
}

// ?- X=tom, X= 25.
// false.
TEST (Var, matchSuccessToAtomThenFailureToNumber) {
  Variable var("X");
  Atom tom("tom");
  Number num25(25);
  EXPECT_TRUE( var.match(tom) );
  EXPECT_FALSE( var.match( num25 ) );
  // EXPECT_EQ( "", var.value() );
}
//?- tom=X, 25=X.
//false.
TEST (Var, matchSuccessToAtomThenFailureToNumber2) {
  Atom tom("tom");
  Variable var( "X" );
  Number num25( 25 ) ;
  EXPECT_TRUE( tom.match( var ) ) ;
  EXPECT_FALSE( num25.match( var ) ) ;
}
//?- X=tom, X=tom.
//true.
TEST(Var, reAssignTheSameAtom){
  Variable var("X");
  Atom tom("tom");
  EXPECT_TRUE( var.match( tom ) );
  EXPECT_TRUE( var.match(tom ) );
  //EXPECT_TRUE( tom.match( var ) );
}
#endif
