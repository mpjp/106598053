#ifndef UTITERATOR_H
#define UTITERATOR_H

#include "struct.h"
#include "variable.h"
#include "atom.h"
#include "list.h"
#include "iterator.h"
#include "number.h"

TEST(iterator, first) {
    Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    Struct t(Atom("t"), { &X, &two });
    Struct s(Atom("s"), { &one, &t, &Y });
    // StructIterator it(&s);
    Iterator<Term*> *itStruct = s.createIterator();
    // Iterator& itStruct = it;
    // ASSERT_EQ(it.first()->symbol());
    itStruct->first();
    ASSERT_EQ("1", itStruct->currentItem()->symbol());
    ASSERT_FALSE(itStruct->isDone());
    itStruct->next();
    ASSERT_EQ("t(X, 2)", itStruct->currentItem()->symbol());
    ASSERT_FALSE(itStruct->isDone());
    itStruct->next();
    ASSERT_EQ("Y", itStruct->currentItem()->symbol());
    itStruct->next();
    ASSERT_TRUE(itStruct->isDone());
}

TEST(iterator, nested_iterator) {
  Number one(1);
  Variable X("X");
  Variable Y("Y");
  Number two(2);
  Struct t(Atom("t"), { &X, &two });  //t(X, 2)
  Struct s(Atom("s"), { &one, &t, &Y }); // s( 1, t(X, 2), Y)

  Iterator<Term*> *it = s.createIterator();
  it->first();
  ASSERT_EQ( "1", it->currentItem()->symbol() );
  it->next();
  ASSERT_EQ( "t(X, 2)", it->currentItem()->symbol() );

  Struct *s2 = dynamic_cast<Struct *>(it->currentItem());
  Iterator<Term*>* it2 = s2->createIterator();
  it2->first();
  ASSERT_EQ( "X", it2->currentItem()->symbol() );
  it2->next();
  ASSERT_EQ( "2", it2->currentItem()->symbol() );

  it->next();
  ASSERT_EQ( "Y", it->currentItem()->symbol() );
  it->next();
  ASSERT_TRUE( it->isDone() );

}

TEST(iterator, firstList) {
    Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    Struct t(Atom("t"), { &X, &two });
    List l({ &one, &t, &Y });
    // ListIterator it(&l);
    Iterator<Term*> *itList = l.createIterator();

    itList->first();
    ASSERT_EQ("1", itList->currentItem()->symbol());
    ASSERT_FALSE(itList->isDone());
    itList->next();
    ASSERT_EQ("t(X, 2)", itList->currentItem()->symbol());
    ASSERT_FALSE(itList->isDone());
    itList->next();
    ASSERT_EQ("Y", itList->currentItem()->symbol());
    itList->next();
    ASSERT_TRUE(itList->isDone());
}

TEST(iterator, NullIterator){
  Number one(1);
  NullIterator<Term*> nullIterator(&one);
  nullIterator.first();
  ASSERT_TRUE(nullIterator.isDone());
  Iterator<Term*> * it = one.createIterator();
  it->first();
  ASSERT_TRUE(it->isDone());
}

//*************************************************************
//*************************************************************

TEST( iterator, bfsList1 ){
  Number num1(1);
  Number num2(2);
  Number num3(3);
  Number num4(4);
  Number num5(5);
  Number num6(6);
  List list3( {&num5, &num6} );
  List list2( {&num2, &num3, &list3, &num4} );
  List list( {&num1, &list2} );  //[1, [2, 3, [5,6], 4]]
  Iterator<Term*> *it = list.createBFSIterator();
  it->first();
  ASSERT_EQ( "1", it->currentItem()->symbol() );
  it->next();
  ASSERT_EQ( "[2, 3, [5, 6], 4]", it->currentItem()->symbol() );
  it->next();
  ASSERT_EQ( "2", it->currentItem()->symbol() );
  it->next();
  ASSERT_EQ( "3", it->currentItem()->symbol() );
  it->next();
  ASSERT_EQ( "[5, 6]", it->currentItem()->symbol() );
  it->next();
  ASSERT_EQ( "4", it->currentItem()->symbol() );
  it->next();
  ASSERT_EQ( "5", it->currentItem()->symbol() );
  it->next();
  ASSERT_EQ( "6", it->currentItem()->symbol() );
  ASSERT_FALSE( it->isDone() );
  it->next();
  ASSERT_TRUE( it->isDone() );
}


