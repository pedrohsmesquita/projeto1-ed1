#ifndef RENDER_H
#define RENDER_H

#include "raylib.h"
#include "interface.h"

void desenharLetraContorno(const Texto& texto, float grossura);

void desenharBotao(const CaixaTexto &ct, float grossura, float escurecer);

void desenharLetraContorno(const Texto& texto, float grossura);

void desenharPalavra(const lista_grafica::ListaLetra &listaV);

void desenharPalavraCaixa(const lista_grafica::ListaLetra &listaV);

void desenharCaixa(const lista_grafica::ListaCaixa &lista);

void desenharCronometro(const lista_grafica::ListaLetra &lista);

void desenharPontuacao(const lista_grafica::ListaLetra &lista);

void desenharJanelaFimJogo();

void desenharListaPalavras(lista_list::ListaLista &lista);

void desenharFundo();

void carregarFundo();

void descarregarFundo();

void desenharLogotipo();

void carregarLogotipo();

void descarregarLogotipo();

#endif // RENDER_H
