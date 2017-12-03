#ifndef UTITERATOR_H
#define UTITERATOR_H

#include "struct.h"
#include "variable.h"
#include "atom.h"
#include "list.h"
#include "iterator.h"
#include "number.h"
//
// TEST(iterator, first) {
//     Number one(1);
//     Variable X("X");
//     Variable Y("Y");
//     Number two(2);
//     Struct t(Atom("t"), { &X, &two });
//     Struct s(Atom("s"), { &one, &t, &Y });
//     // StructIterator it(&s);
//     Iterator<Term*> *itStruct = s.createIterator();
//     // Iterator& itStruct = it;
//     // ASSERT_EQ(it.first()->symbol());
//     itStruct->first();
//     ASSERT_EQ("1", itStruct->currentItem()->symbol());
//     ASSERT_FALSE(itStruct->isDone());
//     itStruct->next();
//     ASSERT_EQ("t(X, 2)", itStruct->currentItem()->symbol());
//     ASSERT_FALSE(itStruct->isDone());
//     itStruct->next();
//     ASSERT_EQ("Y", itStruct->currentItem()->symbol());
//     itStruct->next();
//     ASSERT_TRUE(itStruct->isDone());
// }
//
// TEST(iterator, nested_iterator) {
//   Number one(1);
//   Variable X("X");
//   Variable Y("Y");
//   Number two(2);
//   Struct t(Atom("t"), { &X, &two });  //t(X, 2)
//   Struct s(Atom("s"), { &one, &t, &Y }); // s( 1, t(X, 2), Y)
//
//   Iterator *it = s.createIterator();
//   it->first();
//   ASSERT_EQ( "1", it->currentItem()->symbol() );
//   it->next();
//   ASSERT_EQ( "t(X, 2)", it->currentItem()->symbol() );
//
//   Struct *s2 = dynamic_cast<Struct *>(it->currentItem());
//   Iterator* it2 = s2->createIterator();
//   it2->first();
//   ASSERT_EQ( "X", it2->currentItem()->symbol() );
//   it2->next();
//   ASSERT_EQ( "2", it2->currentItem()->symbol() );
//
//   it->next();
//   ASSERT_EQ( "Y", it->currentItem()->symbol() );
//   it->next();
//   ASSERT_TRUE( it->isDone() );
//   // StructIterator it(&s);
//   // it.first();
//   // it.next();
//   // Struct *s2 = dynamic_cast<Struct *>(it.currentItem());
//   //
//   // StructIterator it2(s2);
//   // it2.first();
//   // ASSERT_EQ("X", it2.currentItem()->symbol());
//   // ASSERT_FALSE(it2.isDone());
//   // it2.next();
//   // ASSERT_EQ("2", it2.currentItem()->symbol());
//   // ASSERT_FALSE(it2.isDone());
//   // it2.next();
//   // ASSERT_TRUE(it2.isDone());
// }
//
// TEST(iterator, firstList) {
//     Number one(1);
//     Variable X("X");
//     Variable Y("Y");
//     Number two(2);
//     Struct t(Atom("t"), { &X, &two });
//     List l({ &one, &t, &Y });
//     ListIterator it(&l);
//     Iterator* itList = &it;
//     itList->first();
//     ASSERT_EQ("1", itList->currentItem()->symbol());
//     ASSERT_FALSE(itList->isDone());
//     itList->next();
//     ASSERT_EQ("t(X, 2)", itList->currentItem()->symbol());
//     ASSERT_FALSE(itList->isDone());
//     itList->next();
//     ASSERT_EQ("Y", itList->currentItem()->symbol());
//     itList->next();
//     ASSERT_TRUE(itList->isDone());
// }
//
// TEST(iterator, NullIterator){
//   Number one(1);
//   NullIterator nullIterator(&one);
//   nullIterator.first();
//   ASSERT_TRUE(nullIterator.isDone());
//   Iterator * it = one.createIterator();
//   it->first();
//   ASSERT_TRUE(it->isDone());
// }
//
// TEST(iterator, NullIteratorTerm){
//   Number one(1);
//   Iterator* it = one.createIterator();
//   it->first();
//   it->next();
//   ASSERT_TRUE(it->isDone());
//   Atom tom( "tom" );
//   it = tom.createIterator();
//   ASSERT_TRUE(it->isDone());
//   Variable X( "X");
//   it = X.createIterator();
//   ASSERT_TRUE(it->isDone());
// }
//
// TEST( iteratior, list ){
//   Atom fires1( "fires1" );
//   Atom fires2( "fires2" );
//   List list( { &fires1, &fires2 });
//   Iterator *it = list.createIterator();
//   ASSERT_EQ( "fires1", it->currentItem()->symbol() );
//   it->first();
//   ASSERT_EQ( "fires1", it->currentItem()->symbol() );
//   it->next();
//   ASSERT_EQ( "fires2", it->currentItem()->symbol() );
//   it->next();
//   ASSERT_TRUE( it->isDone() );
// }
//
// // TEST( iterator, bfs ){
// //   Atom fires1( "fires1" );
// //   Atom fires2( "fires2" );
// //   List list( { &fires1, &fires2 });
// //   Iterator *it = list.createBFSIterator();
// //   it->first();
// //   ASSERT_EQ( "[fires1, fires2]", it->currentItem()->symbol() );
// //     it->next();
// //     ASSERT_FALSE( it->isDone() );
// //     ASSERT_EQ( "fires1", it->currentItem()->symbol() );
// //     // it->next();
// //     // ASSERT_EQ( "fires2", it->currentItem()->symbol() );
// //     // ASSERT_FALSE( it->isDone() );
// //     // it->next();
// //     // ASSERT_TRUE( it->isDone() );
// // }
//
// TEST( iterator, test ){
//   Atom fires1( "fires1" );
//   Atom fires2( "fires2" );
//
//   Atom fires5( "fires5" );
//   Atom fires6( "fires6" );
//   List list2( { &fires5, &fires6 });
//
//   List list( { &fires1, &fires2 , &list2  }); //[1,2,[5,6]]
//
//   Iterator *it = list.createIterator();
//   it->first();
//   ASSERT_EQ( "fires1", it->currentItem()->symbol() );
//   it->next();
//
//   Iterator *ait = (it->currentItem())->createIterator();
//   ASSERT_TRUE( ait->isDone() );
//   // ASSERT_EQ( "", ait->currentItem()->symbol() );
//
//   ASSERT_EQ( "fires2", it->currentItem()->symbol() );
//   it->next();
//   ASSERT_EQ( "[fires5, fires6]", it->currentItem()->symbol() );
//
//   Iterator *t2 = (it->currentItem())->createIterator();  //******
//   ASSERT_EQ( "fires5", t2->currentItem()->symbol() );
//   t2->next();
//   ASSERT_EQ( "fires6", t2->currentItem()->symbol() );
//   t2->next();
//   ASSERT_TRUE( t2->isDone() );
//
//   ASSERT_FALSE( it->isDone() );
//   it->next();
//   ASSERT_TRUE( it->isDone() );
// }
//
TEST( iterator, bfsList ){
  Number num1(1);
  Number num2(2);
  Number num3(3);
  List list( {&num1, &num2, &num3} );  // [1,2,3]
  Iterator<Term*> *it = list.createBFSIterator();
  // it->first();
  // // ASSERT_EQ( "[1, 2, 3]", it->currentItem()->symbol() );
  // // it->next();
  // ASSERT_EQ( "1", it->currentItem()->symbol() );
  // it->next();
  // ASSERT_EQ( "2", it->currentItem()->symbol() );
  // it->next();
  // ASSERT_EQ( "3", it->currentItem()->symbol() );
  //
  // ASSERT_FALSE( it->isDone() );
  // it->next();
  // ASSERT_TRUE( it->isDone() );
}

TEST( iterator, nested_bfs_List ){
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


TEST( iterator, nested_complext_bfsList ){
  Number num1(1);
  Number num2(2);
  Number num3(3);
  Number num4(4);
  Number num5(5);
  Number num6(6);
  List list4( {&num6} );
  List list3( {&num4, &num5} );
  List list2( {&num2, &num3, &list4} );
  List list( {&num1, &list2, &list3} );
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

TEST( iterator, dfs ){
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
  // ASSERT_EQ( "[[2, 3, [4, 5]], 1]", it->currentItem()->symbol() );
  // it->next();
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

TEST( iterator, bfsStruct ){
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

TEST( iterator, struct_bb ){
  Number num1(1);
  Number num2(2);
  Struct s( Atom( "s1" ), { &num1, &num2} );
  Iterator<Term*> *it = s.createBFSIterator();
  it->first();
  ASSERT_EQ( "1", it->currentItem()->symbol() );
}

#endif
