#include <gtest/gtest.h>
#include "utSort.h"


//------------------------------
//#include "include/Shapes.h"
//#include "include/Media.h"


using namespace std;
int main( int argc , char **argv )
{
    testing :: InitGoogleTest( &argc , argv ) ;
    return RUN_ALL_TESTS( ) ;
    /*
    Circle cir(2, 7, 11);
    Triangle tri( {0, 1}, {1, 0}, {0, 0} );
    Rectangle re( 10, 20 , 12, 5 );

    std::vector<Shape *> shapes;
    shapes.push_back(&tri);
    shapes.push_back(&cir);
    shapes.push_back(&re);

    sortByDecreasingPerimeter( shapes) ;
    for ( auto &i : shapes ){
      cout << i->perimeter();
    }
    */
}
