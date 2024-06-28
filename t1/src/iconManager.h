#ifndef ___ICONMANAGER__H___
#define ___ICONMANAGER__H___

#include <vector>

#include "icon.h"
#include "gl_canvas2d.h"

// cria, adiciona e altera o y para plotar ao lado dos graficos
class iconManager {
public:
   vector<Icon> icons;
   int x, y;

   iconManager(int _sw, int _sh) {
        x = _sw - 500;
        y = _sh - 300;

   }

   void insertIcon (int r, int g, int b, const char label[100]) {

      Icon * ic = new Icon(label,x, y, r, g, b);
      icons.push_back(*ic);
      y -= 300;
   }


   void render() {
       for(int i = 0; i < icons.size(); i++) {
            icons[i].render();
       }
   }

};


#endif

