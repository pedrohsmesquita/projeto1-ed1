#ifndef RENDER_H
#define RENDER_H

#include "raylib.h"
#include "interface.h"

void desenharBotao(const CaixaTexto &ct, float grossura, float escurecer);

void desenharLetraContorno(const Texto& texto, float grossura);

void desenharPalavra(const lista_grafica::ListaLetra &listaV);

void desenharPalavraCaixa(const lista_grafica::ListaLetra &listaV);

#endif // RENDER_H
