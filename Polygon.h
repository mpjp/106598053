#ifndef POLYGON_H_INCLUDED
#define POLYGON_H_INCLUDED

#include "../Shape/Shape.h"
#include "../inClass1/Matrix.h"
#include <algorithm>
class Polygon: public Shape
 {
public:
    Polygon(Vector * a[], int numberOfVertices)
    :vertices(a, numberOfVertices) // constructor initialization
    {}
    Polygon(Polygon const &p)
     :vertices(p.vertices){}
    Vector & vertex(int i) const {
        return vertices[i];
    }
    int numberOfVertices ()const{
        return vertices.nRows();
    }
    double perimeter() const{
        double p=0;
        for(int i=1;i<numberOfVertices();i++){
            p+=(vertices[i+1]-vertices[i]).length();
        }
        p+=(vertices[numberOfVertices()]-vertices[1]).length();
        return p;
    }
    double area() const{
        double area=0;
        for(int i=2;i<numberOfVertices();i++){
           area+=VectorArea(vertices[1],vertices[i],vertices[i+1]);
        }
        return area;
    }
    std::string name() const{
        return std::string("polygon");
    }
private:
    Matrix vertices;
};
class IncreasingByAngleToRefVector{
public:
    IncreasingByAngleToRefVector(Vector const &cV,Vector const &refV)
    :c(cV),ref(refV){}
    bool operator()(Vector * u,Vector * v){
        return angle(ref, *u-c)<angle(ref, *v-c);
    }
    Vector c;
    Vector ref;
};
Polygon createConvexPolygon(Vector* vecs[], int n){
    Vector c = centroid(vecs, n);
    Vector ref = *vecs[0] - c;
    //std::sort(vecs, vecs + n, IncreasingByAngleToRefVector(c, ref));
    std::sort(vecs, vecs + n, [&c,&ref] (Vector *u,Vector *v )->bool{return angle(ref, *u-c)<angle(ref, *v-c);});
    return Polygon(vecs, n);
}

#endif // POLYGON_H_INCLUDED
