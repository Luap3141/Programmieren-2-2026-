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
   C posX;
   C posY;
};

template<typename C = long> class Polygon {
protected:
   list<Point<C>> points = {};
   unsigned color = 0;

public:
   Polygon() {}
   Polygon(unsigned newColor) :
         color(newColor) {
   }
   Polygon(Polygon &other) {
      points = other.points;
      color = other.color;
   }
   Polygon& operator=(Polygon &other) {
      points = other.points;
      color = other.color;
      return *this;
   }
   virtual ~Polygon() {}

   virtual Polygon* clone() {
      return new Polygon(*this);
   }

   void add(C newX, C newY) {
      struct Point<C> newPoint = { newX, newY };
      points.push_back(newPoint);
   }

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

   Point<C> center;

public:
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

   RegularPolygon(RegularPolygon &other) {
      this->points = other.points;
      this->color = other.color;
      center = other.center;
   }

   virtual RegularPolygon* clone() {
      return new RegularPolygon(*this);
   }

   virtual void draw(C x0 = 0, C y0 = 0, C scaling = 1.0) {
      Polygon<C>::draw(x0, y0, scaling);
      compsys::fillEllipse(x0 + scaling * center.posX - 2,
            y0 + scaling * center.posY - 2, 4, 4, this->color);
   }
};

template<typename C = long> class Hexagon : public RegularPolygon<C> {
public:
   Hexagon(C centerX, C centerY, C radius, double angle,
            unsigned newColor = 0) : RegularPolygon<C>(centerX, centerY, radius, 6, angle,
                  newColor) {}
};

template<typename C = long> class Square : public RegularPolygon<C> {
public:
   Square(C centerX, C centerY, C radius, double angle,
            unsigned newColor = 0) : RegularPolygon<C>(centerX, centerY, radius, 4, angle,
                  newColor) {}
};

template<typename C = long> class Picture {
   unordered_set<Polygon<C>*> content;

public:
   Picture() {}
   Picture(Picture &other) {
      content = other.content;
   }
   Picture& operator=(Picture &other) {
      content = other.content;
      return *this;
   }
   void add(Polygon<C> &newPolygon) {
      content.insert(&newPolygon);
      cout << content.size() << " | " << &newPolygon << endl;
   }
   void draw(C x, C y, int width, int height, C scaling = 1.0) {
      compsys::beginDrawing(width, height, "Picture");
      for (auto elem : this->content) {
         elem->draw(x, y, scaling);
      }
      compsys::endDrawing();
   }
};

#endif /* POLYGONS_H_ */
