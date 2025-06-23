#ifndef RENDER_H
#define RENDER_H

#include "raylib.h"
#include "interface.h"

void desenharBotao(const CaixaTexto &ct, float grossura, float escurecer);

void desenharLetraContorno(const Texto& texto, float grossura);

void desenharPalavra(const letra_lista::ListaLetra &listaV);

#endif // RENDER_H
