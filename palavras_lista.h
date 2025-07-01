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

namespace tbl_indxd {
    struct SegundoIndice {
        palavra_lista::ListaPalavra lista;
        SegundoIndice *prox;
    };

    struct PrimeiroIndice {
        SegundoIndice celula;
        PrimeiroIndice *prox;
    };

    struct TabelaIndexada {
        PrimeiroIndice *dados;
    };

    void criarTabela(TabelaIndexada &tabela);

    namespace utils {
        bool palavraInseridaExiste(string_lista::String &entrada, TabelaIndexada &tabela);

        void escolherPalavra(TabelaIndexada &tabela, string_lista::String &palavra);

        void indexarTabela(TabelaIndexada &tabela, palavra_lista::ListaPalavra &listaPalavra);
    }
}
/*
namespace dicionario {
    struct ListaInterna {
        palavra_lista::ListaPalavra lista;
        ListaInterna *prox;
    };

    struct ListaExterna {
        ListaInterna listaI;
        ListaExterna *prox;
    };

    void inicializarListaInterna(ListaInterna &lista);

    void inicializarListaExterna(ListaExterna &lista);

    namespace utils {

        ListaInterna *buscaIndiceAlfabetico(ListaExterna *listaPtr, string_lista::String &palavra);


        palavra_lista::ListaPalavra *buscaIndiceAlfabetico(ListaInterna *listaPtr, string_lista::String &palavra);

        void inserirPalavra(ListaExterna &listaE, string_lista::String &palavra);

        void imprimir(ListaExterna *lista);

        bool palavraInseridaExiste(string_lista::String &entrada, ListaExterna *listaPtr); // passo a palavra inserida e a lista externa (que contem a letra inicial de cada palavra da lista)

        void escolherPalavra(dicionario::ListaExterna *lista, string_lista::String &palavra);
    }
}
*/

#endif // PALAVRAS_LISTA_H
