#ifndef INTERFACE_H
#define INTERFACE_H

#include "raylib.h"
#include "string_lista.h"

struct Texto {
    Vector2 posicao;        // Posi��o do texto na tela
    char *conteudo;         // Conte�do para ser desenhado
    float tamanho;          // Tamanho do texto
    float espacamento;      // Espa�amento entre as letras
    bool mouseSobre;        // Identifica se o mouse est� sobre o elemento
    Color cor;              // Cor normal do texto
    Color corSobre;         // Cor para quando o mouse estiver por cima
    Font fonte;            // Fonte para ser utilizada
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
namespace letra_lista {
    struct LetraEstilo {
        Vector2 posicao;                    // Posi��o da letra na tela
        float tamanho;                      // Tamanho da letra
        Color cor;                          // Cor da letra
        Font *fonte;                        // Fonte para ser utilizada
    };

    struct Letra {
        LetraEstilo estilo;                 // Estilo da letra
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

    /**
     * Inicializa a lista e utiliza a c�lula cabe�a para armazenar um estilo
     * base para futuras inser��es.
     */
    void criarLista(ListaLetra &lista, LetraEstilo &estiloBase);

    bool vazia(ListaLetra &lista);

    /**
     * Insere no final da lista um n� que aponta para o respectivo n� da String.
     */
    void insereFinal(ListaLetra &lista, string_lista::NodoString *letra);

    void removeInicio(ListaLetra &lista);

    void removeFinal(ListaLetra &lista);

    namespace utils {
        void inserirString(ListaLetra &lista, string_lista::String &listaS);

        void deletar(ListaLetra &lista);
    }
}

namespace lista_list {
    struct NodoLista {
        letra_lista::ListaLetra palavra;
        NodoLista *prox;
    };

    struct ListaLista {
        NodoLista *primeiro;
        NodoLista *ultimo;
    };

    void criarLista(ListaLista &lista);

    void insereFinal(ListaLista &lista, letra_lista::ListaLetra &palavra);
}

#endif // INTERFACE_H
