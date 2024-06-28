#ifndef __SLIDEBAR_H__
#define __SLIDEBAR_H__

#include <math.h>
#include "gl_canvas2d.h"

class slideBar{
public:
  int x, y;
  int lX;
  int bx, by;
  const int raio = 20;
  bool drag;
  int width, height;

  slideBar(int _x, int _y) {
    x = _x;
    y = _y;
    bx = _x;
    by = _y;
    drag = false;
    width = 200;
    height = 40;
    by = y+20;
    bx = _x;
  }

  void verifyClick(int mx, int my, int button, int state) {

    float dist = sqrt(pow(bx - mx, 2) + pow(by - my, 2));
    bool inside = dist <= raio;
    bool insideBar = bx  >= x && bx  <= x + width;
       if(inside && insideBar && button == 0 && state == 0) {
         lX = mx - x;
         drag = true;
       }
       if (state == 1 || !insideBar) {
            drag = false;
        }
    }

  void dragging (int mx, int my) {
    if (drag) {
        bx = mx - lX;
    }
  }


  void render() {

    CV::color(1,1,1);
    CV::rectFill(x, y, x+width, y+height);
    CV::color(0,0,0);
    CV::circleFill(bx, by, raio, 20);
    CV::text(x, y +50, std::to_string(bx - x).c_str());
  }



};

#endif
