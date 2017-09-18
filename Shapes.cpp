
#include "include/Shapes.h"
#include <list>
#include <iterator>

using namespace std;
double sumOfArea(const std::vector<Shape *> & shapes) {

    double total =0;

    for (Shape *shapePoint: shapes)
        total += shapePoint->area();

    return total;

}

double sumOfPerimeter(const std::vector<Shape *> & shapes){

    double total = 0;

    for (Shape *shapePoint: shapes)
        total += shapePoint->perimeter();

    return total;

}

Shape* theLargestArea(const std::vector<Shape *> & shapes){

    Shape *largestShape = nullptr;
    double largestArea = 0;

    for (Shape *shapePoint: shapes)
        if(shapePoint->area() >= largestArea){
            largestArea = shapePoint->area();
            largestShape = shapePoint;
        }

    return largestShape;

}

double distanceOfVertexs(const vertex vertex_1, const vertex vertex_2) {
    double diff_X, diff_Y, distance;

    diff_X = vertex_1.x - vertex_2.x;
    diff_Y = vertex_1.y - vertex_2.y;

    distance = sqrt(((diff_X * diff_X) + (diff_Y * diff_Y)));

    return distance;
}


void Swap( std::list<Shape *>::iterator it, std::list<Shape *>::iterator it2){
  Shape* a = *it;
  *it = *it2;
  *it2 = a;
}

std::list<Shape *>::iterator getElement( std::list<Shape *> *_list, int target ){
  list<Shape *>::iterator it = _list->begin();
  for( int i = 0; i < target ; i++ ) ++it;
  return it;
}




//----------------------------------------------------------------------------


void sortByDecreasingPerimeter(std::list<Shape *> * shapeList) {
  for( int i = 0; i < shapeList->size(); i++ ){
    for( int j = i ; j > 0 ; j-- ){
      if( (*getElement( shapeList, j ))->perimeter() > (*getElement( shapeList, j-1 ))->perimeter() ) {
          Swap( getElement( shapeList, j ), getElement( shapeList, j-1 ) );
      }
    }
  }
}

void sortByIncreasingPerimeter(std::list<Shape *> * shapeList){
  for( int i = 0; i < shapeList->size(); i++ ){
    for( int j = i ; j > 0 ; j-- ){
      if( (*getElement( shapeList, j ))->perimeter() < (*getElement( shapeList, j-1 ))->perimeter() ) {
          Swap( getElement( shapeList, j ), getElement( shapeList, j-1 ) );
      }
    }
  }
}

void sortByIncreasingArea( std::list<Shape *> * shapeList) {
  for( int i = 0; i < shapeList->size(); i++ ){
    for( int j = i ; j > 0 ; j-- ){
      if( (*getElement( shapeList, j ))->area() < (*getElement( shapeList, j-1 ))->area() ) {
          Swap( getElement( shapeList, j ), getElement( shapeList, j-1 ) );
      }
    }
  }
}

void sortByDecreasingArea( std::list<Shape *> * shapeList ) {
  for( int i = 0; i < shapeList->size(); i++ ){
    for( int j = i ; j > 0 ; j-- ){
      if( (*getElement( shapeList, j ))->area() > (*getElement( shapeList, j-1 ))->area() ) {
          Swap( getElement( shapeList, j ), getElement( shapeList, j-1 ) );
      }
    }
  }

}

void sortByIncreasingCompactness(std::list<Shape *> * shapeList){

  for( int i = 0; i < shapeList->size(); i++ ){
    for( int j = i ; j > 0 ; j-- ){
      if( (*getElement( shapeList, j ))->compactness() < (*getElement( shapeList, j-1 ))->compactness() ) {
          Swap( getElement( shapeList, j ), getElement( shapeList, j-1 ) );
      }
    }
  }

}
