#ifndef UTVARIABLE_H
#define UTVARIABLE_H
#include "variable.h"
#include "number.h"
#include "atom.h"
#include "struct.h"
#include<iostream>
using namespace std;

// TEST( Varable, mem ) {
//   Variable X("X");
//   Variable Y("Y");
//   //X.match(Y);
//   Atom tom("tom");
//   X.match( tom );
//   cout << X.value();
//   cout << Y.value();
//   cout << X.mem_assignable();
//   cout << Y.mem_assignable();
// }
//
// TEST( Variable , Xassign ) {  // X = tom, X = Y  > Y = tom
//   Variable X("X");
//   Variable Y("Y");
//   Atom tom("tom");
//   X.match(tom);
//   X.match(Y);
//   cout << X.mem_assignable();
//   cout << X.value();
//   cout << Y.value();
//   cout << X.mem_assignable();
//   cout << Y.mem_assignable();
// }
//
// TEST( Variable , Yassign ){ // Y = tom, X = Y  > X = tom
//   Variable X("X");
//   Variable Y("Y");
//   Atom tom("tom");
//   Y.match(tom);
//   cout << X.mem_assignable();
//   cout << Y.mem_assignable();
//   X.match( Y );
//   cout << X.mem_assignable();
//   cout << "\n X value = " << X.value();
//   cout << "\n Y value = " << Y.value();
//   cout << X.mem_assignable();
//   cout << Y.mem_assignable();
// }
//
// TEST( Variable, allnotassign) {  // X = Y, Y = tom
//   Variable X("X");
//   Variable Y("Y");
//   Atom tom("tom");
//   //X.match( Y );
//   Y.match(X);
//   X.match( tom );
//   cout << "\n X value = " << X.value();
//   cout << "\n Y value = " << Y.value();
// }
//
// TEST( Variable, assign_lot) {  // X = Y, Y = Z, Z = tom, X = jj
//   Variable X("X");
//   Variable Y("Y");
//   Variable Z("Z");
//   Variable D("D");
//   Atom tom("tom");
//   Atom jj("jj");
//   //X.match( Y );
//   X.match(Y);
//   Y.match(Z);
//   Z.match(tom);
//   D.match(X);
//   cout << X.match( D );
//
//   cout << "\n X value = " << X.value();
//   cout << "\n Y value = " << Y.value();
//   cout << "\n D value = " << D.value();
// }
//
// TEST( Variable , str ){
//   Atom tom("tom");
//   Atom jerry("jerry");
//   Variable X("X");
//   Variable Y("Y");
//   X.match( tom );
//   Y.match( jerry );
//   std::vector< Term*> v = { &X, &Y };
//   Struct s( Atom("s"), v );
//   Variable T( "T" );
//   T.match( s );
//   cout << s.symbol();
//   cout << s.value();
//   cout << T.symbol();
//   cout << T.value();
//   std::vector<Term* > vv = { &s, &T };
//   Struct ss( Atom("SS"), vv );
//   cout << ss.symbol();
//   cout << ss.value();
//   Variable R("R");
//   R.match( ss );
//   cout << "\n" <<  R.symbol();
//   cout << R.value();
// }

// TEST(Variable, dddd) {
//   Variable X("X");
//   Variable Y("Y");
//   Number num(1);
//   X.match(Y);
//   cout << X.value();
//   cout << Y.value();
//   //Y.match(num);
//   Variable Z("Z");
//   Y.match(Z);
//   Y.match(num);
//   cout << X.value();
// }

// TEST(ATOm, matchvar){
//   Variable X("X");
//   Atom tom( "tom" );
//   ASSERT_TRUE(tom.match( X )); // tom = X
//   // Atom peter("peter");
//   // X.match( peter );
//   ASSERT_TRUE(X.match( tom ));
//   //cout << "\n" << tom.match(X);
// }
//
// TEST(ATOm, matchNum){
//   Number num1(3.555);
//   Number num2(3.5555);
//   Variable X("X");
//   X.match( num2 );
//   cout << num1.match( X );
// }

TEST( Variable, mathlooooot ){  // X = Y , Y = tom, W = Z, Y = Z
  Variable X("X");
  Variable Y("Y");
  Variable Z("Z");
  Variable W("W");
  Variable D("D");
  Variable K("K");
  Atom tom("tom");
  ASSERT_EQ( "X", X.value() );
  X.match(Y);
  ASSERT_EQ( "Y", X.value() );
  Y.match( tom );
  ASSERT_EQ( "tom", X.value() );
  W.match( Z );
  ASSERT_EQ( "Z", W.value() );
  Y.match(Z);
  ASSERT_EQ( "tom", X.value() );
  ASSERT_EQ( "tom", Y.value() );
  ASSERT_EQ( "tom", W.value() );
  ASSERT_EQ( "tom", Z.value() );
}

