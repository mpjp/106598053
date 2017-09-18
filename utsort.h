#ifndef EXP_H
#define EXP_H
#include "include/Shapes.h"
#include "include/Media.h"
#include "include/Sort.h"
#include <list>
using namespace std;

TEST (Sort, sortByIncreasingPerimeter) {
    Circle* cir = new Circle(2, 7, 11);
    Triangle* tri = new Triangle( {0, 1}, {1, 0}, {0, 0} );
    Rectangle* re = new Rectangle( 10, 20 , 12, 5 );

    std::list<Shape *> * shapes = new list<Shape *>;
    shapes->push_back(tri);
    shapes->push_back(cir);
    shapes->push_back(re);
    sortByIncreasingPerimeter( shapes ) ;

    double expect_arr[] = {3.41421, 34, 69.115103 };  //70
    int temp_arr = 0;

   for (std::list<Shape *>::iterator it=shapes->begin(); it != shapes->end(); ++it){
        ASSERT_NEAR(expect_arr[temp_arr++], (*it)->perimeter(), 0.001);
    }
}

TEST (Sort, sortByDecreasingPerimeter) {
    Circle* cir = new Circle(2, 7, 10);
    Triangle* tri = new Triangle( {1, 1}, {1, 2}, {2, 3} );
    Rectangle* re = new Rectangle( 10, 20 , 12, 6 );

    std::list<Shape *> * shapes = new list<Shape *>;
    shapes->push_back(tri);
    shapes->push_back(cir);
    shapes->push_back(re);
    sortByDecreasingPerimeter( shapes ) ;

    double expect_arr[] = {62.8319, 36,4.6502  };  //70
    int temp_arr = 0;

    for (std::list<Shape *>::iterator it=shapes->begin(); it != shapes->end(); ++it){
        ASSERT_NEAR(expect_arr[temp_arr++], (*it)->perimeter(), 0.001);
    }

}

TEST (Sort, sortByIncreasingArea) {
    Circle* cir = new Circle(2, 7, 5);
    Rectangle* re = new Rectangle(3, 8, 12, 21);
    Triangle* tri = new Triangle({1, 1}, {3, 1}, {3, 4});

    std::list<Shape *> * shapes = new list<Shape *>;
    shapes->push_back(tri);
    shapes->push_back(cir);
    shapes->push_back(re);

    sortByIncreasingArea( shapes ) ;
    double expect_area_arr[] = { 3, 78.5398, 252 };
    int temp_arr = 0;

    for (std::list<Shape *>::iterator it=shapes->begin(); it != shapes->end(); ++it){
      ASSERT_NEAR(expect_area_arr[temp_arr++], (*it)->area(), 0.001);
    }
}

TEST (Sort, sortByDecreasingArea) {

    Circle* cir = new Circle(2, 7, 5);
    Rectangle* re = new Rectangle(3, 8, 12, 21);
    Triangle* tri = new Triangle({1, 1}, {3, 1}, {3, 4});

    std::list<Shape *> * shapes = new list<Shape *>;
    shapes->push_back(tri);
    shapes->push_back(cir);
    shapes->push_back(re);

    sortByDecreasingArea( shapes ) ;
    double expect_area_arr[] = { 252, 78.5398, 3 };
    int temp_arr = 0;

    for (std::list<Shape *>::iterator it=shapes->begin(); it != shapes->end(); ++it){
      ASSERT_NEAR(expect_area_arr[temp_arr++], (*it)->area(), 0.001);
    }
}

TEST (Sort, sortByIncreasingCompactness) {

    Circle* cir = new Circle(3, 7, 10);
    Rectangle* re = new Rectangle(2, 10, 12, 21);
    Triangle* tri = new Triangle({1, 1}, {5, 2}, {5, 8});

    std::list<Shape *> * shapes = new list<Shape *>;
    shapes->push_back(cir);
    shapes->push_back(tri);
    shapes->push_back(re);

    sortByIncreasingCompactness( shapes ) ;
    double expect_area_arr[] = { 0.65987, 3.81818, 5 };
    int temp_arr = 0;

    for (std::list<Shape *>::iterator it=shapes->begin(); it != shapes->end(); ++it){
      ASSERT_NEAR(expect_area_arr[temp_arr++], (*it)->compactness(), 0.001);
    }
}

#endif
