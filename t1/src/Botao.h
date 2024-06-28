#ifndef __BOTAO_H__
#define __BOTAO_H__

#include "gl_canvas2d.h"
#include "img.h"
#include <functional>

class Botao{
public:
  float height, width, x, y, r, g, b;
  char label[100];
  int clicked = 0;

  std::function<void()> btnFunction;


  Botao(float _x, float _y, float _width, float _hei, float _r, float _g, float _b, char *_label, std::function<void()> func)
  {
     height  = _hei;
     width = _width;
     x = _x;
     y = _y;
     r = _r;
     g = _g;
     b = _b;
     strcpy(label, _label);
     btnFunction = func;
  }


  void render()
  {

    CV::color(r,g,b);
    CV::rectFill(x, y, x + width, y + height);
    CV::color(0.3, 0.3, 0.3);
    CV::text(x + 5, y + height/2, label);
  }

  //recebe as coordenadas do mouse para tratar clique ou detectar quando o mouse esta em cima do botao
  void verifyClick(int mx, int my)
  {
      if(mx >= x && mx <= (x + width) && my >= y && my <= (y + height)) btnFunction();
  }

};

#endif
