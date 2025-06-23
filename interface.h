#ifndef INTERFACE_H
#define INTERFACE_H

#include "raylib.h"
#include "string_lista.h"

struct Texto {
    Vector2 posicao;        // Posição do texto na tela
    char *conteudo;         // Conteúdo para ser desenhado
    float tamanho;          // Tamanho do texto
    float espacamento;      // Espaçamento entre as letras
    bool mouseSobre;        // Identifica se o mouse está sobre o elemento
    Color cor;              // Cor normal do texto
    Color corSobre;         // Cor para quando o mouse estiver por cima
    Font fonte;            // Fonte para ser utilizada
};

struct Caixa {
    Rectangle retangulo;    // Posição inicial, largura e altura da caixa
    float redondeza;        // O quão redonda serão as bordas
    int segmentos;          // Quantidade de segmentos para as bordas
    bool mouseSobre;        // Identifica se o mouse está sobre o elemento
    Color cor;              // Cor normal da caixa
    Color corSobre;         // Cor para quando o mouse estiver por cima
};

struct CaixaTexto {
    Caixa caixa;
    Texto texto;
    int id;
};

/**
 * Este namespace contém definição de uma outra lista cujo objetivo é auxiliar
 * no desenho gráficos dos caracteres da String implementada por lista.
 */
namespace letra_lista {
    struct LetraEstilo {
        Vector2 posicao;                    // Posição da letra na tela
        float tamanho;                      // Tamanho da letra
        Color cor;                          // Cor da letra
        Font *fonte;                        // Fonte para ser utilizada
    };

    struct Letra {
        LetraEstilo estilo;                 // Estilo da letra
        string_lista::NodoString *letra;    // Aponta para o nó da String
    };

    struct NodoLetra {
        Letra info;                         // Dado da lista
        NodoLetra *prox;                    // Aponta para a próxima letra visual
        NodoLetra *ant;                     // Aponta para o nó anterior
    };

    struct ListaLetra {
        NodoLetra *primeiro;
        NodoLetra *ultimo;
    };

    /**
     * Inicializa a lista e utiliza a célula cabeça para armazenar um estilo
     * base para futuras inserções.
     */
    void criarLista(ListaLetra &lista, LetraEstilo &estiloBase);

    bool vazia(ListaLetra &lista);

    /**
     * Insere no final da lista um nó que aponta para o respectivo nó da String.
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
