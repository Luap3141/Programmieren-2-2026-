//cpp file for "Polygon.h"
#include "Polygon.h"
#include "Drawing.h"
#include <cmath>

Polygon::Polygon(unsigned int color) {
   this->color = color;
   this->points = nullptr;
}

Polygon::Polygon(Polygon &p) {
   this->color = p.color;
   if (p.points == nullptr) {
      this->points = nullptr;
      return;
   }

   Vertex *other = p.points;
   Vertex *tmp = new Vertex;
   this->points = tmp;
   while (true) {
      tmp->posX = other->posX;
      tmp->posY = other->posY;

      if (other->next == nullptr) {
         tmp->next = nullptr;
         return;
      }

      tmp->next = new Vertex;

      other = other->next;
      tmp = tmp->next;
   }
}

Polygon& Polygon::operator=(Polygon &p) {
   this->color = p.color;
   if (p.points == nullptr) {
      this->points = nullptr;
      return *this;
   }

   Vertex *other = p.points;
   Vertex *tmp = new Vertex;
   this->points = tmp;
   while (true) {
      tmp->posX = other->posX;
      tmp->posY = other->posY;

      if (other->next == nullptr) {
         tmp->next = nullptr;
         return *this;
      }

      tmp->next = new Vertex;

      other = other->next;
      tmp = tmp->next;
   }
   return *this;
}

Polygon::~Polygon() {
   Vertex *curr = this->points;
   Vertex *tmp;
   while (true) {
      if (curr == nullptr) {
         return;
      }
      tmp = curr->next;
      delete curr;
      curr = tmp;
   }
}

Polygon* Polygon::clone() {
   Polygon *clone = new Polygon(*this);
   return clone;
}

void Polygon::add(double x, double y) {
   if (this->points == nullptr) {
      this->points = new Vertex;
      this->points->posX = x;
      this->points->posY = y;
      this->points->next = nullptr;
      return;
   }
   Vertex *tmp = this->points;
   while (true) {
      if (tmp->next == nullptr) {
         tmp->next = new Vertex;
         tmp->next->posX = x;
         tmp->next->posY = y;
         tmp->next->next = nullptr;
         return;
      }
      tmp = tmp->next;
   }

}

void Polygon::draw(double x0, double y0, double f) {
   if (this->points == nullptr) {
      return;
   }
   Vertex *tmp = this->points;
   double startX = 0, startY = 0, endX = 0, endY = 0;
   while (true) {
      startX = x0 + tmp->posX * f;
      startY = y0 + tmp->posY * f;
      compsys::fillEllipse(startX - 2, startY - 2, 4, 4, this->color);

      if (tmp->next == nullptr) {
         break;
      }

      tmp = tmp->next;
      endX = x0 + tmp->posX * f;
      endY = y0 + tmp->posY * f;
      compsys::drawLine(startX, startY, endX, endY, this->color);
   }
   compsys::drawLine(endX, endY, x0 + this->points->posX * f,
         y0 + this->points->posY * f, this->color);
}

RegularPolygon::RegularPolygon(double x, double y, double r, int n, double a,
      unsigned int c) {
   centerX = x;
   centerY = y;
   color = c;
   points = nullptr;
   const double pi = 3.14159265358979323846;

   double offsetX, offsetY;
   for (int i = 0; i < n; i++) {
      offsetX = r * std::cos(2 * pi * i / n + a);
      offsetY = r * std::sin(2 * pi * i / n + a);
      this->add(x + offsetX, y + offsetY);
   }
}

RegularPolygon::RegularPolygon(RegularPolygon &p) :
      Polygon::Polygon(p) {
   this->centerX = p.centerX;
   this->centerY = p.centerY;
}

void RegularPolygon::draw(double x0, double y0, double f) {
   Polygon::draw(x0, y0, f);
   compsys::fillEllipse(x0 + f * this->centerX - 2, y0 + f * this->centerY - 2,
         4, 4, this->color);
}

RegularPolygon::~RegularPolygon() {
   //Nothing to be done here as the linked list is handled by Polygons destructor.
}

RegularPolygon* RegularPolygon::clone() {
   RegularPolygon *clone = new RegularPolygon(*this);
   return clone;
}

Picture::~Picture() {
   if (this == nullptr) {
      if (this->data != nullptr) {
         delete this->data;
      }
      return;
   }
   delete this->next;
}

Picture::Picture(Picture &p) {
   //can this be recursive??
   this->data = p.data->clone();
   if (p.next == nullptr) {
      this->next = nullptr;
      return;
   }
   this->next = new Picture(p);
}

Picture& Picture::operator=(Picture &p) {
   this->data = p.data->clone();
   if (p.next == nullptr) {
      this->next = nullptr;
      return *this;
   }
   this->next = new Picture(p);
   return *this;
}

void Picture::add(Polygon &p) {
   if (this->next == nullptr && this->data == nullptr) {
      this->data = p.clone();
      return;
   }
   Picture *tmp = this;
   while (true) {
      if (tmp->next == nullptr) {
         tmp->next = new Picture;
         tmp = tmp->next;
         tmp->data = p.clone();
         return;
      }
      tmp = tmp->next;
   }
}

void Picture::draw(double x, double y, double w, double h, double f) {
   compsys::beginDrawing(w, h, "Picture");
   if (this->next == nullptr && this->data == nullptr) {
      compsys::endDrawing();
      return;
   }
   Picture *tmp = this;
   while (true) {
      tmp->data->draw(x, y, f);
      if (tmp->next == nullptr) {
         compsys::endDrawing();
         return;
      }
      tmp = tmp->next;
   }
}
