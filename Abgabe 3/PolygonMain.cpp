#include "Drawing.h"
#include "Polygon.h"
#include <iostream>

#include <cmath>

int main() {

   //Some Tests that I had in there when
   //trying to get copy onstructor, copy assignment operator etc to work.
   Polygon p = Polygon(0x000000);
   p.add(10, 10);
   p.add(25, 0);
   Polygon q;
   //Shows that my copy assignment operator works
   q = p;
   Polygon *r = p.clone();
   r->add(600, 500);
   q.add(30, 30);
   compsys::beginDrawing(700, 700, "Polygons");
   p.draw(300, 300, 8);
   q.draw(200, 300, 8);
   RegularPolygon x(100, 100, 50, 5);
   x.draw(100, 100, 3);
   compsys::endDrawing();

   //Septagons
   Picture test;
   for (int i = 0; i < 32; i++) {
      RegularPolygon a(0, 5 * i, 200, 7, i, 8 * i * 0x010000);
      test.add(a);
   }
   test.draw(300, 200, 600, 600);

   //Heaxgons and Squares
   Picture test1;
   for (int i = 0; i < 10; i++) {
      Square a(400, 400, 50 * i, i, 0x000000);
      Hexagon b(400, 400, 50 * i, i, 0xFFBBBB);
      test1.add(a);
      test1.add(b);
   }
   test1.draw(0, 0, 800, 800);

   //Snake approximates a lissajous curve. First it's drawn in the center, then in the corner at 4 times size
   Polygon snake;
   for (int i = 0; i < 120; i++) {
      const double pi = 3.14159265358979323846;
      snake.add(100 * std::sin(i / pi), 100 * std::cos(3 * i / pi));
   }
   Picture test2;
   test2.add(snake);
   test2.draw(400, 400, 800, 800, 1);
   Picture test3;
   test3 = test2;
   test3.draw(200, 200, 800, 800, 4);

   return 0;
}
