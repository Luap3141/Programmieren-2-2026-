/*
 * Polygon.h
 * Declares classes Polygon, RegularPolygon, Hexagon, Square and Picture
 * also declares their methods and a handful of implementations if they are jsut one line.
 */

struct Vertex {

   double posX;
   double posY;

   struct Vertex *next;

};

class Polygon {
   /*
    * class Polygon
    * a Polygon is a linked list of Vertices that each have an x and y coordinate.
    * it is closed, that means the last vertex is connected to the first.
    * it also stores its color in hexadecimal
    */
protected:
   Vertex *points = nullptr;
   unsigned int color = 0x0;

public:
// create polygon in denoted color (default black)
   Polygon(unsigned int color = 0);
// copy constructor, copy assignment operator, destructor
   Polygon(Polygon &p);
   Polygon& operator=(Polygon &p);
   virtual ~Polygon();
// create a heap-allocated copy of this polygon
   virtual Polygon* clone();
// add point with relative coordinates (x,y) to polygon
   void add(double x, double y);
// draws the polygon at absolute coordinates (x0,y0) scaled by factor f;
// thus every point (x,y) is drawn at position (x0+x*f, y0+y*f)
   virtual void draw(double x0 = 0, double y0 = 0, double f = 1);
};

class RegularPolygon: public Polygon {
   /*
    * class RegularPolygon
    * a RegularPolygon is a Polygon that looks like a convex, regular polygon.
    * Additionally, it has a center, which is also drawn as a point.
    * Represented by a linked List.
    */
protected:
   double centerX = 0;
   double centerY = 0;
public:

   /*
    * Default Constructor
    */
   RegularPolygon() {
   }
   ;
   /*
    * RegularPolygon(x,y,r,n,a,c)
    * Creates a regular Polygon
    * x and y are the position of the center
    * r is the radius, so the distance from the center of a vertex
    * n is the number of vertices
    * a is the angle of the vector from center to the first vertex. Default 0
    * c is the color in hexadecimal. Default Black (=0)
    */
   RegularPolygon(double x, double y, double r, int n, double a = 0,
         unsigned int c = 0);
   /*
    * Copy Constructor
    */
   RegularPolygon(RegularPolygon &p);
   /*
    * void draw(x0,y0,f)
    * draws the polygon.
    * has to be called after beginDrawing()
    * x0 and y0 are x and y offset.
    * f is scaling factor
    */
   virtual void draw(double x0 = 0, double y0 = 0, double f = 1);

   /*
    * Destructor
    */
   virtual ~RegularPolygon();

   /*
    * RegularPolygon* clone()
    * creates a heap-allocated copy
    */
   virtual RegularPolygon* clone();
};

class Square: public RegularPolygon {
   /*
    * class Square
    * a Square is a special case of a RegularPolygon.
    * it has 4 vertices
    */
public:

   /*
    * Square(x,y,r,n,a,c)
    * Creates a Square
    * x and y are the position of the center
    * r is the radius, so the distance from the center of a vertex
    * a is the angle of the vector from center to the first vertex. Default 0
    * c is the color in hexadecimal. Default Black (=0)
    */
   Square(double x, double y, double r, double a = 0, unsigned int c = 0) :
         RegularPolygon(x, y, r, 4, a, c) {
   }
   /*
    * Square(p)
    * Copy constructor
    */
   Square(Square &p) :
         RegularPolygon(p) {
   }
   ;
   ;
};

class Hexagon: public RegularPolygon {
   /*
    * class Hexagon
    * a Hexagon is a special case of a Regularpolygon.
    * it has 6 vertices
    */
public:

   /*
    * Hexagon(x,y,r,a,c)
    * Creates a Hexagon
    * x and y are the position of the center
    * r is the radius, so the distance from the center of a vertex
    * a is the angle of the vector from center to the first vertex. Default 0
    * c is the color in hexadecimal. Default Black (=0)
    */
   Hexagon(double x, double y, double r, double a = 0, unsigned int c = 0) :
         RegularPolygon(x, y, r, 6, a, c) {
   }
   /*
    * Hexagon(p)
    * Copy Constructor
    */
   Hexagon(Hexagon &p) :
         RegularPolygon(p) {};
};

class Picture {
   /*
    * class Picture
    * a Picture is a linked list. Each Element contains a Polygon as Data.
    */
   Polygon *data = nullptr;
   Picture *next = nullptr;
public:

   /*
    * Default Constructor
    */
   Picture() {
   }
   /*
    * Copy constructor
    */
   Picture(Picture &p);
   /*
    * Copy assignment operator
    */
   Picture& operator=(Picture &p);
   /*
    * Destructor
    */
   ~Picture();

   /*
    * void add(p)
    * Adds Polygon p to the linked List that is your Picture
    */
   void add(Polygon &p);

   /*
    * draw(x,y,w,h,f)
    * Creates a Canvas of width w and height h.
    * Draws all the polygons in the picture from position (x,y) with scaling factor f.
    */
   void draw(double x, double y, double w, double h, double f = 1.0);
};
