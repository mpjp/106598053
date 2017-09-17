#ifndef EXP_H
#define EXP_H
#include "include/Shapes.h"
#include "include/Media.h"
#include "include/Sort.h"
using namespace std;
TEST (Sort, sortByIncreasingPerimeter) {
    Circle cir(2, 7, 11);
    Triangle tri( {0, 1}, {1, 0}, {0, 0} );
    Rectangle re( 10, 20 , 12, 5 );

    std::vector<Shape *> shapes;
    shapes.push_back(&tri);
    shapes.push_back(&cir);
    shapes.push_back(&re);

    sortByIncreasingPerimeter( shapes) ;
    double expect_arr[] = {3.41421, 34, 69.115103 };  //70
    int temp_arr = 0;

    for ( auto &i : shapes ){
        ASSERT_NEAR(expect_arr[temp_arr++], i->perimeter(), 0.001);
    }
}

TEST (Sort, sortByDecreasingPerimeter) {
    Circle cir(2, 7, 11);
    Triangle tri( {0, 1}, {1, 0}, {0, 0} );
    Rectangle re( 10, 20 , 12, 5 );

    std::vector<Shape *> shapes;
    shapes.push_back(&tri);
    shapes.push_back(&cir);
    shapes.push_back(&re);

    sortByDecreasingPerimeter( shapes) ;
    double expect_arr[] = {69.115103, 34,3.41421  };
    int temp_arr = 0;

    for ( auto &i : shapes ){
        ASSERT_NEAR(expect_arr[temp_arr++], i->perimeter(), 0.001);
    }

}

TEST (Sort, sortByIncreasingArea) {
    Circle cir(2, 7, 11);
    Rectangle rect(3, 8, 12, 21);
    Triangle tri({1, 1}, {3, 1}, {3, 4});

    std::vector<Shape *> shapes;
    shapes.push_back(&tri);
    shapes.push_back(&cir);
    shapes.push_back(&rect);
    sortByIncreasingArea( shapes );
    double expect_area_arr[] = { 3, 252, 380.133 };
    int temp_arr = 0;

    for ( auto &i : shapes ){
        ASSERT_NEAR(expect_area_arr[temp_arr++], i->area(), 0.001);
    }
}

TEST (Sort, sortByDecreasingArea) {
    Circle cir(2, 7, 11);
    Rectangle rect(3, 8, 12, 21);
    Triangle tri({1, 1}, {3, 1}, {3, 4});

    std::vector<Shape *> shapes;
    shapes.push_back(&tri);
    shapes.push_back(&cir);
    shapes.push_back(&rect);
    sortByDecreasingArea( shapes );
    double expect_area_arr[] = { 380.133, 252,3  };
    int temp_arr = 0;

    for ( auto &i : shapes ){
        ASSERT_NEAR(expect_area_arr[temp_arr++], i->area(), 0.001);
    }
}

TEST (Sort, sortByIncreasingCompactness) {

}

#endif
