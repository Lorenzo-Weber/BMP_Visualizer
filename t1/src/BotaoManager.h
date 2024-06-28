#ifndef __BOTAOMANAGER_H__
#define __BOTAOMANAGER_H__

#include "gl_canvas2d.h"
#include <vector>
#include <functional>
#include "Botao.h"
#include "imgManager.h"


class BotaoManager {
public:
   vector<Botao> botoes;
   int x;
   int offset;
   int iter;
   int alt, diff;

   BotaoManager() {
      x = 15;
      iter = 0;
   }

    // Insere botao e atualiza o x do proximo botao
   void insertBtn (int y, float w, float h, char * label, std::function<void()> func) {
      alt = y - y/8;
      diff = alt + (y - alt)/3;
      offset =  w + x;
      Botao * bt = new Botao(x + iter * offset, diff, w, h, 0.666, 0.854, 0.941, label, func);
      botoes.push_back(*bt);
      iter++;
   }

   void render () {
      for (int i = 0; i < botoes.size(); i++) {
         botoes[i].render();
      }
   }

   void action (int mx, int my, int button, int state) {
      if(button == 0 && state == 0) {
         for (int i = 0; i < botoes.size(); i++) {
            botoes[i].verifyClick(mx, my);
         }

      }
   }
};

#endif
