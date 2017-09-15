#ifndef UTPOLYGON_H_INCLUDED
#define UTPOLYGON_H_INCLUDED

#include "../inClass1/Vector.h"
#include "Polygon.h"
#include <cmath>
using namespace std;

TEST(Polygon, construct) {
    double a[2] = {1,0}, b[2] = {1,1}, c[2] = {0, 0};
    Vector u(a, 2), v(b, 2), w(c, 2);
    // hmmm... maybe we need to fix Matrix
    Vector *p[3] = { &u, &v, &w};
    Polygon triangle(p, 3);

    ASSERT_EQ(u, triangle.vertex(1));
    ASSERT_EQ(v, triangle.vertex(2));
    ASSERT_EQ(w, triangle.vertex(3));
}

TEST(Polygon, perimeter) {
    double a[2] = {1,0}, b[2] = {1,1}, c[2] = {0, 0};
    Vector u(a, 2), v(b, 2), w(c, 2);
    Vector *p[3] = { &u, &v, &w};
    Polygon triangle(p, 3);

    ASSERT_EQ(1+1+sqrt(2), triangle.perimeter());
}

TEST(Polygon,area){
 double a[2] = {1,0}, b[2] = {1,1}, c[2] = {0, 0};
    Vector u(a, 2), v(b, 2), w(c, 2);
    Vector *p[3] = { &u, &v, &w};
    Polygon triangle(p, 3);

    ASSERT_NEAR(1.0/2.0,triangle.area(), 0.00001);
}
TEST(Polygon,areaSquare){
    double a[2] = {1, 0}, b[2] = {1, 1}, c[2] = {0, 1},d[2] = {0, 0};
    Vector u(a, 2), v(b, 2), w(c, 2), x(d, 2);
    Vector *p[4] = { &u, &v, &w, &x};
    Polygon square(p, 4);

    EXPECT_NEAR( 1.0, square.area(), 0.00001);
}

TEST(Polygon, Order){
    double a[2] = {1, 1}, b[2] = {0, 2}, c[2] = {0, 0},d[2] = {1, 0};
    Vector u(a, 2), v(b, 2), w(c, 2), x(d, 2);
    Vector *p[4] = { &u, &v, &w, &x};
    Polygon square(p, 4);

    EXPECT_NEAR( 1.5, square.area(), 0.00001);
}

TEST(Polygon, notOrder){
    double a[2] = {1, 1}, b[2] = {0, 2}, c[2] = {0, 0},d[2] = {1, 0};
    Vector u(b, 2), v(a, 2), w(c, 2), x(d, 2);
    Vector *p[4] = { &u, &v, &w, &x};
    Polygon square2 = createConvexPolygon(p, 4);

    EXPECT_NEAR( 1.5, square2.area(), 0.00001);
    EXPECT_NEAR( u[1], square2.vertex(1)[1],0.00001);
    EXPECT_NEAR( u[2], square2.vertex(1)[2],0.00001);
    EXPECT_NEAR( w[1], square2.vertex(2)[1],0.00001);
    EXPECT_NEAR( w[2], square2.vertex(2)[2],0.00001);
    EXPECT_NEAR( x[1], square2.vertex(3)[1],0.00001);
    EXPECT_NEAR( x[2], square2.vertex(3)[2],0.00001);
    EXPECT_NEAR( v[1], square2.vertex(4)[1],0.00001);
    EXPECT_NEAR( v[2], square2.vertex(4)[2],0.00001);

}


#endif // UTPOLYGON_H_INCLUDED
