#include <Functions.h>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "Drawing.h"
#include "Segment.h"
#include <thread>
using namespace std;
using namespace compsys;

const int W = 799;
const int H = 599;
const int T = 30;

int main(int argc, const char *argv[]) {
   beginDrawing(W, H, "Laser", 0xFFFFFF);
   Segment ray;
   int n;
   Segment *mirrors;
   init(argc, argv, ray, n, mirrors);
   drawMirrors(n, mirrors);
   for (int i = 0; i < T; i++) {
      Segment ray0;
      reflectRay(n, mirrors, ray, ray0);
      drawRay(ray);
      ray = ray0;
   }
   delete[] mirrors;

   cout << "Close window to exit..." << endl;
   endDrawing();
   return 0;
}

