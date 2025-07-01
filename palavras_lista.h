#ifndef PALAVRAS_LISTA_H
#define PALAVRAS_LISTA_H

#include "string_lista.h"

namespace palavra_lista {
    struct NodoPalavra {
        string_lista::String palavra;
        NodoPalavra *prox;
    };

    // É a, de fato, lista de palavras
    struct ListaPalavra {
        NodoPalavra *primeiro;
        NodoPalavra *ultimo;
    };

    void criarLista(ListaPalavra &lista);

    bool vazia(ListaPalavra &lista);

    void insereFinal(ListaPalavra &lista, string_lista::String &palavra);

    void removeFinal(ListaPalavra &lista);

    namespace utils {
        void inserePalavra(ListaPalavra &lista, string_lista::String &palavra);
    }
}

namespace dicionario {
    /*
     * Indexa a lista de palavras cuja segunda letra varia de "a" até "z"
     */
    struct ListaInterna {
        palavra_lista::ListaPalavra lista;
        ListaInterna *prox;
    };
    /*
     * Indexa a lista de palavras cuja primeira letra varia de "a" até "z"
     */
    struct ListaExterna {
        ListaInterna listaI;
        ListaExterna *prox;
    };

    void inicializarListaInterna(ListaInterna &lista);

    void inicializarListaExterna(ListaExterna &lista);

    namespace utils {
        /*
         * Ponteiro para ListaExterna foi enviado por ser mais conviente para percorrer a lista.
         * ListaExterna é percorrida em busca do nó que representa a primeira letra da String.
         *
         * Retorna um ponteiro para ListaInterna.
         */
        ListaInterna *buscaIndiceAlfabetico(ListaExterna *listaPtr, string_lista::String &palavra);

        /*
         * Ponteiro para ListaInterna foi enviado por ser mais conviente para percorrer a lista.
         * ListaInterna é percorrida em busca do nó que representa a segunda letra da String.
         *
         * Retorna um ponteiro para Palavra (que é a lista de palavras).
         */
        palavra_lista::ListaPalavra *buscaIndiceAlfabetico(ListaInterna *listaPtr, string_lista::String &palavra);

        void inserirPalavra(ListaExterna &listaE, string_lista::String &palavra);

        void imprimir(ListaExterna *lista);

        bool palavraInseridaExiste(string_lista::String &entrada, ListaExterna *listaPtr); // passo a palavra inserida e a lista externa (que contem a letra inicial de cada palavra da lista)

        void escolherPalavra(dicionario::ListaExterna *lista, string_lista::String &palavra);
    }
}

#endif // PALAVRAS_LISTA_H
