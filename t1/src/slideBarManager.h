#ifndef __SLIDEBARMANAGER_H__
#define __SLIDEBARMANAGER_H__

#include <vector>
#include "slideBar.h"

class slideBarManager {
public:
    std::vector<slideBar> sliders;

    slideBarManager() {}

    void insertSlider(int x, int y) {
        slideBar* sl = new slideBar(x, y);
        sliders.push_back(*sl);
    }

    void update(int mx, int my) {
        for (int i = 0; i < sliders.size(); i++) {
            sliders[i].dragging(mx, my);
        }
    }

    void clickListener(int mx, int my, int state, int button) {
        for (int i = 0; i < sliders.size(); i++) {
            sliders[i].verifyClick(mx, my, button, state);
        }
    }

    void render() {
        for (int i = 0; i < sliders.size(); i++) {
            sliders[i].render();
        }
    }
};

#endif
