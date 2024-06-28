#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

#include "gl_canvas2d.h"

#include "slideBarManager.h"
#include "imgManager.h"
#include "BotaoManager.h"
using namespace std;

//largura e altura inicial da tela . Alteram com o redimensionamento de tela.
int screenWidth = 1920, screenHeight = 1080;
int alt = screenHeight - screenHeight/8;

int mouseX, mouseY; //variaveis globais do mouse para poder exibir dentro da render().

// Crio todos os managers e a variavel img que itera sobre o arquivo bmp.txt
ImgManager * book;
BotaoManager * bts;
int img = 0;
slideBarManager * sl;

// Button Functions
    // Funcao de save, abre o arquivo save.txt e sobreescreve com o estado atual
  void save () {

    std::ofstream arquivo(".\\1_canvasGlut\\save\\save.txt", std::ios::trunc);

    if (arquivo.is_open()) {
        for(int i = 0; i < book->images.size(); i++) {
            arquivo << book->images[i].x << " " << book->images[i].y << " " << book->images[i].arquivo << "\n";
        }
        std::cout << "\n\nSalvo\n";
    } else {
        std::cerr << "Erro ao abrir o arquivo para escrita.\n";
    }
  }

  // Le o arquivo save.txt e insere as imagens
void load() {
    std::ifstream arquivo(".\\1_canvasGlut\\save\\save.txt");

    if (arquivo.is_open()) {
        int x, y;
        char arquivoNome[100];
        while (arquivo >> x >> y >> arquivoNome) {
            book->insertImg(x, y, arquivoNome);
        }
        std::cout << "\n\nCarregado\n";
    } else {
        std::cerr << "Erro ao abrir o arquivo para leitura.\n";
    }
}
    // Deleta a imagem selecionada
  void DeleteImage () {
     int found = book->findImg();
     if(found != -1) book->images.erase(book->images.begin() + found);

  }
    // Desativa o canal R da imagem selecionada
  void rChannel () {
     int found = book->findImg();
     if(found != -1) book->images[found].r = !book->images[found].r;

  }

  // Desativa o canal G da imagem selecionada
  void gChannel () {
     int found = book->findImg();
     if(found != -1) book->images[found].g = !book->images[found].g;

  }

  // Desativa o canal B da imagem selecionada
  void bChannel () {
     int found = book->findImg();
     if(found != -1) book->images[found].b = !book->images[found].b;

  }

  // Liga e desliga o gray scale
  void grayScale () {
     int found = book->findImg();
     if(found != -1) book->images[found].gray = !book->images[found].gray;

  }

  // Aumenta a imagem
  void scaleUp () {
      int found = book->findImg();
            if(found != -1)  {
            book->images[found].scaleFactor *= 2;
      }

  }

  // Diminui a imagem
  void scaleDown () {
      int found = book->findImg();
      if(found != -1)  {
            book->images[found].scaleFactor /= 2;
      }
  }

  // Flip no eixo y
  void flipY () {
      int found = book->findImg();
      if(found != -1)  {
            book->images[found].flipY = !book->images[found].flipY;
      }
  }

  // Flip no eixo x
  void flipX () {
        int found = book->findImg();
      if(found != -1)  {
            book->images[found].flipX = !book->images[found].flipX;
      }
  }

  // Adiciona uma imagem de acordo com o que esta escrito no arquivo bmp.txt
  void addImg() {
    vector<string> caminhos;
    char formatado[100];

    std::ifstream arquivo(".\\1_canvasGlut\\save\\bmp.txt");

    if (arquivo.is_open()) {
        string arquivoNome;
        while (arquivo >> arquivoNome) {
            caminhos.push_back(arquivoNome);
    }
    cout << caminhos[img];
    strcpy(formatado, caminhos[img].c_str());

    book->insertImg(100, 100, formatado);
    if(img == caminhos.size() - 1) {
        img = 0;
    }
    else img++;
    }
  }

void render()
{
   CV::clear(0.266, 0.341, 0.376);
   book->render();
   book->update(mouseX, mouseY);
   CV::color(0.141, 0.180, 0.2);
   CV::rectFill(0, screenHeight, screenWidth, alt);
   bts->render();
   sl->render();
   sl->update(mouseX, mouseY);
}

void keyboard(int key)
{
   book->keyboardListener(key, 1);
}

void keyboardUp(int key)
{
   book->keyboardListener(key, 0);
}

void mouse(int button, int state, int wheel, int direction, int x, int y)
{
   mouseX = x; //guarda as coordenadas do mouse para exibir dentro da render()
   mouseY = y;

   book->clickListener(mouseX, mouseY, button, state, screenHeight, screenWidth);
   bts->action(mouseX, mouseY, button, state);
   sl->clickListener(mouseX, mouseY, state, button);
}

int main(void)
{
   book = new ImgManager(screenWidth, screenHeight);
   bts = new BotaoManager();
   sl = new slideBarManager();
   sl->insertSlider(200, 200);

   load();

   bts->insertBtn(screenHeight, 60, 40, "Save", save);
   bts->insertBtn(screenHeight, 60, 40, "Del", DeleteImage);
   bts->insertBtn(screenHeight, 60, 40, "Add", addImg);
   bts->insertBtn(screenHeight, 60, 40,"Red", rChannel);
   bts->insertBtn(screenHeight, 60, 40, "Green", gChannel);
   bts->insertBtn(screenHeight, 60, 40, "Blue", bChannel);
   bts->insertBtn(screenHeight, 60, 40, "Gray", grayScale);
   bts->insertBtn(screenHeight, 60, 40, " - ", scaleDown);
   bts->insertBtn(screenHeight, 60, 40, " + ", scaleUp);
   bts->insertBtn(screenHeight, 60, 40, " Y ", flipY);
   bts->insertBtn(screenHeight, 60, 40, " X ", flipX);

   CV::init(screenWidth, screenHeight, "T1 Computação Gráfica");
   CV::run();
}
