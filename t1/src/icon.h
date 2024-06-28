#ifndef ___ICON__H___
#define ___ICON__H___

#include "bmp.h"
#include "gl_canvas2d.h"


// um icone eh uma imagem com 1/3 do tamanho
class Icon {
public:
    unsigned char * data;
    int width, height;
    int x, y;
    int r, g, b;
    float scaleFactor;

    Icon(const char * filename, int _x, int _y, int _r, int _g, int _b) {
        Bmp * img = new Bmp(filename);
        img->convertBGRtoRGB();
        data = img->getImage();
        width = img->getWidth();
        height = img->getHeight();
        r = _r, g = _g, b = _b;
        x = _x, y = _y;
        scaleFactor = 0.3;
    }

    void render() {

        int scaledWidth = static_cast<int>(width * scaleFactor);
        int scaledHeight = static_cast<int>(height * scaleFactor);

        for (int i = x; i < scaledWidth + x; i++) {
            for (int j = y; j < scaledHeight + y; j++) {
                int origX = static_cast<int>((i - x) / scaleFactor);
                int origY = static_cast<int>((j - y) / scaleFactor);
                int index = (origY * width + origX) * 3;

                CV::color((data[index] / 255.0) * r, (data[index + 1] / 255.0) * g, (data[index + 2] / 255.0) * b);
                CV::rectFill(i, j, i + 1, j + 1);
            }
        }
    }

};
#endif
