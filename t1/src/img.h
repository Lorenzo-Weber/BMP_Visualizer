#ifndef ___IMG__H___
#define ___IMG__H___

#include <vector>
using namespace std;

#include "bmp.h"
#include "graphManager.h"
#include "iconManager.h"
#include "gl_canvas2d.h" // Assuming this header contains OpenGL canvas functions

// contem graficos e icones
class Img {
public:
    unsigned char * data;
    graphManager * graphs;
    iconManager * icons;
    char arquivo[100];
    int width, height;
    int x, y;
    int r, g, b;
    int len = 255;
    vector<int> cR, cG, cB;
    int w, a, s, d;
    int gray, drag, clicked;
    int lX, lY;
    float scaleFactor;
    bool flipX, flipY;

    Img(const char * filename, int _x, int _y, int sw, int sh) {
        Bmp * img = new Bmp(filename);
        graphs = new graphManager(sw, sh);
        icons = new iconManager(sw, sh);
        img->convertBGRtoRGB();
        data = img->getImage();
        width = img->getWidth();
        height = img->getHeight();
        r = 1, g = 1, b = 1;
        w = 0, a = 0, s = 0, d = 0;
        x = _x, y = _y;
        gray = 0, clicked = 0, drag = 0;
        strcpy(arquivo, filename);
        addGraphs();
        addIcons();
        scaleFactor = 1;
        flipX = false;
        flipY = false;
    }

     void dragging(int mx, int my) {
      if (drag) {
         x = mx - lX;
         y = my - lY;
      }
    }

    // verifica se o mouse esta dentro da imagem ou dentro da area de botoes

    void verifyClick(int mx, int my, int button, int state, int sh, int sw) {

       bool inside = ( (mx >= x && mx <= x + width * scaleFactor) && (my >= y && my <= y + height * scaleFactor) );
       bool buttonArea = (mx >= 0 && mx <= sw && my > sh - (sh/8) && my < sh);

       if(inside && button == 0 && state == 0) {
         lX = mx - x;
         lY = my - y;
         drag = 1;
         clicked = 1;
       }
       if(!inside && button == 0 && state == 0 && !buttonArea) {
         clicked = 0;
       }
        if (state == 1) {
            drag = 0;
        }
    }

    // se a imagem for selecionada cria uma hitbox de 15 pixeis maior
    void selected() {
         if(clicked) {
            CV::color(1 * r,1 * g,1 * b);
            CV::rect(x - 15, y + height * scaleFactor + 15, x + width * scaleFactor + 15, y - 15);
         }
    }

    void render() {
        float scaledWidth = width * scaleFactor;
        float scaledHeight = height * scaleFactor;

        for (int i = x; i < scaledWidth + x; i++) {
            for (int j = y; j < scaledHeight + y; j++) {
                int originalX = (flipX ? width - 1 - (i - x) / scaleFactor : (i - x) / scaleFactor);
                int originalY = (flipY ? height - 1 - (j - y) / scaleFactor : (j - y) / scaleFactor);

                if (originalX >= 0 && originalX < width && originalY >= 0 && originalY < height) {
                    int index = (originalY * width + originalX) * 3;

                    if (gray) {
                        CV::color((data[index] / 255.0), (data[index] / 255.0), (data[index] / 255.0));
                    } else {
                        CV::color((data[index] / 255.0) * r, (data[index + 1] / 255.0) * g, (data[index + 2] / 255.0) * b);
                    }
                }

                int renderX = i;
                int renderY = j;

                CV::rectFill(renderX, renderY, renderX + 1, renderY + 1);
            }
        }
    }

    void zera() {
        for (int i = 0; i < 255; i ++) {
            cR.push_back(0);
            cG.push_back(0);
            cB.push_back(0);
        }
    }

    void countRGB () {
        zera();
        for (int i = x; i < width + x ; i++) {
            for (int j = y; j < height + y; j++) {
                int index = ((j-y) * width + (i-x)) * 3;
                cR[data[index]]++;
                cG[data[index+1]]++;
                cB[data[index+2]]++;
            }
        }

    }

    void addGraphs () {
        countRGB();
        graphs->insertGraph(cR, 1,0,0);
        graphs->insertGraph(cG, 0,1,0);
        graphs->insertGraph(cB, 0,0,1);
    }

    void addIcons () {
        icons->insertIcon(1, 0, 0, arquivo);
        icons->insertIcon(0, 1, 0, arquivo);
        icons->insertIcon(0, 0, 1, arquivo);
    }

    void plotGraph () {
        graphs->render();
    }

    void plotIcons () {
        icons->render();
    }

    void moving () {
       if(w) y+=3;
       if(a) x-=3;
       if(s) y-=3;
       if(d) x+=3;
    }
};


#endif


