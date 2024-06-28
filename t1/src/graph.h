#ifndef __GRAPH_H__
#define __GRAPH_H__

#include "gl_canvas2d.h"
#include "img.h"

#include<math.h>
#include <vector>
#include <iostream>


class graph {
public:
   int w, h, x, y;
   int r, g, b;
   vector<int> color;

   graph(int _x, int _y, vector<int> _color, int _r, int _g, int _b) {
      x = _x, y = _y;
      w = 255;
      h = 300;
      r = _r;
      g = _g;
      b = _b;
      color = norm(_color);
   }

   // Divide todos os valores por 12 para ficar melhor de ver
   vector<int> norm (vector<int> vet) {

      for (int i =0 ; i < 255 ; i++) {
         vet[i] = vet[i] / 12;
      }
      return vet;
   }

   // Cria o grafico de fato
   void render() {
      CV::color(r, g, b);
      CV::rectFill(x-1,y+h/2, x+1, y);
      CV::rectFill(x, y-1, x+w/2, y+1);
      for(int i = 0; i < color.size(); i++) {
            CV::line(x+i, y, x+i+1, y + color[i]/3);
      }
   }

};

#endif
