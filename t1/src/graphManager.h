#ifndef __GRAPHMANAGER_H__
#define __GRAPHMANAGER_H_

#include "gl_canvas2d.h"

#include <vector>
#include "graph.h"

class graphManager {
public:

    vector<graph> graphVec;
    int x, y, height;

    graphManager(int sw, int sh) {
        x = sw - 300;
        y = sh - 330;
        height = sh;

    }

    // Insere grafico e atualiza o y do proximo grafico
    void insertGraph (vector<int> color, int r, int g, int b) {
        graph * gr = new graph(x, y, color, r, g, b);
        graphVec.push_back(*gr);
        y -= 300;
    }

    void render() {
      CV::color(0.141, 0.180, 0.2);
      CV::rectFill(x - 300, height , x + 300, 0);
      CV::color(1,1,1);
      CV::text(x+50, height - 170, "Histograma");
      for (int i =0; i < graphVec.size(); i++) {
            graphVec[i].render();
      }
    }

};

#endif
