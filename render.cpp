#include "render.h"

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
        DrawTextEx(texto.fonte, texto.conteudo,
                   (Vector2){texto.posicao.x - grossura, texto.posicao.y - grossura},
                   texto.tamanho, texto.espacamento, corEscurecida);
        DrawTextEx(texto.fonte, texto.conteudo,
                   (Vector2){texto.posicao.x + grossura, texto.posicao.y - grossura},
                   texto.tamanho, texto.espacamento, corEscurecida);
        DrawTextEx(texto.fonte, texto.conteudo,
                   (Vector2){texto.posicao.x - grossura, texto.posicao.y + grossura},
                   texto.tamanho, texto.espacamento, corEscurecida);
        DrawTextEx(texto.fonte, texto.conteudo,
                   (Vector2){texto.posicao.x + grossura, texto.posicao.y + grossura},
                   texto.tamanho, texto.espacamento, corEscurecida);
    }
    DrawTextEx(texto.fonte, texto.conteudo, texto.posicao, texto.tamanho, texto.espacamento, cor);

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

void desenharPalavra(const letra_lista::ListaLetra &listaV) {
    letra_lista::NodoLetra *no = listaV.primeiro->prox;
    float x = 20.0f, y = 20.0f;

    while (no != NULL) {
        DrawTextCodepoint(GetFontDefault(), no->info.letra->val, (Vector2){x, y}, 16.0f, BLACK);
        x += 15; y += 15;
        no = no->prox;
    }
}


