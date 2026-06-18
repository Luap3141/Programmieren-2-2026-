/*
 * Polygons.h
 *
 *  Created on: Jun 18, 2026
 *      Author: luap314
 */

#ifndef POLYGONS_H_
#define POLYGONS_H_

#include <list>
#include <cmath>
#include <Drawing.h>
#include <unordered_set>
#include <iostream>

using namespace std;

template<typename C = long> struct Point {
   /*
    * struct Point
    * has two members, X position and Y position
    */
   C posX;
   C posY;
};

template<typename C = long> class Polygon {
   /*
    * class Polygon
    * Basic Class of this exercise
    * contains a color and list of points as members
    */
protected:
   list<Point<C>> points = {};
   unsigned color = 0;

public:

   /*
    * Polygon()
    * default constructor
    */
   Polygon() {}

   /*
    * Polygon(newColor)
    * constructor with color as parameter
    */
   Polygon(unsigned newColor) :
         color(newColor) {
   }

   /*
    * Polygon(other)
    * copy constructor
    */
   Polygon(Polygon &other) {
      points = other.points;
      color = other.color;
   }

   /*
    * operator=(other)
    * copy assignment operator
    */
   Polygon& operator=(Polygon &other) {
      points = other.points;
      color = other.color;
      return *this;
   }

   /*
    * ~Polygon
    * destructor
    */
   virtual ~Polygon() {}

   /*
    * clone()
    * creates a heap-allocated deep-copy
    */
   virtual Polygon* clone() {
      return new Polygon(*this);
   }

   /*
    * add(newX, newY)
    * adds a point with coordinates newXand newY to the polygon
    */
   void add(C newX, C newY) {
      struct Point<C> newPoint = { newX, newY };
      points.push_back(newPoint);
   }

   /*
    * draw(x0, y0, scaling)
    * draws polygon relative to x0 and y0, with scaling factor scaling
    * beginDrawing() needs to be called first
    * each vertex is a dot with a diameter of 4 pixels.
    * There is a line connecting each vertex to the next - the last and first vertices are connected as well
    */
   virtual void draw(C x0 = 0, C y0 = 0, C scaling = 1) {
      auto it = points.begin();
      auto current = points.begin();
      compsys::fillEllipse(x0 + scaling * it->posX - 2, y0 + scaling * it->posY - 2, 4, 4, this->color);
      ++it;
      while (it != points.end()) {
         compsys::fillEllipse(x0 + scaling * it->posX - 2, y0 + scaling * it->posY - 2, 4, 4, this->color);
         compsys::drawLine(x0 + scaling * current->posX, y0 + scaling * current->posY, x0 + scaling * it->posX, y0 + scaling * it->posY, this->color);
         current = it;
         ++it;
      }
      compsys::drawLine(x0 + scaling * points.begin()->posX, y0 + scaling * points.begin()->posY, x0 + scaling * current->posX, y0 + scaling * current->posY, this->color);
      return;
   }
};

template<typename C = long> class RegularPolygon: public Polygon<C> {

   /*
    * class RegularPolygon
    * subclass of Polygon
    * All RegularPolygons must be regular polygons.
    * Additionally, they have a center as well.
    */

   Point<C> center;

public:

   /*
    * RegularPolygon(centerX, centerY, radius, n, angle, newColor)
    * Creates a regular n-gon around (centerX,centerY) and radius radius.
    * it's rotated by angle
    */
   RegularPolygon(C centerX, C centerY, C radius, int n, double angle = 0,
         unsigned newColor = 0) {
      center = { centerX, centerY };
      this->color = newColor;
      const double pi = 3.1415926535897932386;

      C offsetX;
      C offsetY;
      for (int i = 0; i < n; i++) {
         offsetX = radius * cos(2 * pi * i / n + angle);
         offsetY = radius * sin(2 * pi * i / n + angle);
         this->add(centerX + offsetX, centerY + offsetY);
      }
   }

   /*
    * RegularPolyon(other)
    * copy constructor
    */
   RegularPolygon(RegularPolygon &other) {
      this->points = other.points;
      this->color = other.color;
      center = other.center;
   }

   /*
    * clone()
    * creates heap-allocated deep-copy
    */
   virtual RegularPolygon* clone() {
      return new RegularPolygon(*this);
   }

   /*
    * draw(x0, y0, scaling)
    * draws polygon relative to x0 and y0, with scaling factor scaling
    * beginDrawing() needs to be called first
    * each vertex is a dot with a diameter of 4 pixels.
    * There is a line connecting each vertex to the next - the last and first vertices are connected as well
    * Additionally, the center dot is drawn
    */
   virtual void draw(C x0 = 0, C y0 = 0, C scaling = 1.0) {
      Polygon<C>::draw(x0, y0, scaling);
      compsys::fillEllipse(x0 + scaling * center.posX - 2,
            y0 + scaling * center.posY - 2, 4, 4, this->color);
   }
};

template<typename C = long> class Hexagon : public RegularPolygon<C> {
   /*
    * class Hexagon
    * subclass of RegularPolygon
    * contains only a constructor where n is set to 6
    */
public:
   Hexagon(C centerX, C centerY, C radius, double angle,
            unsigned newColor = 0) : RegularPolygon<C>(centerX, centerY, radius, 6, angle,
                  newColor) {}
};

template<typename C = long> class Square : public RegularPolygon<C> {
   /*
    * class Square
    * subclass of RegularPolygon
    * contains only a constructor where n is set to 4
    */
public:
   Square(C centerX, C centerY, C radius, double angle,
            unsigned newColor = 0) : RegularPolygon<C>(centerX, centerY, radius, 4, angle,
                  newColor) {}
};

template<typename C = long> class Picture {
   /*
    * class Picture
    * contains a set of Polygons
    */
   unordered_set<Polygon<C>*> content;

public:

   /*
    * constructors...
    */
   Picture() {}
   Picture(Picture &other) {
      content = other.content;
   }
   Picture& operator=(Picture &other) {
      content = other.content;
      return *this;
   }

   /*
    * add(newPolygon)
    * adds a Polygon to the picture
    */
   void add(Polygon<C> &newPolygon) {
      content.insert(&newPolygon);
      cout << content.size() << " | " << &newPolygon << endl;
   }

   /*
    * draw(x,y,width,height,scaling)
    * draws a canvas of width width and height height.
    * Then draws a Polygons, translated by (x,y) and scaled by scaling
    * calls beginDrawing) and endDrawing() by itself.
    */
   void draw(C x, C y, int width, int height, C scaling = 1.0) {
      compsys::beginDrawing(width, height, "Picture");
      for (auto elem : this->content) {
         elem->draw(x, y, scaling);
      }
      compsys::endDrawing();
   }
};

#endif /* POLYGONS_H_ */
