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

    bool pesquisa(ListaPalavra &lista, string_lista::String &listaS);

    namespace utils {
        void inserePalavra(ListaPalavra &lista, string_lista::String &palavra);

        void salvarEmDisco(ListaPalavra &lista);

        /**
         * Deleta os nós de ListaPalavra (NodoPalavra), mas sem ousar deletar a
         * String do membro "palavra" e nem deletar a cabeça.
         */
        void deletar(ListaPalavra &lista);

        /**
         * Deleta (destrói) o conteúdo da String de cada nó de ListaPalavra.
         */
        void deletarConteudo(ListaPalavra &lista);

        /**
         * Deleta o conteúdo da String de cada nó de ListaPalavra e também
         * destrói ListaPalavra.
         */
        void destruicaoProfunda(ListaPalavra &lista);

        /**
         * Deleta os nós de ListaPalavra (NodoPalavra) e também a sua cabeça.
         */
        void destruir(ListaPalavra &lista);
    }
}

namespace tbl_indxd {
    /*
    struct SegundoIndice {
        palavra_lista::ListaPalavra lista;
        SegundoIndice *prox;
    };
    */

    struct PrimeiroIndice {
        palavra_lista::NodoPalavra *celula;
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

        /**
         * Destrói toda a TabelaIndexada, tanto SegundoIndice como o PrimeiroIndice.
         */
        void destruir(TabelaIndexada &tabela);
    }
}

#endif // PALAVRAS_LISTA_H
