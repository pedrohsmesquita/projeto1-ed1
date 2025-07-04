#ifndef INTERFACE_H
#define INTERFACE_H

#include "raylib.h"
#include "string_lista.h"
#include "palavras_lista.h"

#define LARGURA_TELA 800
#define ALTURA_TELA 450
#define LARGURA32_CHAR_PX 20
#define ALTURA32_CHAR_PX 32
#define ESPACAMENTO_LETRAS 4
#define LETRA_ESCOLHIDA_TAM 30.0f
#define LETRA_DIGITADA_TAM 24.0f
#define LETRA_BOTOES_TAM 48.0f

struct Fontes {
    Font openSansBold48;
    Font openSansBold30;
    Font openSansSemiBold18;
    Font openSansSemiBold24;
};

struct Texto {
    Vector2 posicao;        // Posi��o do texto na tela
    char *conteudo;         // Conte�do para ser desenhado
    float tamanho;          // Tamanho do texto
    float espacamento;      // Espa�amento entre as letras
    bool mouseSobre;        // Identifica se o mouse est� sobre o elemento
    Color cor;              // Cor normal do texto
    Color corSobre;         // Cor para quando o mouse estiver por cima
    Font *fonte;            // Fonte para ser utilizada
};

struct Caixa {
    Rectangle retangulo;    // Posi��o inicial, largura e altura da caixa
    float redondeza;        // O qu�o redonda ser�o as bordas
    int segmentos;          // Quantidade de segmentos para as bordas
    bool mouseSobre;        // Identifica se o mouse est� sobre o elemento
    Color cor;              // Cor normal da caixa
    Color corSobre;         // Cor para quando o mouse estiver por cima
};

struct CaixaTexto {
    Caixa caixa;
    Texto texto;
    int id;
};

/**
 * Este namespace cont�m defini��o de uma outra lista cujo objetivo � auxiliar
 * no desenho gr�ficos dos caracteres da String implementada por lista.
 */
namespace lista_grafica {
    struct LetraEstilo {
        Vector2 posicao;                    // Posi��o da letra na tela
        float tamanho;                      // Tamanho da letra
        Color cor;                          // Cor da letra
        Font *fonte;                        // Fonte para ser utilizada
    };

    struct Letra {
        LetraEstilo estilo;                 // Estilo da letra
        Caixa caixa;
        bool animando;
        string_lista::NodoString *letra;    // Aponta para o n� da String
    };

    struct NodoLetra {
        Letra info;                         // Dado da lista
        NodoLetra *prox;                    // Aponta para a pr�xima letra visual
        NodoLetra *ant;                     // Aponta para o n� anterior
    };

    struct ListaLetra {
        NodoLetra *primeiro;
        NodoLetra *ultimo;
    };

    struct NodoCaixa {
        Caixa caixa;
        NodoCaixa *prox;
    };

    struct ListaCaixa {
        NodoCaixa *primeiro;
        NodoCaixa *ultimo;
    };

    /**
     * Inicializa a lista e utiliza a c�lula cabe�a para armazenar um estilo
     * base para futuras inser��es.
     */
    void criarLista(ListaLetra &lista);

    void criarLista(ListaCaixa &lista);

    void criarLista(ListaLetra &lista, Caixa &caixa);

    bool vazia(ListaLetra &lista);

    bool vazia(ListaCaixa &lista);

    /**
     * Insere no final da lista um n� que aponta para o respectivo n� da String.
     */
    void insereFinal(ListaLetra &lista, string_lista::NodoString *letra);

    void insereFinal(ListaCaixa &lista, Caixa &caixa);

    void removeInicio(ListaLetra &lista);

    void removeFinal(ListaLetra &lista);

    void removeFinal(ListaCaixa &lista);

    namespace utils {
        void inserirString(ListaLetra &lista, string_lista::String &listaS, float espaco);

        void inserirStringEstililizada(ListaLetra &lista, string_lista::String &listaS);

        /**
         * Deleta todos os n�s de ListaLetra (NodoLetra), sem remover a cabe�a.
         */
        void deletar(ListaLetra &lista);

        /**
         * Deleta todos os n�s de ListaCaixa (NodoCaixa), sem remover a cabe�a.
         */
        void deletar(ListaCaixa &lista);

        /**
         * Deleta todos os n�s de ListaLetra (NodoLetra) e tamb�m remove a cabe�a.
         */
        void destruir(ListaLetra &lista);

        /**
         * Deleta todos os n�s de ListaCaixa (NodoCaixa) e tamb�m remove a cabe�a.
         */
        void destruir(ListaCaixa &lista);

        void inserirLetra(ListaLetra &lista, string_lista::NodoString *letra, bool animando, float espaco);

        void inserirLetra(ListaLetra &lista, string_lista::NodoString *letra);
    }
}

namespace lista_list {
    struct NodoLista {
        lista_grafica::ListaLetra palavra;
        NodoLista *prox;
    };

    struct ListaLista {
        NodoLista *primeiro;
        NodoLista *ultimo;
    };

    void criarLista(ListaLista &lista);

    void insereFinal(ListaLista &lista, lista_grafica::ListaLetra &palavra);

    namespace utils {
        void inserePalavra(ListaLista &lista, palavra_lista::ListaPalavra &palavra);

        /**
         * Deleta o conte�do e todos os n�s de ListaLista (NodoLista).
         */
        void deletar(ListaLista &lista);

        /**
         * Deleta o conte�do e todos os n�s de ListaLista (NodoLista), incluindo a cabe�a.
         */
        void destruir(ListaLista &lista);
    }
}

void carregarFontes();

Font *obterOpenSansBold48();

Font *obterOpenSansBold30();

Font *obterOpenSansSemiBold24();

Font *obterOpenSansSemiBold18();

void definirEstiloCabecaSorteada(lista_grafica::ListaLetra &lista);

void centralizar(lista_grafica::ListaLetra &lista);

void centralizarTextoCaixa(lista_grafica::NodoLetra *no);

void letrasPlaceholders(lista_grafica::ListaLetra &listaP, lista_grafica::ListaCaixa &listaC);

#endif // INTERFACE_H
