#ifndef UTLIST_H
#define UTLIST_H
#include <vector>
#include <string>
using std::string;

#include "list.h"
#include "struct.h"
#include "atom.h"
#include "number.h"
#include "variable.h"
#include <stdexcept>
#include<iostream>
using namespace std;

// When create a new list without any item
// Then #symbol() of the list should return "[]"
TEST (List, constructor) {
  vector<Term *> args = {};
  List list(args);
  EXPECT_EQ( "[]", list.symbol() );
}

// Given there are two perfect numbers: 8128
// When create a new list with the perfect Number
// Then #symbol() of the list should return "[8128]"
TEST(List, Numbers) {
 Number num(8128);
 vector<Term *> args = {&num};
 List l(args);
 EXPECT_EQ( "[8128]", l.symbol() );
}

// Given there are two atoms: "terence_tao", "alan_mathison_turing"
// When create a new list with the Atoms
// Then #symbol() of the list should return "[terence_tao, alan_mathison_turing]"
TEST(List, Atoms) {
  Atom terence_tao("terence_tao");
  Atom alan_mathison_turing("alan_mathison_turing");
  std::vector<Term*> v = { &terence_tao, &alan_mathison_turing};
  List l( v );
  EXPECT_EQ( "[terence_tao, alan_mathison_turing]", l.symbol() );
}

// Given there are two variables: X, Y
// When create a new list with the variables
// Then #symbol() of the list should return "[X, Y]"
TEST(List, Vars) {
  Variable X("X");
  Variable Y("Y");
  std::vector<Term*> v = {&X,&Y};
  List l( v );
  EXPECT_EQ( "[X, Y]", l.symbol() );
}

// ?- tom = [496, X, terence_tao].
// false.
TEST(List, matchToAtomShouldFail) {
  Atom tom("tom");
  Number num(496);
  Variable X("X");
  Atom t("terence_tao");
  std::vector<Term*> v = {&num,&X,&t};
  List list(v);
  ASSERT_FALSE( tom.match( list ));
}

// ?- 8128 = [496, X, terence_tao].
// false.
TEST(List, matchToNumberShouldFail) {
  Number num8128(8128);
  Number num(496);
  Variable X("X");
  Atom t("terence_tao");
  std::vector<Term*> v = {&num,&X,&t};
  List list(v);
  ASSERT_FALSE( num8128.match( list ));
}

// ?- s(X) = [496, X, terence_tao].
// false.
TEST(List, matchToStructShouldFail) {
  Variable X("X");
  std::vector<Term*> v = {&X};
  Struct s(Atom("s"), v );

  Number num(496);
  Atom t("terence_tao");
  std::vector<Term*> vv = {&num,&X,&t};
  List list(vv);

  ASSERT_FALSE( list.match(s) );
}

// ?- Y = [496, X, terence_tao].
// Y = [496, X, terence_tao].
TEST(List, matchToVarShouldSucceed) {
  Variable Y("Y");
  Variable X("X");
  Number num(496);
  Atom t("terence_tao");
  std::vector<Term*> vv = {&num,&X,&t};
  List list(vv);
  ASSERT_TRUE( list.match(Y) );
}

// ?- X = [496, X, terence_tao].
// false.
TEST(List, matchToVarOccuredInListShouldFail) {
  Variable X("X");
  Number num(496);
  Atom t("terence_tao");
  std::vector<Term*> vv = {&num,&X,&t};
  List list(vv);
  ASSERT_FALSE( list.match(X) );
}

// ?- [496, X, terence_tao] = [496, X, terence_tao].
// true.
TEST(List, matchToSameListShouldSucceed) {
  Variable X("X");
  Number num(496);
  Atom t("terence_tao");
  std::vector<Term*> vv = {&num,&X,&t};
  List list(vv);
  List list2(vv);
  ASSERT_TRUE( list.match( list2 ) );
}

// ?- [496, X, terence_tao] = [496, Y, terence_tao].
// true.
TEST(List, matchToSameListWithDiffVarNameShouldSucceed) {
  Variable X("X");
  Variable Y("Y");
  Number num(496);
  Atom t("terence_tao");
  std::vector<Term*> v = {&num,&X,&t};
  List list( v );
  std::vector<Term*> vv = {&num,&Y,&t};
  List list2( vv );
  ASSERT_TRUE( list.match( list2 ) );
}