TEST(Variable , circular){  // X=Y, W=Z,Y= W, Y = tom
  Variable X("X");
  Variable Y("Y");
  Variable W("W");
  Variable Z("Z");
  Atom tom("tom");
  Y.match( tom );


}

// TEST( Stru, var ){
//   Variable X("X");
//   Variable Y("Y");
//   Variable D("D");
//   cout << X.value() << " " << Y.value() ;
//   std::vector<Term*> v = {&X, &Y};
//   Struct Stru( Atom("Str"), v );
//   cout << "Stru sym = " << Stru.symbol() << ", Stru value = " << Stru.value() << "\n";
//   Variable S("S");
//   S.match( Stru );
//   cout << "S sym = " << S.symbol() << ", S value = " << S.value() ;
//   Atom tom("tom");
//   X.match(tom);
//   cout << "X.value()  = " <<  X.value() << " ," << Y.value() << "\n" ;
//   cout << "S sym = " << S.symbol() << ", S value = " << S.value() ;
//   D.match( S );
//   cout << "D sym = " << D.symbol() << ", D value = " << D.value() ;
//   Y.match( tom );
//   cout << "D sym = " << D.symbol() << ", D value = " << D.value() ;
// }

//

// ?- X=Y, X=1.
// Y=1
TEST (Variable, varY_to_varX_and_num1_to_varX) {
  Variable X("X");
  Variable Y("Y");
  Number num(1);
  ASSERT_TRUE( X.match(Y) );
  ASSERT_TRUE( X.match(num));
  ASSERT_EQ( "1", Y.value() );
}
//
// ?- X=Y, Y=1.
// X=1
TEST (Variable, varY_to_varX_and_num1_to_varY) {
  Variable X("X");
  Variable Y("Y");
  Number num(1);
  ASSERT_TRUE( X.match(Y) );
  ASSERT_TRUE( Y.match( num ) );
  ASSERT_EQ( "1", X.value() );
}

// ?- X=X, X=1.
// X=1
TEST (Variable, varX_match_varX_and_num1_to_varX) {
  Variable X("X");
  Number num1(1);
  ASSERT_TRUE( X.match(X) );
  ASSERT_TRUE( X.match( num1 )) ;
  ASSERT_EQ( "1", X.value() );
  // cout << "X X is = " << X.value();
}

// ?- Y=1, X=Y.
// X=1
TEST (Variable, num1_to_varY_and_varX_match_varY) {
  Variable Y("Y");
  Number num(1);
  Variable X("X");
  ASSERT_TRUE( Y.match( num ) );
  ASSERT_TRUE( X.match( Y ) );
  ASSERT_EQ( "1", X.value() );
}

// ?- X=Y, Y=Z, Z=1
// X=1, Y=1, Z=1
TEST (Variable, num1_to_varZ_to_varY_to_varX) {
  Variable X("X");
  Variable Y("Y");
  Variable Z("Z");
  Number num(1);
  ASSERT_TRUE( X.match(Y) );
  ASSERT_TRUE( Y.match(Z) );
  ASSERT_TRUE( Z.match( num ) );
  ASSERT_EQ( "1", X.value() );
}

// ?- X=Y, X=Z, Z=1
// X=1, Y=1, Z=1
TEST (Variable, num1_to_varZ_to_varX_and_varY_to_varX) {
  Variable X("X");
  Variable Y("Y");
  Variable Z("Z");
  Number num1(1);
  ASSERT_TRUE( X.match(Y) );
  ASSERT_TRUE( X.match(Z) );
  ASSERT_TRUE( X.match(num1) );
  ASSERT_EQ( "1", X.value() );
  ASSERT_EQ( "1", Y.value() );
  ASSERT_EQ( "1", Z.value() );
}


// Give there is a Struct s contains Variable X
// And another Variable Y
// When Y matches Struct s
// Then #symbol() of Y should return "Y"
// And #value() of Y should return "s(X)"

TEST (Variable, Struct1) {
  Variable X("X");
  Variable Y("Y");
  std::vector<Term *> v = {&X};
 Struct s( Atom("s"), v );
  Y.match( s );
  ASSERT_EQ( "Y", Y.symbol());
  ASSERT_EQ( "s(X)", Y.value() );
}

// Give there is a Struct s contains Variable X
// And another Variable Y
// When Y matches Struct s
// And X matches Atom "teddy"
// Then #symbol() of Y should return "Y"
// And #value() of Y should return "s(teddy)"
TEST (Variable, Struct2) {
  Variable X( "X" );
  Variable Y( "Y" );
  Atom teddy("teddy");
  //X.match( teddy );
  std::vector<Term *> v = { &X };
  Struct s( Atom("s"), v );
  Y.match( s );      // Y = s(X)
  X.match( teddy );  // X= teddy
  ASSERT_EQ( "Y", Y.symbol() );
  ASSERT_EQ( "s(teddy)", Y.value() );
}

#endif
