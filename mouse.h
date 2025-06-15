#ifndef MOUSE_H
#define MOUSE_H

#include "raylib.h"
#define SEM_SELECAO 0

struct Mouse {
    Vector2 posicao;        // Posi��o X e Y do mouse na tela
    int opcaoSelecionada;   // Armazena uma op��o selecionada na tela
    bool botaoEsqClick;     // Guarda se o bot�o esquerdo do mouse foi clicado
    MouseCursor tipoCursor; // Indica o tipo de cursor para ser desenhado na tela
};

Mouse* obterMouse();
void lerMouse(Mouse& mouse);

#endif // MOUSE_H
