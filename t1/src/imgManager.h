#ifndef ___IMGMANAGER__H___
#define ___IMGMANAGER__H___

#ifndef IMGMANAGER_H
#define IMGMANAGER_H
using namespace std;
#include <vector>

#include "img.h"
#include "gl_canvas2d.h"

// cria um vetor de imagens
class ImgManager {
public:
   vector<Img> images;
   int sw, sh;
   ImgManager(int _sw, int _sh) {
        sw = _sw;
        sh = _sh;
   }

   void insertImg (int x, int y, char * label) {

      Img * im = new Img(label, x, y, sw, sh);
      images.push_back(*im);
   }

    // funcao de update para poder capturar todas alteracoes
   void update(int mx, int my) {
      for (int i = 0; i < images.size(); i++) {
         images[i].selected();
         images[i].dragging(mx, my);
         images[i].moving();
         updateZ();
      }
   }
    // uma imagem ao ser clicada ela e jogada para o fim do vetor
   void updateZ () {
        for (int i = 0; i < images.size(); i++) {
            if(images[i].clicked) {
                images.push_back(images[i]);
                images.erase(images.begin() + i);
                break;
            }
        }
   }

   void clickListener (int mx, int my, int button, int state, int sh, int sw) {
      for (vector<Img>::reverse_iterator rit = images.rbegin(); rit != images.rend(); ++rit) {
         rit->verifyClick(mx, my, button, state, sh, sw);
         if (rit->clicked) break;
      }
   }

   // liga e desliga o movimento da imagem, type se refere a keyboard e keyboardup (1 e 0 respectivamente)
   void keyboardListener (int key, int type) {

      for (int i = 0; i < images.size(); i++) {
         if(images[i].clicked) {
            if(key == 119) {
               if(type) images[i].w = 1;
               else images[i].w = 0;
            }
            if(key == 115) {
               if(type) images[i].s = 1;
               else images[i].s = 0;
            }
            if (key == 97) {
               if(type) images[i].a = 1;
               else images[i].a = 0;
            }
            if (key == 100) {
               if(type) images[i].d = 1;
               else images[i].d = 0;
            }
         }
      }
   }

   void render() {
       for(int i = 0; i < images.size(); i++) {
            images[i].render();
            if(images[i].clicked) {
                images[i].plotGraph();
                images[i].plotIcons();
            }
       }
   }

   int findImg () {
      for (int i = 0; i < images.size(); ++i) {
         if(images[i].clicked) return i;
      }
      return -1;
   }

};


#endif // IMG_H


#endif // ___IMG__H___