TEST( iterator, bfsList2 ){
  Number num1(1);
  Number num2(2);
  Number num3(3);
  Number num4(4);
  Number num5(5);
  Number num6(6);
  List list4( {&num6} );
  List list3( {&num4, &num5} );
  List list2( {&num2, &num3, &list4} );
  List list( {&num1, &list2, &list3} );  // [1,[2,3,[6]],[4,5]]
  Iterator<Term*> *it = list.createBFSIterator();
  it->first();
  ASSERT_EQ( "1", it->currentItem()->symbol() );
  it->next();
  ASSERT_EQ( "[2, 3, [6]]", it->currentItem()->symbol() );
  it->next();
  ASSERT_EQ( "[4, 5]", it->currentItem()->symbol() );
  it->next();
  ASSERT_EQ( "2", it->currentItem()->symbol() );
  it->next();
  ASSERT_EQ( "3", it->currentItem()->symbol() );
  it->next();
  ASSERT_EQ( "[6]", it->currentItem()->symbol() );
  it->next();
  ASSERT_EQ( "4", it->currentItem()->symbol() );
  it->next();
  ASSERT_EQ( "5", it->currentItem()->symbol() );
  it->next();
  ASSERT_EQ( "6", it->currentItem()->symbol() );

  ASSERT_FALSE( it->isDone() );
  it->next();
  ASSERT_TRUE( it->isDone() );
}

TEST( iterator, bfs_Struct1 ){
  Number num1(1);
  Number num2(2);
  Struct s( Atom( "s1" ), { &num1, &num2} );
  Iterator<Term*> *it = s.createBFSIterator();
  it->first();
  ASSERT_EQ( "1", it->currentItem()->symbol() );
  it->next();
  ASSERT_EQ( "2", it->currentItem()->symbol() );
  ASSERT_FALSE( it->isDone() );
  it->next();
  ASSERT_TRUE( it->isDone() );
}

TEST( iterator, bfs_Struct2 ){
  Number num1(1);
  Number num2(2);
  Number num3(3);
  Number num4(4);
  Number num5(5);
  Struct t( Atom( "t"), {&num2, &num3} );
  Struct z( Atom( "z"), {&num4, &num5} );
  Struct s( Atom( "s"), { &num1, &t, &z} );
  Iterator<Term*> *it = s.createBFSIterator();
  it->first();
  ASSERT_EQ( "1", it->currentItem()->symbol() );
  it->next();
  ASSERT_EQ( "t(2, 3)", it->currentItem()->symbol() );
  it->next();
  ASSERT_EQ( "z(4, 5)", it->currentItem()->symbol() );
  it->next();
  ASSERT_EQ( "2", it->currentItem()->symbol() );
  it->next();
  ASSERT_EQ( "3", it->currentItem()->symbol() );
  it->next();
  ASSERT_EQ( "4", it->currentItem()->symbol() );
  it->next();
  ASSERT_EQ( "5", it->currentItem()->symbol() );

  ASSERT_FALSE( it->isDone() );
  it->next();
  ASSERT_TRUE( it->isDone() );
}

TEST( iterator, dfs_list1 ){
  Number num1(1);
  Number num2(2);
  Number num3(3);
  Number num4(4);
  Number num5(5);
  List list3( {&num4, &num5} );  //[4,5]
  List list2( {&num2, &num3, &list3} );  //[2,3,[4,5]]
  List list( {&list2, &num1} );  //[[2,3,[4,5]],1]
  Iterator<Term*> *it = list.createDFSIterator();
  it->first();
  EXPECT_EQ( "[2, 3, [4, 5]]", it->currentItem()->symbol() );
  it->next();
  EXPECT_EQ( "2", it->currentItem()->symbol() );
  it->next();
  EXPECT_EQ( "3", it->currentItem()->symbol() );
  it->next();
  EXPECT_EQ( "[4, 5]", it->currentItem()->symbol() );
  it->next();
  EXPECT_EQ( "4", it->currentItem()->symbol() );
  it->next();
  EXPECT_EQ( "5", it->currentItem()->symbol() );
  it->next();
  EXPECT_EQ( "1", it->currentItem()->symbol() );
  ASSERT_FALSE( it->isDone() );
  it->next();
  ASSERT_TRUE( it->isDone() );
}