// ?- [496, X, terence_tao] = [496, 8128, terence_tao].
// X = 8128.
TEST(List, matchToVarToAtominListShouldSucceed) {
  Variable X("X");
  Number num(496);
  Number num8128( 8128 );
  Atom t("terence_tao");
  std::vector<Term*> v = {&num,&X,&t};
  List list( v );
  std::vector<Term*> vv = {&num,&num8128,&t};
  List list2( vv );
  ASSERT_TRUE( list.match( list2 ) );
}

// ?- Y = [496, X, terence_tao], X = alan_mathison_turing.
// Y = [496, alan_mathison_turing, terence_tao],
// X = alan_mathison_turing.
TEST(List, matchVarinListToAtomShouldSucceed) {
  Variable X("X");
  Variable Y("Y");
  Number num(496);
  Atom t("terence_tao");
  std::vector<Term*> v = {&num,&X,&t};
  List list( v );
  Y.match( list );
  Atom alan( "alan_mathison_turing" );
  X.match( alan );
  EXPECT_EQ( "[496, alan_mathison_turing, terence_tao]", Y.value() );
  EXPECT_EQ( "alan_mathison_turing", X.value() );
}

// Example:
// ?- [first, second, third] = [H|T].
// H = first, T = [second, third].
TEST(List, headAndTailMatching1) {
  Atom f("first"), s("second"), t("third");
  vector<Term *> args = {&f, &s, &t};
  List l(args);
  // // cout << l.head()->symbol();
  // cout << l.head()->symbol();
  // cout << l.tail()->head()->value();
  // cout << l.tail()->head()->value();
  EXPECT_EQ(string("first"), l.head()->symbol());
  EXPECT_EQ(string("[second, third]"), l.tail()->value());
}

// Example:
// ?- [first, second, third] = [first, H|T].
// H = second, T = [third].
TEST(List, headAndTailMatching2) {
  Atom f("first"), s("second"), t("third");
  vector<Term *> args = {&f, &s, &t};
  List l(args);
  EXPECT_EQ(string("second"), l.tail()->head()->value());
  EXPECT_EQ(string("[third]"), l.tail()->tail()->value());
}

// ?- [[first], second, third] = [H|T].
// H = [first], T = [second, third].
// --------------------------------------------------
TEST(List, headAndTailMatching3) {
  Atom first("first");
  std::vector<Term* > args = {&first};
  List l(args);

  Atom s("second");
  Atom t("third");
  std::vector<Term*> v = {&l ,&s, &t };
  List list( v );
  EXPECT_EQ( "[first]" , list.head()->value() );
  EXPECT_EQ( "[second, third]", list.tail()->value() );

}

// ?- [first, second, third] = [first, second, H|T].
// H = third, T = [].
TEST(List, headAndTailMatching4) {
  Atom f("first");
  Atom s("second");
  Atom t("third");
  std::vector<Term*> v = {&f, &s,&t};
  List list( v );
  EXPECT_EQ( "third", list.tail()->tail()->head()->value() ) ;
  EXPECT_EQ( "[]",  list.tail()->tail()->tail()->value() );

}

// Given there is a empty list
// When client still want to get the head of list
// Then it should throw a string: "Accessing head in an empty list" as an exception.
TEST (List, emptyExecptionOfHead) {

  try {
    std::vector<Term*> v = {};
    List list( v );
    list.head();
  }
  catch(std::out_of_range const & err) {
      EXPECT_EQ(err.what(),std::string("Accessing head in an empty list"));
  }
  // catch(const & err) {
  //   EXPECT_EQ(err.what(), std::string("Accessing head in an empty list"));
  // }

}

// Given there is a empty list
// When client still want to get the head of list
// Then it should throw a string: "Accessing tail in an empty list" as an exception.
TEST (List, emptyExecptionOfTail) {
  try {
    std::vector<Term*> v = {};
    List list( v );
    list.tail();
  }
  catch(std::out_of_range const & err) {
      EXPECT_EQ(err.what(),std::string("Accessing tail in an empty list"));
  }
  // catch(...) {
  // }
}




#endif
