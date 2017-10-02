#ifndef UTATOM_H
#define UTATOM_H
#include "atom.h"

TEST( Atom, num ){
  Atom tom("tom");
  //Numbr num(10);
  //tom.match( num );
}

TEST(Atom, first) {
  ASSERT_TRUE(true);
}

TEST(Atom, tom) {
  Atom tom("tom");
  ASSERT_EQ("tom", tom._symbol);
}

// ?- tom = tom, tom = jr.
// false.
TEST(Atom, match_tom_and_jerry) {
  Atom tom("tom");
  Atom jerry("jerry");
  //EXPECT_FALSE(tom == jerry);
  //EXPECT_TRUE(tom == tom);

  EXPECT_FALSE( tom.match( jerry ) );
  EXPECT_TRUE( tom.match(tom) ) ;
}

#endif
