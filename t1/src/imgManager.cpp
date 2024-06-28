#include "img.h" // Assuming this header contains necessary includes and declarations
#include "bmp.h"
#include "gl_canvas2d.h" // Assuming this header contains OpenGL canvas functions
/*
class Img {
public:
    unsigned char * data;
    int width, height;
    int x = 100;
    int y = 100;
    int r, g, b;
    int dragged, clicked;

    img(const char * filename) {
        Bmp * img = new Bmp(filename);
        img->convertBGRtoRGB();
        data = img->getImage();
        width = img->getWidth();
        height = img->getHeight();
        r = 1;
        g = 1;
        b = 1;
        dragged = 0;
        clicked = 0;
    }

    void verifyClick(int mx, int my) {
        if(mx >= x && mx <= x + width) {
            if (my >= y && my <= y + height) {
                clicked = 1;
            }
        }
    }

    void selected() {
        if (clicked) {
            CV::color(1,0,0);
            CV::rect(x - 15, y + height + 15, x + width + 15, y - 15);
        }
    }

    void render() {
        for (int i = x; i < width; i++) {
            for (int j = y; j < height; j++) {
                int index = ((j-y) * width + (i-x)) * 3;
                CV::color(data[index] / 255.0, data[index + 1] / 255.0, data[index + 2] / 255.0);
                CV::rectFill(i, j, i + 1, j + 1);
            }
        }
    }
};
*/