TEST( iterator, dfs_list2 ){
  Number num1(1);
  Number num2(2);
  Number num3(3);
  Number num4(4);
  Number num5(5);
  Number num6(6);
  List list4( {&num6} );
  List list3( {&num4, &num5} );
  List list2( {&num2, &num3, &list4} );
  List list( {&num1, &list2, &list3} );  // [1,[2,3,[6]],[4,5]]
  Iterator<Term*> *it = list.createDFSIterator();
  it->first();
  ASSERT_EQ( "1", it->currentItem()->symbol() );
  it->next();
  ASSERT_EQ( "[2, 3, [6]]", it->currentItem()->symbol() );
  it->next();
  ASSERT_EQ( "2", it->currentItem()->symbol() );
  it->next();
  ASSERT_EQ( "3", it->currentItem()->symbol() );
  it->next();
  ASSERT_EQ( "[6]", it->currentItem()->symbol() );
  it->next();
  ASSERT_EQ( "6", it->currentItem()->symbol() );
  it->next();
  ASSERT_EQ( "[4, 5]", it->currentItem()->symbol() );
  it->next();
  ASSERT_EQ( "4", it->currentItem()->symbol() );
  it->next();
  ASSERT_EQ( "5", it->currentItem()->symbol() );

  ASSERT_FALSE( it->isDone() );
  it->next();
  ASSERT_TRUE( it->isDone() );
}

TEST( iterator, dfs_struct1 ){
  Number num1(1);
  Number num2(2);
  Number num3(3);
  Number num4(4);
  Number num5(5);
  Struct t( Atom( "t"), {&num2, &num3} );
  Struct z( Atom( "z"), {&num4, &num5} );
  Struct s( Atom( "s"), { &num1, &t, &z} );
  Iterator<Term*> *it = s.createDFSIterator();
  it->first();
  ASSERT_EQ( "1", it->currentItem()->symbol() );
  it->next();
  ASSERT_EQ( "t(2, 3)", it->currentItem()->symbol() );
  it->next();
  ASSERT_EQ( "2", it->currentItem()->symbol() );
  it->next();
  ASSERT_EQ( "3", it->currentItem()->symbol() );
  it->next();
  ASSERT_EQ( "z(4, 5)", it->currentItem()->symbol() );
  it->next();
  ASSERT_EQ( "4", it->currentItem()->symbol() );
  it->next();
  ASSERT_EQ( "5", it->currentItem()->symbol() );

  ASSERT_FALSE( it->isDone() );
  it->next();
  ASSERT_TRUE( it->isDone() );
}

TEST( iterator, dfs_struct2 ){
  Number num1(1);
  Number num2(2);
  Number num3(3);
  Number num4(4);
  Struct t( Atom( "t"), {&num1, &num2} );
  Struct s( Atom( "s" ), { &t, &num3, &num4} );  // s(t(1,2),3,4)
  Iterator<Term*> *it = s.createDFSIterator();
  it->first();
  ASSERT_EQ( "t(1, 2)", it->currentItem()->symbol() );
  Struct *s_name = dynamic_cast<Struct *>(it->currentItem());
  ASSERT_EQ( "t", (s_name->name()).symbol() );

  it->next();
  ASSERT_EQ( "1", it->currentItem()->symbol() );
  it->next();
  ASSERT_EQ( "2", it->currentItem()->symbol() );
  it->next();
  ASSERT_EQ( "3", it->currentItem()->symbol() );
  it->next();
  ASSERT_EQ( "4", it->currentItem()->symbol() );
  ASSERT_FALSE( it->isDone() );
  it->next();
  ASSERT_TRUE( it->isDone() );
}



TEST( iterator, combo_mix ){
  Number num1(1);
  Number num2(2);
  Atom bun( "bun" );
  Atom beffPatty("beffPatty");
  Atom shrededLett("shrededLett");
  Atom fried1("fried1");
  Atom fried2("fried2");
  List frieds({&fried1, &fried2} );
  Atom coke( "coke" );
  Atom bigMac("bigMac");
  Atom combol( "combol") ;
  Struct sbigMac( bigMac, {&bun,&beffPatty,&shrededLett} );
  Struct scombol( combol, { &sbigMac, &coke, &frieds } );
  Iterator<Term*> *it = scombol.createBFSIterator();
  it->first();
  ASSERT_EQ( "bigMac(bun, beffPatty, shrededLett)", it->currentItem()->symbol() );
  it->next();
  ASSERT_EQ( "coke", it->currentItem()->symbol() );
  it->next();
  ASSERT_EQ( "[fried1, fried2]", it->currentItem()->symbol() );
  it->next();
  ASSERT_EQ( "bun", it->currentItem()->symbol() );
  it->next();
  ASSERT_EQ( "beffPatty", it->currentItem()->symbol() );
  it->next();
  ASSERT_EQ( "shrededLett", it->currentItem()->symbol() );
  it->next();
  ASSERT_EQ( "fried1", it->currentItem()->symbol() );
  it->next();
  ASSERT_EQ( "fried2", it->currentItem()->symbol() );

}
#endif
