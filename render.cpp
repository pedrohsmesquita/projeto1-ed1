#include "render.h"
#include "palavras_lista.h"

Texture2D imagemTelaInicial;

void escurecerCor(const Color& corOriginal, Color& cor, float fatorEscurecer) {
    cor.r = corOriginal.r * fatorEscurecer;
    cor.g = corOriginal.g * fatorEscurecer;
    cor.b = corOriginal.b * fatorEscurecer;
    cor.a = corOriginal.a;
}

void desenharLetraContorno(const Texto& texto, float grossura) {
    Color cor;
    if (texto.mouseSobre) cor = texto.corSobre;
    else cor = texto.cor;
    if (grossura > 0.0f) {
        Color corEscurecida;
        escurecerCor(cor, corEscurecida, 0.70f);
        DrawTextEx(*texto.fonte, texto.conteudo,
                   (Vector2){texto.posicao.x - grossura, texto.posicao.y - grossura},
                   texto.tamanho, texto.espacamento, corEscurecida);
        DrawTextEx(*texto.fonte, texto.conteudo,
                   (Vector2){texto.posicao.x + grossura, texto.posicao.y - grossura},
                   texto.tamanho, texto.espacamento, corEscurecida);
        DrawTextEx(*texto.fonte, texto.conteudo,
                   (Vector2){texto.posicao.x - grossura, texto.posicao.y + grossura},
                   texto.tamanho, texto.espacamento, corEscurecida);
        DrawTextEx(*texto.fonte, texto.conteudo,
                   (Vector2){texto.posicao.x + grossura, texto.posicao.y + grossura},
                   texto.tamanho, texto.espacamento, corEscurecida);
    }
    DrawTextEx(*texto.fonte, texto.conteudo, texto.posicao, texto.tamanho, texto.espacamento, cor);

}

void desenharBotao(const CaixaTexto &ct, float grossura, float escurecer) {
    Color corEscurecida, cor;

    if (ct.caixa.mouseSobre)
        cor = ct.caixa.corSobre;
    else cor = ct.caixa.cor;

    escurecerCor(cor, corEscurecida, escurecer);
    DrawRectangleRounded(ct.caixa.retangulo, ct.caixa.redondeza, ct.caixa.segmentos, cor);
    DrawRectangleRoundedLines(ct.caixa.retangulo, ct.caixa.redondeza, ct.caixa.segmentos, corEscurecida);
    desenharLetraContorno(ct.texto, grossura);
}

void desenharPalavra(const lista_grafica::ListaLetra &listaV) {
    lista_grafica::NodoLetra *no = listaV.primeiro->prox;

    while (no != NULL) {
        float x = no->info.estilo.posicao.x;
        DrawTextCodepoint(*(no->info.estilo.fonte), no->info.letra->val,
                          no->info.estilo.posicao, no->info.estilo.tamanho, no->info.estilo.cor);
        no = no->prox;
    }
}

void desenharPalavraCaixa(const lista_grafica::ListaLetra &listaV) {
    lista_grafica::NodoLetra *no = listaV.primeiro->prox;

    while (no != NULL) {
        DrawRectangleRounded(no->info.caixa.retangulo, no->info.caixa.redondeza, no->info.caixa.segmentos, no->info.caixa.cor);
        no = no->prox;
    }
    desenharPalavra(listaV);
}

void desenharCronometro(const lista_grafica::ListaLetra &lista) {
    DrawTextEx(*lista.primeiro->info.estilo.fonte,
               "Tempo",
               (Vector2){lista.primeiro->info.estilo.posicao.x, lista.primeiro->info.estilo.posicao.y - 16.0f},
               lista.primeiro->info.estilo.tamanho, 0.0f, lista.primeiro->info.estilo.cor);
    desenharPalavra(lista);
}

void desenharPontuacao(const lista_grafica::ListaLetra &lista) {
    DrawTextEx(*lista.primeiro->info.estilo.fonte,
               "Pontuacao",
               (Vector2){lista.primeiro->info.estilo.posicao.x, lista.primeiro->info.estilo.posicao.y - 16.0f},
               lista.primeiro->info.estilo.tamanho, 0.0f, lista.primeiro->info.estilo.cor);
    desenharPalavra(lista);
}

void desenharCaixa(const lista_grafica::ListaCaixa &lista) {
    lista_grafica::NodoCaixa *no = lista.primeiro->prox;

    while (no != NULL) {
        DrawRectangleRounded(no->caixa.retangulo, no->caixa.redondeza, no->caixa.segmentos, no->caixa.cor);
        no = no->prox;
    }
}

void desenharListaPalavras(lista_list::ListaLista &lista) {
    lista_list::NodoLista *no = lista.primeiro;

    while (no != NULL) {
        desenharPalavra(no->palavra);
        no = no->prox;
    }
}

void desenharTelaInicial() {
    DrawTexture(imagemTelaInicial, 0, 0, WHITE);
}

#define IMAGEM_TELA_INICIAL "assets/images/imagem_inicial.png"

void carregarImagemTelaInicial() {
    imagemTelaInicial = LoadTexture(IMAGEM_TELA_INICIAL);
}

void descarregarImagemTelaInicial() {
    UnloadTexture(imagemTelaInicial);
}
